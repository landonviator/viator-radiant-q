#pragma once
#include <JuceHeader.h>
#include "../globals/Parameters.h"
#include "../PluginProcessor.h"

class PultecComp  : public juce::Component
{
public:
    PultecComp(ViatorradiantqAudioProcessor&);
    ~PultecComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorradiantqAudioProcessor& audioProcessor;
    
    void paintBackground(juce::Graphics& g);
    void paintScrews(juce::Graphics& g);
    void positionDials();
    void positionLabels();
    
    juce::OwnedArray<viator_gui::ImageFader> _dials;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
    void setDialProps();
    
    juce::OwnedArray<juce::Label> _labels;
    void setLabelProps();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PultecComp)
};
