#include "Parameters.h"


ViatorParameters::Params::Params()
{
    initSliderParams();
    initButtonParams();
    initMenuParams();
}

void ViatorParameters::Params::initSliderParams()
{
    using skew = SliderParameterData::SkewType;
    using type = SliderParameterData::NumericType;
    
    _sliderParams.push_back({ViatorParameters::lowBoostID, ViatorParameters::lowBoostName, 0.0f, 15.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat, false});
    _sliderParams.push_back({ViatorParameters::lowAttenID, ViatorParameters::lowAttenName, -15.0f, 0.0f, -15.0f, skew::kNoSkew, 0.0, type::kFloat, true});
    _sliderParams.push_back({ViatorParameters::highBoostID, ViatorParameters::highBoostName, 0.0f, 15.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat, false});
    _sliderParams.push_back({ViatorParameters::highAttenID, ViatorParameters::highAttenName, -15.0f, 0.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat, true});
    _sliderParams.push_back({ViatorParameters::highAttenRangeID, ViatorParameters::highAttenRangeName, 5000.0f, 20000.0f, 10000.0f, skew::kSkew, 10000.0, type::kInt, false});
    _sliderParams.push_back({ViatorParameters::lowFreqID, ViatorParameters::lowFreqName, 20.0f, 100.0f, 60.0f, skew::kSkew, 60.0, type::kInt, false});
    _sliderParams.push_back({ViatorParameters::bandwidthID, ViatorParameters::bandwidthFreqName, 0.0f, 10.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat, false});
    _sliderParams.push_back({ViatorParameters::highFreqID, ViatorParameters::highFreqName, 3000.0f, 16000.0f, 8000.0f, skew::kSkew, 8000.0f, type::kInt, false});
    _sliderParams.push_back({ViatorParameters::volumeID, ViatorParameters::volumeName, -30.0f, 30.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat, false});
}

void ViatorParameters::Params::initButtonParams()
{
}

void ViatorParameters::Params::initMenuParams()
{
}
