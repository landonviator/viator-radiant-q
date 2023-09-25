#pragma once
#include <JuceHeader.h>
#include "../globals/Parameters.h"
#include "../PluginProcessor.h"

class ViatorradiantqAudioProcessorEditor;

class PultecComp  : public juce::Component
{
public:
    PultecComp(ViatorradiantqAudioProcessor&);
    ~PultecComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ViatorradiantqAudioProcessor& audioProcessor;
    
    juce::OwnedArray<viator_gui::ImageFader> _dials;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
    juce::OwnedArray<juce::Label> _labels;
    void paintBackground(juce::Graphics& g);
    void paintScrews(juce::Graphics& g);
    void positionDials();
    void positionLabels();
    void setDialProps();
    void setLabelProps();
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    
    juce::StringArray _tooltips =
    {
        "Increases the volume of the signal going into the EQ.",
      "Increases the gain of a low-shelf filter at the specified cutoff frequency.",
        "Reduces the gain of a low-peak filter at a frequency higher than the low-shelf cutoff, thereby enhancing the precision of the low-shelf filter. When you set both the low boost and low attenuation to the same value, you achieve the iconic tube EQ trick.",
        "Increases the gain of a high-shelf filter at the specified cutoff frequency.",
        "Decreases the cutoff frequency of a low-pass filter, with its range determined by the 'High Range' parameter.",
        "Alters the spectrum of frequencies influenced by the 'High Attenuation' parameter.",
        "Changes the center frequency for the low filters.",
        "Changes the bandwidth (AKA Q) of all filters from wide to narrow.",
        "Changes the center frequency for the high shelf filter.",
        "Increase the volume of the signal coming out of the EQ."
    };
    
    std::unique_ptr<juce::Drawable> wideIcon;
    std::unique_ptr<juce::Drawable> narrowIcon;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PultecComp)
};
