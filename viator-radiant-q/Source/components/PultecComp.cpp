#include <JuceHeader.h>
#include "PultecComp.h"

PultecComp::PultecComp()
{

}

PultecComp::~PultecComp()
{
}

void PultecComp::paint (juce::Graphics& g)
{
    const auto shape = viator_utils::Gradient::RectShape::kRounded;
    auto rect = getLocalBounds();
    auto color = juce::Colour(35, 40, 51);
    auto contrast = 0.1;
    viator_utils::Gradient::addRadialGradient(g, color, rect, shape, contrast);
}

void PultecComp::resized()
{

}
