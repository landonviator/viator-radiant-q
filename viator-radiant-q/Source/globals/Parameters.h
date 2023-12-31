#pragma once
#include <JuceHeader.h>
#include "Globals.h"

namespace ViatorParameters
{
// Param data
struct SliderParameterData
{
    enum SkewType
    {
        kSkew,
        kNoSkew
    };
    
    enum NumericType
    {
        kInt,
        kFloat
    };
    
    public:
        juce::String paramID;
        juce::String paramName;
        float min;
        float max;
        float initial;
        SkewType isSkew;
        float center;
        NumericType isInt;
        bool isReverse;
};

struct ButtonParameterData
{
    public:
        juce::String paramID;
        juce::String paramName;
        bool initial;
};

struct MenuParameterData
{
    public:
        juce::String paramID;
        juce::String paramName;
        juce::StringArray choices;
        int defaultIndex;
};

    class Params
    {
    public:
        Params();
        
        // Get a ref to the param data
        std::vector<ViatorParameters::SliderParameterData>& getSliderParams(){return _sliderParams;};
        std::vector<ViatorParameters::ButtonParameterData>& getButtonParams(){return _buttonParams;};
        std::vector<ViatorParameters::MenuParameterData>& getMenuParams(){return _menuParams;};
        
        std::vector<ViatorParameters::SliderParameterData>& getPultecSliderParams(){return _pultecParams;};
        std::vector<ViatorParameters::SliderParameterData>& getIOSliderParams(){return _ioParams;};
        
    private:
        // Adds params to the vector
        void initSliderParams();
        void initButtonParams();
        void initMenuParams();
        
        
    private:
        // Vector holding param data
        std::vector<ViatorParameters::SliderParameterData> _sliderParams;
        std::vector<ViatorParameters::ButtonParameterData> _buttonParams;
        std::vector<ViatorParameters::MenuParameterData> _menuParams;
        
        std::vector<ViatorParameters::SliderParameterData> _pultecParams;
        std::vector<ViatorParameters::SliderParameterData> _ioParams;
    };
}
