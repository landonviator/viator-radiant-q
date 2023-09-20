/*
  ==============================================================================

    PultecComp.h
    Created: 20 Sep 2023 1:09:49am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PultecComp  : public juce::Component
{
public:
    PultecComp();
    ~PultecComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PultecComp)
};
