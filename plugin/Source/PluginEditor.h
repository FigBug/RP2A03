/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class RP2A03AudioProcessorEditor  : public gin::ProcessorEditor
{
public:
    RP2A03AudioProcessorEditor (RP2A03AudioProcessor&);
    ~RP2A03AudioProcessorEditor() override;

    //==============================================================================
    void resized() override;
    void paint (juce::Graphics& g) override;

    RP2A03AudioProcessor& proc;
    
    gin::TriggeredScope scope {proc.fifo};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RP2A03AudioProcessorEditor)
};
