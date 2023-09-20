#pragma once
#include <JuceHeader.h>
#include "../globals/Parameters.h"

class PultecComp  : public juce::Component
{
public:
    PultecComp();
    ~PultecComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void paintBackground(juce::Graphics& g);
    void paintScrews(juce::Graphics& g);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PultecComp)
};
