#include "PluginProcessor.h"
#include "PluginEditor.h"

ViatorradiantqAudioProcessorEditor::ViatorradiantqAudioProcessorEditor (ViatorradiantqAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), _pultecComp(audioProcessor)
{
    addAndMakeVisible(_headerComp);
    addAndMakeVisible(_pultecComp);
    viator_utils::PluginWindow::setPluginWindowSize(0.0, 0.0, *this, 2.0, 1.0);
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
}
