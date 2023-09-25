#include "PluginProcessor.h"
#include "PluginEditor.h"

ViatorradiantqAudioProcessorEditor::ViatorradiantqAudioProcessorEditor (ViatorradiantqAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), _pultecComp(audioProcessor)
{
    addAndMakeVisible(_headerComp);
    addAndMakeVisible(_pultecComp);
    setFaderProps();
    viator_utils::PluginWindow::setPluginWindowSize(audioProcessor._width, audioProcessor._height, *this, 2.0, 1.0);
}

ViatorradiantqAudioProcessorEditor::~ViatorradiantqAudioProcessorEditor()
{
}

//==============================================================================
void ViatorradiantqAudioProcessorEditor::paint (juce::Graphics& g)
{
    const auto shape = viator_utils::Gradient::RectShape::kRounded;
    auto rect = getLocalBounds();
    auto color = juce::Colour(14, 14, 14);
    auto contrast = 0.05;
    viator_utils::Gradient::addRadialGradient(g, color, rect, shape, contrast);
}

void ViatorradiantqAudioProcessorEditor::resized()
{
    // header
    const auto headerHeightMult = 0.12;
    const auto headerHeight = getHeight() * headerHeightMult;
    _headerComp.setBounds(0, 0, getWidth(), headerHeight);
    
    auto bgWidth = getWidth() * 0.9;
    auto bgHeight = getHeight() * 0.76;
    auto bgY = getHeight() * 0.18;
    _pultecComp.setBounds(getLocalBounds().withSizeKeepingCentre(bgWidth, bgHeight).withY(bgY));
    
    positionFaders();
    
    savePluginBounds();
}

void ViatorradiantqAudioProcessorEditor::savePluginBounds()
{
    audioProcessor.variableTree.setProperty("width", getWidth(), nullptr);
    audioProcessor.variableTree.setProperty("height", getHeight(), nullptr);
    audioProcessor._width = getWidth();
    audioProcessor._height = getHeight();
}

void ViatorradiantqAudioProcessorEditor::setFaderProps()
{
    auto params = audioProcessor._parameterMap;
    
    for (int i = 0; i < params.getIOSliderParams().size(); ++i)
    {
        _sliders.add(std::make_unique<viator_gui::Fader>());
        _attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params.getIOSliderParams()[i].paramID, *_sliders[i]));
        _sliders[i]->setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
        _sliders[i]->setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(99, 99, 99));
        _sliders[i]->setComponentID(params.getIOSliderParams()[i].paramID);
        _sliders[i]->setName(params.getIOSliderParams()[i].paramName);
        _sliders[i]->addMouseListener(this, false);
        _sliders[i]->setDialValueType(viator_gui::CustomFader::ValueType::kFloat);
        _sliders[i]->setViatorTooltip(_tooltips[i]);
        addAndMakeVisible(*_sliders[i]);
    }
}

void ViatorradiantqAudioProcessorEditor::positionFaders()
{
    auto compX = 0.0;
    auto compY = getHeight() * 0.25;
    const auto compWidth = getWidth() * 0.05;
    const auto compHeight = getHeight() * 0.6;
    _sliders[0]->setBounds(compX, compY, compWidth, compHeight);
    
    compX = getWidth() * 0.95;
    _sliders[1]->setBounds(compX, compY, compWidth, compHeight);
}

void ViatorradiantqAudioProcessorEditor::mouseEnter(const juce::MouseEvent &event)
{
    for (auto& slider : _sliders)
    {
        if (event.eventComponent == slider)
        {
            _headerComp.setViatorTooltip(slider->getViatorTooltip());
        }
    }
}

void ViatorradiantqAudioProcessorEditor::mouseExit(const juce::MouseEvent &event)
{
    _headerComp.setViatorTooltip("");
}
