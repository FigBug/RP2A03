#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class slLookAndFeel : public LookAndFeel_V3,
                      private DeletedAtShutdown
{
public:
    slLookAndFeel();
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override;
    
    
    
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override;
    
    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider&) override;
    
    Colour tyrianPurple;
    Colour prune;
    Colour fireEngineRed;
    Colour veryPaleYellow;
    Colour russianViolet;
    
    juce_DeclareSingleton(slLookAndFeel, false);
};
