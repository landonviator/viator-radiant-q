#include "PluginProcessor.h"
#include "PluginEditor.h"

ViatorradiantqAudioProcessor::ViatorradiantqAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ), _treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getMenuParams()[i].paramID, this);
    }
    
    for (int i = 0; i < 4; i++)
    {
        _filters.add(std::make_unique<viator_dsp::SVFilter<float>>());
    }
}

ViatorradiantqAudioProcessor::~ViatorradiantqAudioProcessor()
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getMenuParams()[i].paramID, this);
    }
}

const juce::String ViatorradiantqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ViatorradiantqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ViatorradiantqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ViatorradiantqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ViatorradiantqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ViatorradiantqAudioProcessor::getNumPrograms()
{
    return 1;
}

int ViatorradiantqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ViatorradiantqAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ViatorradiantqAudioProcessor::getProgramName (int index)
{
    return {};
}

void ViatorradiantqAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ViatorradiantqAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        auto param = _parameterMap.getSliderParams()[i];
        
        auto range = juce::NormalisableRange<float>(param.min, param.max);
        
        if (param.isSkew == ViatorParameters::SliderParameterData::SkewType::kSkew)
        {
            range.setSkewForCentre(param.center);
        }

        if (param.isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            params.push_back (std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, param.paramName, range, param.initial, valueToTextFunction, textToValueFunction));
        }
        
        else
        {
            params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, range, param.initial));
        }
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        auto param = _parameterMap.getButtonParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, _parameterMap.getButtonParams()[i].initial));
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        auto param = _parameterMap.getMenuParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, param.choices, param.defaultIndex));
    }
    
    return { params.begin(), params.end() };
}

void ViatorradiantqAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
}

void ViatorradiantqAudioProcessor::updateParameters()
{
    const auto lowFreq = _treeState.getRawParameterValue(ViatorParameters::lowFreqID)->load();
    const auto dipCutoff = _treeState.getRawParameterValue(ViatorParameters::lowFreqID)->load() * 3.0;
    const auto lowAtten = _treeState.getRawParameterValue(ViatorParameters::lowAttenID)->load();
    const auto lowAttenReversed = juce::jmap(lowAtten, 0.0f, -10.0f, -10.0f, 0.0f);
    const auto lowAttenRange = juce::jmap(std::abs(lowAttenReversed), 0.0f, 10.0f, 0.0f, 2.0f);
    const auto dipMovement = dipCutoff * (1.0 / (lowAttenRange + 1.0));
    
    const auto lowBoost = _treeState.getRawParameterValue(ViatorParameters::lowBoostID)->load();
    const auto highFreq = _treeState.getRawParameterValue(ViatorParameters::highFreqID)->load();
    const auto highBoost = _treeState.getRawParameterValue(ViatorParameters::highBoostID)->load();
    const auto highAtten = _treeState.getRawParameterValue(ViatorParameters::highAttenID)->load();
    
    const auto gain = _treeState.getRawParameterValue(ViatorParameters::gainID)->load();
    const auto volume = _treeState.getRawParameterValue(ViatorParameters::volumeID)->load();
    
    _gainModule.setGainDecibels(gain);
    _volumeModule.setGainDecibels(volume + 5.5);
    
    _filters[0]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, lowFreq);
    _filters[1]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, dipMovement);
    _filters[2]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, highFreq);
    
    const auto range = _treeState.getRawParameterValue(ViatorParameters::highAttenRangeID)->load();
    const auto highCut = juce::jmap(highAtten, -10.0f, 0.0f, 22000.0f, range);
    _filters[3]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, highCut);
    
    _filters[0]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, lowBoost);
    _filters[1]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, lowAttenReversed * 0.4);
    _filters[2]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, highBoost);
    _filters[3]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, highAtten);
    
    const auto q = _treeState.getRawParameterValue(ViatorParameters::bandwidthID)->load();
    const auto qScaled = juce::jmap(q, 0.0f, 10.0f, 0.5f, 1.5f);
    
    _filters[0]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, qScaled);
    _filters[2]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, qScaled);
    _filters[3]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, qScaled);
}

void ViatorradiantqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _spec.sampleRate = sampleRate;
    _spec.maximumBlockSize = samplesPerBlock;
    _spec.numChannels = getTotalNumInputChannels();
    
    for (int i = 0; i < _filters.size(); i++)
    {
        _filters[i]->prepare(_spec);
        _filters[i]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kQType, viator_dsp::SVFilter<float>::QType::kParametric);
    }
    
    _filters[0]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowShelf);
    _filters[1]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kBandShelf);
    _filters[1]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, 1.0);
    _filters[2]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kBandShelf);
    _filters[3]->setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowPass);
    
    _lowShelfCompensation.prepare(_spec);
    _lowShelfCompensation.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowShelf);
    _lowShelfCompensation.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, -0.5);
    _lowShelfCompensation.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, 600.0);
    
    _gainModule.prepare(_spec);
    _gainModule.setRampDurationSeconds(0.02);
    _volumeModule.prepare(_spec);
    _volumeModule.setRampDurationSeconds(0.02);
}

void ViatorradiantqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ViatorradiantqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
    || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void ViatorradiantqAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::dsp::AudioBlock<float> block {buffer};
    updateParameters();
    
    _gainModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    for (int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        float* data = block.getChannelPointer(ch);
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            auto input = data[sample];
            data[sample] = _piDivisor * std::atan(input);
        }
    }
    
    for (auto& filter : _filters)
    {
        filter->process(juce::dsp::ProcessContextReplacing<float>(block));
    }
    
    _volumeModule.process(juce::dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool ViatorradiantqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ViatorradiantqAudioProcessor::createEditor()
{
    return new ViatorradiantqAudioProcessorEditor (*this);
}

//==============================================================================
void ViatorradiantqAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    _treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    _treeState.state.writeToStream (stream);
}

void ViatorradiantqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        _treeState.state = tree;
        _width = variableTree.getProperty("width");
        _height = variableTree.getProperty("height");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ViatorradiantqAudioProcessor();
}
