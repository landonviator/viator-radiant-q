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
    paintBackground(g);
    paintScrews(g);
}

void PultecComp::resized()
{

}

void PultecComp::paintBackground(juce::Graphics &g)
{
    const auto shape = viator_utils::Gradient::RectShape::kRounded;
    auto rect = getLocalBounds();
    auto color = juce::Colour(35, 40, 51).darker(1.4);
    auto contrast = 0.1;
    viator_utils::Gradient::addRadialGradient(g, color, rect, shape, contrast);
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.15f));
    auto texture = juce::ImageCache::getFromMemory(BinaryData::lightgrayconcretewall_jpg, BinaryData::lightgrayconcretewall_jpgSize);
    g.drawImage(texture, getLocalBounds().toFloat());
    g.setColour(juce::Colours::whitesmoke);
}

void PultecComp::paintScrews(juce::Graphics &g)
{
    auto screw = juce::ImageCache::getFromMemory(BinaryData::screw_png, BinaryData::screw_pngSize);
    auto screwX = getWidth() * 0.035;
    auto screwY = getHeight() * 0.23;
    auto screwSize = getWidth() * 0.03;
    g.drawImageWithin(screw, screwX, screwY, screwSize, screwSize, juce::RectanglePlacement::stretchToFit);
    screwY *= 3;
    g.drawImageWithin(screw, screwX, screwY, screwSize, screwSize, juce::RectanglePlacement::stretchToFit);
    screwX = getWidth() * 0.965 - screwSize;
    screwY = getHeight() * 0.23;
    g.drawImageWithin(screw, screwX, screwY, screwSize, screwSize, juce::RectanglePlacement::stretchToFit);
    screwY *= 3;
    g.drawImageWithin(screw, screwX, screwY, screwSize, screwSize, juce::RectanglePlacement::stretchToFit);
}
