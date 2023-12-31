#pragma once
#include <JuceHeader.h>
#include "globals/Parameters.h"

class ViatorradiantqAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ViatorradiantqAudioProcessor();
    ~ViatorradiantqAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    ViatorParameters::Params _parameterMap;
    juce::AudioProcessorValueTreeState _treeState;
    
    juce::ValueTree variableTree
    { "Variables", {},
        {
        { "Group", {{ "name", "Vars" }},
            {
                { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "height" }, { "value", 0.0 }}}
            }
        }
        }
    };
    
    float _width = 0.0f;
    float _height = 0.0f;
    
private:
    
    juce::dsp::ProcessSpec _spec;
    juce::OwnedArray<viator_dsp::SVFilter<float>> _filters;
    viator_dsp::SVFilter<float> _lowShelfCompensation;
    juce::dsp::Gain<float> _gainModule;
    juce::dsp::Gain<float> _volumeModule;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    using Parameter = juce::AudioProcessorValueTreeState::Parameter;
    static juce::String valueToTextFunction(float x) { return juce::String(static_cast<int>(x)); }
    static float textToValueFunction(const juce::String& str) { return str.getFloatValue(); }
    void updateParameters();
    
    const int _versionNumber = 1;
    static constexpr float _piDivisor = 2.0 / juce::MathConstants<float>::pi;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorradiantqAudioProcessor)
};
