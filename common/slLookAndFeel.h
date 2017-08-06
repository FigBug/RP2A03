#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class slLookAndFeel : public LookAndFeel_V3
{
public:
    slLookAndFeel();
    
    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider&) override;
    
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
    
    void drawButtonText (Graphics&, TextButton&, bool isMouseOverButton, bool isButtonDown) override;

};
