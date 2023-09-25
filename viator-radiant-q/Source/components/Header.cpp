#include <JuceHeader.h>
#include "Header.h"

Header::Header()
{
    _tooltipLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_tooltipLabel);
}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    
    // force image to color correctly
    g.setColour(juce::Colours::white.withAlpha(0.7f));
    
    // add logo image
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon_png, BinaryData::landon_pngSize);
    g.drawImageWithin(headerLogo,
                      getWidth() * 0.02,
                      0,
                      getWidth() * 0.17,
                      getHeight(),
                      juce::RectanglePlacement::centred);
    
    g.setColour(juce::Colour::fromRGB(60, 60, 73).brighter(0.1).withAlpha(0.25f));
    g.drawLine(rect.getX(), rect.getHeight(), rect.getWidth(), rect.getHeight(), 2.0f);
}

void Header::resized()
{
    const auto compX = getWidth() * 0.2;
    const auto compWidth = getWidth() * 0.77;
    _tooltipLabel.setBounds(compX, 0, compWidth, getHeight());
    _tooltipLabel.setFont(juce::Font("Helvetica", getHeight() * 0.25, juce::Font::FontStyleFlags::plain));
}

void Header::setViatorTooltip(const juce::String &content)
{
    _tooltipLabel.setText(content, juce::dontSendNotification);
}
