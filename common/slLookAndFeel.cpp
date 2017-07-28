#include "slLookAndFeel.h"

juce_ImplementSingleton(slLookAndFeel);

//==============================================================================
slLookAndFeel::slLookAndFeel()
  : tyrianPurple (0xff561643),
    prune (0xff6c0e23),
    fireEngineRed (0xffc42021),
    veryPaleYellow (0xfff3ffb9),
    russianViolet (0xff3c1742)
{
    setColour (Label::textColourId, Colours::white.withAlpha (0.9f));
    
    setColour (Slider::rotarySliderFillColourId, Colours::white);
}

void slLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                      float sliderPos, float minSliderPos, float maxSliderPos,
                                      const Slider::SliderStyle style, Slider& slider)
{
    g.fillAll (slider.findColour (Slider::backgroundColourId));
    
    if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
    {
        const float fx = (float) x, fy = (float) y, fw = (float) width, fh = (float) height;
        
        Path p;
        
        if (style == Slider::LinearBarVertical)
            p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
        else
            p.addRectangle (fx, fy, sliderPos - fx, fh);
        
        Colour baseColour (slider.findColour (Slider::thumbColourId)
                           .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                           .withMultipliedAlpha (0.8f));
        
        g.setGradientFill (ColourGradient (baseColour.brighter (0.08f), 0.0f, 0.0f,
                                           baseColour.darker (0.08f), 0.0f, (float) height, false));
        g.fillPath (p);
        
        g.setColour (baseColour.darker (0.2f));
        
        if (style == Slider::LinearBarVertical)
            g.fillRect (fx, sliderPos, fw, 1.0f);
        else
            g.fillRect (sliderPos, fy, 1.0f, fh);
    }
    else
    {
        drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

void slLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                float /*sliderPos*/,
                                                float /*minSliderPos*/,
                                                float /*maxSliderPos*/,
                                                const Slider::SliderStyle /*style*/, Slider& slider)
{
    const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
    
    const Colour trackColour (slider.findColour (Slider::trackColourId));
    const Colour gradCol1 (trackColour.overlaidWith (Colour (slider.isEnabled() ? 0x13000000 : 0x09000000)));
    const Colour gradCol2 (trackColour.overlaidWith (Colour (0x06000000)));
    Path indent;
    
    if (slider.isHorizontal())
    {
        const float iy = y + height * 0.5f - sliderRadius * 0.5f;
        
        g.setGradientFill (ColourGradient (gradCol1, 0.0f, iy,
                                           gradCol2, 0.0f, iy + sliderRadius, false));
        
        indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius, 5.0f);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        
        g.setGradientFill (ColourGradient (gradCol1, ix, 0.0f,
                                           gradCol2, ix + sliderRadius, 0.0f, false));
        
        indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius, 5.0f);
    }
    
    g.fillPath (indent);
    
    g.setColour (trackColour.contrasting (0.5f));
    g.strokePath (indent, PathStrokeType (0.5f));
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
        const float thickness = 0.7f;

        g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (0.05f));
        
        {
            Path filledArc;
            filledArc.addPieSegment (rx, ry, rw, rw, angle, rotaryEndAngle, thickness);
            g.fillPath (filledArc);
        }
        
        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 0.9f : 0.8f));
        
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
