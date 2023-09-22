#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "components/Header.h"
#include "components/PultecComp.h"

class ViatorradiantqAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ViatorradiantqAudioProcessorEditor (ViatorradiantqAudioProcessor&);
    ~ViatorradiantqAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorradiantqAudioProcessor& audioProcessor;

    Header _headerComp;
    PultecComp _pultecComp;
    
    // Save plugin size in value tree
    void savePluginBounds();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorradiantqAudioProcessorEditor)
};
