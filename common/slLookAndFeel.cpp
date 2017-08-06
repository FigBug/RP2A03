#include "slLookAndFeel.h"

//==============================================================================
slLookAndFeel::slLookAndFeel()
{
    setColour (Label::textColourId, Colours::white.withAlpha (0.9f));
    
    setColour (Slider::rotarySliderFillColourId, Colours::white);
    
    setColour (TextButton::buttonColourId, Colours::black);
    setColour (TextButton::buttonOnColourId, Colours::white);
    setColour (TextButton::textColourOffId, Colours::white);
    setColour (TextButton::textColourOnId, Colours::black);
}

void slLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                      const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin (width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    
    if (radius > 12.0f)
    {
        const float thickness = 0.8f;

        g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (0.05f));
        
        {
            Path filledArc;
            filledArc.addPieSegment (rx, ry, rw, rw, angle, rotaryEndAngle, thickness);
            g.fillPath (filledArc);
        }
        
        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 0.95f : 0.9f));
        
        {
            Path filledArc;
            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
            g.fillPath (filledArc);
        }
        
   }
    else
    {
        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (Colour (0x80808080));
        
        Path p;
        p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
        PathStrokeType (rw * 0.1f).createStrokedPath (p, p);
        
        p.addLineSegment (Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);
        
        g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    }
}

void slLookAndFeel::drawButtonBackground (Graphics& g, Button& b, const Colour& backgroundColour,
                                          bool isMouseOverButton, bool isButtonDown)
{
    g.setColour (b.findColour (TextButton::buttonOnColourId));
    if (b.getToggleState())
        g.fillRect (b.getLocalBounds());
    else
        g.drawRect (b.getLocalBounds());
}

void slLookAndFeel::drawButtonText (Graphics& g, TextButton& b, bool isMouseOverButton, bool isButtonDown)
{
    g.setFont (getTextButtonFont (b, b.getHeight()));
    
    g.setColour (b.findColour (b.getToggleState() ? TextButton::textColourOnId : TextButton::textColourOffId));
    g.drawText (b.getButtonText(), b.getLocalBounds(), Justification::centred);
}
