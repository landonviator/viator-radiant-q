#pragma once
#include <JuceHeader.h>

class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setViatorTooltip(const juce::String& content);
    
private:
    
    juce::Label _tooltipLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
