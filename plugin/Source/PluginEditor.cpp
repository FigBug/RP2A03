/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
RP2A03AudioProcessorEditor::RP2A03AudioProcessorEditor (RP2A03AudioProcessor& p)
    : slAudioProcessorEditor (p), processor (p)
{
    logo = ImageFileFormat::loadFrom (BinaryData::logo_png, BinaryData::logo_pngSize);
    
    for (slParameter* pp : p.getPluginParameters())
    {
        ParamComponent* c = pp->isOnOff() ? (ParamComponent*)new Switch (pp) : (ParamComponent*)new Knob (pp);
        
        addAndMakeVisible (c);
        controls.add (c);
    }
    
    addAndMakeVisible (&scope);
    
    setGridSize (6, 2);
    
    scope.setNumSamplesPerPixel (2);
    scope.setVerticalZoomFactor (3.0f);
}

RP2A03AudioProcessorEditor::~RP2A03AudioProcessorEditor()
{
}

//==============================================================================
void RP2A03AudioProcessorEditor::paint (Graphics& g)
{
    slAudioProcessorEditor::paint (g);
    
    g.setFont (Font (15.0f));
    g.setColour (Colours::white);
    g.drawText("Ver: " JucePlugin_VersionString, getLocalBounds().reduced (4), Justification::topRight);
    
    g.drawImageAt (logo, getWidth() / 2 - logo.getWidth() / 2, 0);
}

void RP2A03AudioProcessorEditor::resized()
{
    using AP = RP2A03AudioProcessor;
    
    slAudioProcessorEditor::resized();
    
    Rectangle<int> r = getControlsArea();
    
    componentForId (AP::paramPulse1Level)->setBounds (getGridArea (0, 0));
    componentForId (AP::paramPulse1DutyCycle)->setBounds (getGridArea (0, 1));
    componentForId (AP::paramPulse2Level)->setBounds (getGridArea (1, 0));
    componentForId (AP::paramPulse2DutyCycle)->setBounds (getGridArea (1, 1));
    componentForId (AP::paramNoiseLevel)->setBounds (getGridArea (4, 0));
    componentForId (AP::paramNoiseShort)->setBounds (getGridArea (4, 1));
    componentForId (AP::paramTriangleLevel)->setBounds (getGridArea (5, 0));
    componentForId (AP::paramOutput)->setBounds (getGridArea (5, 1));

    scope.setBounds (getGridArea (2, 0, 2, 2).reduced (5));
}
