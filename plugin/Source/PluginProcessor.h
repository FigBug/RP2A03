/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Simple_Apu.h"

//==============================================================================
/**
*/
class RP2A03AudioProcessorEditor;
class RP2A03AudioProcessor : public gin::Processor
{
public:
    //==============================================================================
    RP2A03AudioProcessor();
    ~RP2A03AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    
    static const char* paramPulse1Level;
    static const char* paramPulse1DutyCycle;
    static const char* paramPulse2Level;
    static const char* paramPulse2DutyCycle;
    static const char* paramTriangleLevel;
    static const char* paramNoiseLevel;
    static const char* paramNoiseShort;
    static const char* paramOutput;
    static const char* paramPulse1Tune;
    static const char* paramPulse1TuneFine;
    static const char* paramPulse2Tune;
    static const char* paramPulse2TuneFine;
    static const char* paramTriangleTune;
    static const char* paramTriangleTuneFine;
    static const char* paramPulse1Sweep;
    static const char* paramPulse1Shift;
    static const char* paramPulse2Sweep;
    static const char* paramPulse2Shift;

    gin::AudioFifo fifo {1, 44100};
    
private:
    void runUntil (int& done, AudioSampleBuffer& buffer, int pos);
    void runOsc (int curNote, bool trigger);
    void writeReg (int reg, int value, bool force);
    
    int lastNote = -1;
    int velocity = 0;
    Array<int> noteQueue;
    
    LinearSmoothedValue<float> outputSmoothed;
    
    Simple_Apu apu;
    
    std::map<int, int> regCache;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RP2A03AudioProcessor)
};
