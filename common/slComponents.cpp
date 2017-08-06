/*
  ==============================================================================

    slComponents.cpp
    Created: 3 Nov 2015 9:33:48am
    Author:  Roland Rabien

  ==============================================================================
*/

#include "slComponents.h"

//==============================================================================
Readout::Readout (slParameter* parameter_)
  : parameter (parameter_)
{
    parameter->addListener (this);
    setText (parameter->getUserValueText(), dontSendNotification);
}

Readout::~Readout()
{
    parameter->removeListener (this);
}

void Readout::parameterChanged (slParameter *source)
{
    setText (parameter->getUserValueText(), dontSendNotification);
}

//==============================================================================
ParamComponent::ParamComponent (slParameter* parameter_)
  : Component (""), parameter (parameter_)
{
    
}
//==============================================================================
Knob::Knob (slParameter* parameter)
  : ParamComponent (parameter),
    value (parameter),
    knob (parameter, Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox)
{
    addAndMakeVisible (name);
    addAndMakeVisible (value);
    addAndMakeVisible (knob);
 
    knob.setSkewFactor (parameter->getSkew());
    
    name.setText (parameter->getShortName(), dontSendNotification);
    value.setJustificationType (Justification::centredTop);
    name.setJustificationType (Justification::centredBottom);
    
    value.setFont (value.getFont().withHeight (15.0));
}

void Knob::resized()
{
    Rectangle<int> r = getLocalBounds().reduced (4);
    
    name.setBounds (r.removeFromTop (20));
    value.setBounds (r.removeFromBottom (20));
    knob.setBounds (r.reduced (2));
}
//==============================================================================
Switch::Switch (slParameter* parameter)
  : ParamComponent (parameter),
    button (parameter)
{
    addAndMakeVisible (&name);
    addAndMakeVisible (&button);
    
    name.setText (parameter->getShortName(), dontSendNotification);
    name.setJustificationType (Justification::centred);
}

void Switch::resized()
{
    Rectangle<int> r = getLocalBounds().withSizeKeepingCentre (getWidth() - 10, 20);
    
    button.setBounds (r);
    name.setBounds (r.translated (0, -20));
}
