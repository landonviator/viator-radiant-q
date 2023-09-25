#include <JuceHeader.h>
#include "PultecComp.h"
#include "../PluginEditor.h"

PultecComp::PultecComp(ViatorradiantqAudioProcessor& p) : audioProcessor(p)
{
    setDialProps();
    setLabelProps();
    
    wideIcon = juce::Drawable::createFromImageData(BinaryData::fadsoftclip_svg, BinaryData::fadsoftclip_svgSize);
    narrowIcon = juce::Drawable::createFromImageData(BinaryData::fadfilterbandpass_svg, BinaryData::fadfilterbandpass_svgSize);

}

PultecComp::~PultecComp()
{
}

void PultecComp::paint (juce::Graphics& g)
{
    paintBackground(g);
    paintScrews(g);
    
    auto imageX = _dials[6]->getX() - getWidth() * 0.02;
    const auto imageY = getHeight() * 0.785;
    const auto imageSize = _dials[6]->getWidth() * 0.15;
    
    if (wideIcon)
    {
        wideIcon->replaceColour(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
        wideIcon->drawWithin(g, getLocalBounds().toFloat().withX(imageX).withY(imageY).withWidth(imageSize).withHeight(imageSize), juce::RectanglePlacement::stretchToFit, 1.0f);
    }
    
    imageX = _dials[6]->getRight();
    
    if (narrowIcon)
    {
        narrowIcon->replaceColour(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
        narrowIcon->drawWithin(g, getLocalBounds().toFloat().withX(imageX).withY(imageY).withWidth(imageSize).withHeight(imageSize), juce::RectanglePlacement::stretchToFit, 1.0f);
    }
}

void PultecComp::resized()
{
    positionDials();
    positionLabels();
}

void PultecComp::setDialProps()
{
    auto params = audioProcessor._parameterMap;
    auto mainDialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
    auto auxDialImage = juce::ImageCache::getFromMemory(BinaryData::Knob_01_png, BinaryData::Knob_01_pngSize);
    auto scaleImage = juce::ImageCache::getFromMemory(BinaryData::scale_small_knob_b_png, BinaryData::scale_small_knob_b_pngSize);
    
    for (int i = 0; i < params.getPultecSliderParams().size(); ++i)
    {
        auto isAuxDial = i == 4 || i == 5 || i == 7;
        auto isReversed = i == 1 || i == 3;
        
        _dials.add(std::make_unique<viator_gui::ImageFader>());
        _attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, params.getPultecSliderParams()[i].paramID, *_dials[i]));
        _dials[i]->setComponentID(params.getPultecSliderParams()[i].paramID);
        _dials[i]->setName(params.getPultecSliderParams()[i].paramName);
        _dials[i]->setFaderImageAndNumFrames(isAuxDial ? auxDialImage : mainDialImage, 128);
        _dials[i]->addMouseListener(this, true);
        _dials[i]->setIsReversed(isReversed);
        
        if (isAuxDial)
        {
            _dials[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kInt);
        }
        
        _dials[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        _dials[i]->setViatorTooltip(_tooltips[i + 1]);
        addAndMakeVisible(*_dials[i]);
    }
}

void PultecComp::setLabelProps()
{
    for (int i = 0; i < 2; ++i)
    {
        _labels.add(std::make_unique<juce::Label>());
        _labels[i]->setJustificationType(juce::Justification::centred);
        _labels[i]->setColour(juce::Label::ColourIds::textColourId, juce::Colours::ghostwhite.withAlpha(0.25f));
        addAndMakeVisible(*_labels[i]);
    }
    
    _labels[0]->setText("Radiant Q", juce::dontSendNotification);
    _labels[1]->setText("Electron Tube Powered \n Program Equalizer", juce::dontSendNotification);
}

void PultecComp::paintBackground(juce::Graphics &g)
{
    const auto shape = viator_utils::Gradient::RectShape::kRounded;
    auto rect = getLocalBounds();
    auto color = juce::Colour(22, 33, 62).darker(0.2);
    auto contrast = 0.1;
    viator_utils::Gradient::addRadialGradient(g, color, rect, shape, contrast);
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.1f));
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

void PultecComp::positionLabels()
{
    const auto labelX = getWidth() * 0.7;
    const auto labelY = getHeight() * 0.6;
    const auto labelWidth = getWidth() * 0.2;
    const auto labelHeight = getHeight() * 0.1;
    _labels[0]->setBounds(labelX, labelY, labelWidth, labelHeight);
    _labels[0]->setFont(juce::Font("Helvetica", _labels[0]->getHeight() * 0.8, juce::Font::FontStyleFlags::bold));
    _labels[1]->setBounds(labelX, _labels[0]->getBottom(), labelWidth, labelHeight * 2.0);
    _labels[1]->setFont(juce::Font("Helvetica", _labels[0]->getHeight() * 0.4, juce::Font::FontStyleFlags::plain));
}

void PultecComp::mouseEnter(const juce::MouseEvent &event)
{
    if (auto slider = dynamic_cast<viator_gui::ImageFader*>(event.eventComponent))
    {
        if (auto parent = dynamic_cast<ViatorradiantqAudioProcessorEditor*>(getParentComponent()))
        {
            parent->getViatorHeader().setViatorTooltip(slider->getViatorTooltip());
        }
    }
}

void PultecComp::mouseExit(const juce::MouseEvent &event)
{
    if (auto parent = dynamic_cast<ViatorradiantqAudioProcessorEditor*>(getParentComponent()))
    {
        parent->getViatorHeader().setViatorTooltip("");
    }
}
