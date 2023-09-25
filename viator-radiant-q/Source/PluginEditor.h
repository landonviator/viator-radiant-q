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

    Header& getViatorHeader(){return _headerComp;};
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorradiantqAudioProcessor& audioProcessor;

    Header _headerComp;
    PultecComp _pultecComp;
    
    juce::OwnedArray<viator_gui::Fader> _sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
    void positionFaders();
    void setFaderProps();
    
    juce::StringArray _tooltips =
    {
        "Increases the volume of the signal going into the EQ. This will drive the distortion when raised above 0 dB.",
        "Increase the volume of the signal coming out of the EQ. This will NOT drive the distortion, only raise the volume."
    };
    
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    
    // Save plugin size in value tree
    void savePluginBounds();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorradiantqAudioProcessorEditor)
};
