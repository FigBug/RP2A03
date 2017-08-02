/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RP2A03AudioProcessorEditor::RP2A03AudioProcessorEditor (RP2A03AudioProcessor& p)
    : slAudioProcessorEditor (&p), processor (p)
{
    for (slParameter* pp : p.getPluginParameters())
    {
        Knob* k = new Knob (pp);
        
        addAndMakeVisible (k);
        controls.add (k);
    }
    
    addAndMakeVisible (&scope);
    
    setSize (600, 350);
    
    scope.setNumSamplesPerPixel (10);
    scope.setVerticalZoomFactor (3.0f);
}

RP2A03AudioProcessorEditor::~RP2A03AudioProcessorEditor()
{
}

//==============================================================================
void RP2A03AudioProcessorEditor::resized()
{
    slAudioProcessorEditor::resized();
    
    Rectangle<int> r = getControlsArea().removeFromTop (150);
    
    int w = r.getWidth() / controls.size();
    
    for (auto c : controls)
        c->setBounds (r.removeFromLeft (w));
    
    r = getControlsArea().removeFromBottom (130);
    scope.setBounds (r);
}
