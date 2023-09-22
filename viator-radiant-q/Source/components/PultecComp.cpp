#include <JuceHeader.h>
#include "PultecComp.h"

PultecComp::PultecComp(ViatorradiantqAudioProcessor& p) : audioProcessor(p)
{
    setDialProps();
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
    positionDials();
}

void PultecComp::setDialProps()
{
    auto params = audioProcessor._parameterMap;
    auto mainDialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
    auto auxDialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_01_png, BinaryData::Knob_01_pngSize);
    auto scaleImage = juce::ImageCache::getFromMemory(BinaryData::scale_small_knob_b_png, BinaryData::scale_small_knob_b_pngSize);
    
    for (int i = 0; i < params.getSliderParams().size(); ++i)
    {
        auto isAuxDial = i == 4 || i == 5 || i == 7;
        
        _dials.add(std::make_unique<viator_gui::ImageFader>());
        _attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params.getSliderParams()[i].paramID, *_dials[i]));
        _dials[i]->setComponentID(params.getSliderParams()[i].paramID);
        _dials[i]->setName(params.getSliderParams()[i].paramName);
        _dials[i]->setFaderImageAndNumFrames(isAuxDial ? auxDialImage : mainDialImage, 128);
        
        if (isAuxDial)
        {
            _dials[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kInt);
        }
        
        _dials[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        addAndMakeVisible(*_dials[i]);
    }
}

void PultecComp::paintBackground(juce::Graphics &g)
{
    const auto shape = viator_utils::Gradient::RectShape::kRounded;
    auto rect = getLocalBounds();
    auto color = juce::Colour(22, 33, 62).darker(0.2);
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

void PultecComp::positionDials()
{
    auto compX = getWidth() * 0.12;
    auto compY = getHeight() * 0.1;
    const auto compSize = getWidth() * 0.12;
    const auto padding = getWidth() * 0.025;
    
    _dials[0]->setBounds(compX, compY, compSize, compSize);
    compX += compSize + padding;
    _dials[1]->setBounds(compX, compY, compSize, compSize);
    compX += compSize + padding * 4.0;
    _dials[2]->setBounds(compX, compY, compSize, compSize);
    compX += compSize + padding;
    _dials[3]->setBounds(compX, compY, compSize, compSize);
    compX += compSize + padding * 1.3;
    _dials[4]->setBounds(compX, compY, compSize, compSize);
    
    compY += compSize * 1.6;
    compX = getWidth() * 0.192;
    _dials[5]->setBounds(compX, compY, compSize, compSize);
    compX = getWidth() * 0.38;
    _dials[6]->setBounds(compX, compY, compSize, compSize);
    compX = getWidth() * 0.556;
    _dials[7]->setBounds(compX, compY, compSize, compSize);
}
