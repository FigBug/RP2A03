/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const char* RP2A03AudioProcessor::paramPulse1Level      = "pulse1Level";
const char* RP2A03AudioProcessor::paramPulse1DutyCycle  = "pulse1Duty";
const char* RP2A03AudioProcessor::paramPulse2Level      = "pulse2Level";
const char* RP2A03AudioProcessor::paramPulse2DutyCycle  = "pulse2Duty";
const char* RP2A03AudioProcessor::paramTriangleLevel    = "triangleLevel";
const char* RP2A03AudioProcessor::paramNoiseLevel       = "noiseLevel";
const char* RP2A03AudioProcessor::paramNoiseShort       = "noisePeriod";
const char* RP2A03AudioProcessor::paramOutput           = "output";
const char* RP2A03AudioProcessor::paramPulse1Tune       = "pulse1Tune";
const char* RP2A03AudioProcessor::paramPulse1TuneFine   = "pulse1TuneFine";
const char* RP2A03AudioProcessor::paramPulse2Tune       = "pulse2Tune";
const char* RP2A03AudioProcessor::paramPulse2TuneFine   = "pulse2TuneFine";
const char* RP2A03AudioProcessor::paramTriangleTune     = "triangleTune";
const char* RP2A03AudioProcessor::paramTriangleTuneFine = "triangleTuneFine";
const char* RP2A03AudioProcessor::paramPulse1Sweep      = "pulse1Sweep";
const char* RP2A03AudioProcessor::paramPulse1Shift      = "pulse1Shift";
const char* RP2A03AudioProcessor::paramPulse2Sweep      = "pulse2Sweep";
const char* RP2A03AudioProcessor::paramPulse2Shift      = "pulse2Shift";

//==============================================================================
static juce::String percentTextFunction (const gin::Parameter& p, float v)
{
    return juce::String::formatted("%.0f%%", v / p.getUserRangeEnd() * 100);
}

static juce::String onOffTextFunction (const gin::Parameter&, float v)
{
    return v > 0.0f ? "On" : "Off";
}

static juce::String dutyTextFunction (const gin::Parameter&, float v)
{
    const int duty = int (v);
    switch (duty)
    {
        case 0: return "12.5%";
        case 1: return "25%";
        case 2: return "50%";
        case 3: return "75%";
    }
    return "";
}

static juce::String sweepTextFunction (const gin::Parameter&, float v)
{
	juce::String str;
    switch (int (v))
    {
        case 0: str = "Off"; break;
		default: str = juce::String (int (v));
    }
    return str;
}

static juce::String intTextFunction (const gin::Parameter&, float v)
{
    return juce::String (int (v));
}

//==============================================================================
RP2A03AudioProcessor::RP2A03AudioProcessor()
    : gin::Processor (false, gin::ProcessorOptions().withAdditionalCredits({"Shay Green"}))
{
    addExtParam (paramPulse1Level,     "Pulse 1 Level",      "Pulse",       "", {    0.0f,   1.0f, 0.0f, 1.0f }, 1.0f, 0.0f, percentTextFunction);
    addExtParam (paramPulse1DutyCycle, "Pulse 1 Duty Cycle", "Duty Cycle",  "", {    0.0f,   3.0f, 1.0f, 1.0f }, 0.0f, 0.0f, dutyTextFunction);
    addExtParam (paramPulse2Level,     "Pulse 2 Level",      "Pulse",       "", {    0.0f,   1.0f, 0.0f, 1.0f }, 0.0f, 0.0f, percentTextFunction);
    addExtParam (paramPulse2DutyCycle, "Pulse 2 Duty Cycle", "Duty Cycle",  "", {    0.0f,   3.0f, 1.0f, 1.0f }, 0.0f, 0.0f, dutyTextFunction);
    addExtParam (paramNoiseLevel,      "Noise Level",        "Noise",       "", {    0.0f,   1.0f, 0.0f, 1.0f }, 0.0f, 0.0f, percentTextFunction);
    addExtParam (paramNoiseShort,      "Noise Short",        "Short",       "", {    0.0f,   1.0f, 1.0f, 1.0f }, 0.0f, 0.0f, onOffTextFunction);
    addExtParam (paramTriangleLevel,   "Triangle Level",     "Triangle",    "", {    0.0f,   1.0f, 1.0f, 1.0f }, 0.0f, 0.0f, onOffTextFunction);
    addExtParam (paramOutput,          "Output",             "Output",      "", {    0.0f,   1.0f, 0.0f, 1.0f }, 1.0f, 0.0f, percentTextFunction);
    addExtParam (paramPulse1Tune,      "Pulse 1 Tune",       "Tune",        "", {  -48.0f,  48.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramPulse1TuneFine,  "Pulse 1 Tune Fine",  "Fine",        "", { -100.0f, 100.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramPulse2Tune,      "Pulse 2 Tune",       "Tune",        "", {  -48.0f,  48.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramPulse2TuneFine,  "Pulse 2 Tune Fine",  "Fine",        "", { -100.0f, 100.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramTriangleTune,    "Triangle Tune",      "Tune",        "", {  -48.0f,  48.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramTriangleTuneFine,"Triangle Tune Fine", "Fine",        "", { -100.0f, 100.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramPulse1Sweep,     "Pulse 1 Sweep",      "Sweep",       "", {   -8.0f,   8.0f, 1.0f, 1.0f }, 0.0f, 0.0f, sweepTextFunction);
    addExtParam (paramPulse1Shift,     "Pulse 1 Shift",      "Shift",       "", {    0.0f,   7.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);
    addExtParam (paramPulse2Sweep,     "Pulse 2 Sweep",      "Sweep",       "", {   -8.0f,   8.0f, 1.0f, 1.0f }, 0.0f, 0.0f, sweepTextFunction);
    addExtParam (paramPulse2Shift,     "Pulse 2 Shift",      "Shift",       "", {    0.0f,   7.0f, 1.0f, 1.0f }, 0.0f, 0.0f, intTextFunction);

    init();
}

RP2A03AudioProcessor::~RP2A03AudioProcessor()
{
}

//==============================================================================
void RP2A03AudioProcessor::prepareToPlay (double sampleRate, int)
{
    apu.sample_rate (long (sampleRate));
    apu.write_register (0x4015, 0x0F);
    
    outputSmoothed.reset (sampleRate, 0.05);
}

void RP2A03AudioProcessor::releaseResources()
{
}

void RP2A03AudioProcessor::runUntil (int& done, juce::AudioSampleBuffer& buffer, int pos)
{
    int todo = std::min (pos, buffer.getNumSamples()) - done;
    
    while (todo > 0)
    {
        if (apu.samples_avail() == 0)
            apu.step();
        
        Simple_Apu::sample_t out[1024];
		int count = int (apu.read_samples (out, std::min ({todo, int (apu.samples_avail()), 1024})));
        
        float* data = buffer.getWritePointer (0, done);
        for (int i = 0; i < count; i++)
            data[i] = out[i] / 32768.0f;
        
        done += count;
        todo -= count;
    }

}

void RP2A03AudioProcessor::processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midi)
{
	buffer.clear();
    outputSmoothed.setTargetValue (getParameter (paramOutput)->getUserValue());

    int done = 0;
    runOsc (lastNote, false);
    runUntil (done, buffer, 0);
    
    for (auto itr : midi)
    {
        auto msg = itr.getMessage();
        int pos = itr.samplePosition;
        
        runUntil (done, buffer, pos);
        
        if (msg.isNoteOn())
        {
            noteQueue.add (msg.getNoteNumber());
            velocity = msg.getVelocity();
        }
        else if (msg.isNoteOff())
        {
            noteQueue.removeFirstMatchingValue (msg.getNoteNumber());
        }
        else if (msg.isAllNotesOff())
        {
            noteQueue.clear();
        }
        
        int curNote = noteQueue.size() > 0 ? noteQueue.getLast() : -1;
        
        if (curNote != lastNote)
        {
            runOsc (curNote, curNote != lastNote);
            lastNote = curNote;
        }
    }
    
    int numSamples = buffer.getNumSamples();
    runUntil (done, buffer, numSamples);
    
    float* data = buffer.getWritePointer (0);
    for (int i = 0; i < numSamples; i++)
        data[i] *= outputSmoothed.getNextValue();

    if (fifo.getFreeSpace() >= numSamples)
        fifo.writeMono (data, numSamples);
}

void RP2A03AudioProcessor::runOsc (int curNote, bool trigger)
{
    const float p1Level = parameterValue (paramPulse1Level);
    const int p1Duty    = parameterIntValue (paramPulse1DutyCycle);
    const int p1Tune    = parameterIntValue (paramPulse1Tune);
    const int p1Fine    = parameterIntValue (paramPulse1TuneFine);
    const float p2Level = parameterValue (paramPulse2Level);
    const int p2Duty    = parameterIntValue (paramPulse2DutyCycle);
    const int p2Tune    = parameterIntValue (paramPulse2Tune);
    const int p2Fine    = parameterIntValue (paramPulse2TuneFine);
    const float tLevel  = parameterValue (paramTriangleLevel);
    const int tTune     = parameterIntValue (paramTriangleTune);
    const int tFine     = parameterIntValue (paramTriangleTuneFine);
    const float nLevel  = parameterValue (paramNoiseLevel);
    const bool nShort   = parameterValue (paramNoiseShort) > 0.0f;
    const int p1Sweep   = parameterIntValue (paramPulse1Sweep);
    const int p1Shift   = parameterIntValue (paramPulse1Shift);
    const int p2Sweep   = parameterIntValue (paramPulse2Sweep);
    const int p2Shift   = parameterIntValue (paramPulse2Shift);
    
    int v = curNote == -1 ? 0 : velocity;
    
    // Pulse 1
    int period1 = int (111860.8 / gin::getMidiNoteInHertz (curNote + p1Tune + p1Fine / 100.0) - 1);
    if (period1 <= 0x7ff && curNote != -1)
    {
        writeReg (0x4000, (p1Duty << 6) | 0x30 | int (p1Level * v / 127.0 * 0xF), trigger);

        if (p1Sweep != 0)
            writeReg (0x4001,
                      (p1Sweep != 0 ? 0x80 : 0x00) |
                      ((abs (p1Sweep) - 1) << 4) |
                      (((p1Sweep < 0) ? 0 : 1) << 3) |
                      p1Shift, trigger);
        else
            writeReg (0x4001, 0x00, trigger);
        
        writeReg (0x4003, (period1 >> 8) & 0x7, trigger);
        writeReg (0x4002, period1 & 0xFF, trigger);
    }
    else
    {
        writeReg (0x4000, (p1Duty << 6) | 0x30, trigger);
    }

    // Pulse 2
    int period2 = int (111860.8 / gin::getMidiNoteInHertz (curNote + p2Tune + p2Fine / 100.0) - 1);
    if (period2 < 0x7ff && curNote != -1)
    {
        writeReg (0x4004, (p2Duty << 6) | 0x30 | int (p2Level * v / 127.0 * 0xF), trigger);

        if (p2Sweep != 0)
            writeReg (0x4005,
                      (p2Sweep != 0 ? 0x80 : 0x00) |
                      ((abs (p2Sweep) - 1) << 4) |
                      (((p2Sweep < 0) ? 0 : 1) << 3) |
                      p2Shift, trigger);
        else
            writeReg (0x4005, 0x00, trigger);
        
        writeReg (0x4006, period2 & 0xFF, trigger);
        writeReg (0x4007, (period2 >> 8) & 0x7, trigger);
    }
    else
    {
        writeReg (0x4004, (p2Duty << 6) | 0x30, trigger);
    }
    
    // Triangle
    int period3 = int (tLevel == 1.0f ? 111860.8 / gin::getMidiNoteInHertz (curNote + tTune + tFine / 100.0) * 2 - 1 : 0);
    if (period3 > 0 && period3 <= 0x7ff && curNote != -1)
    {
        writeReg (0x4008, 0xFF, trigger);
        writeReg (0x400A, period3 & 0xFF, trigger);
        writeReg (0x400B, (period3 >> 8) & 0x7, trigger);
    }
    else
    {
        writeReg (0x4008, 0x00, trigger);
    }
    
    // Noise
    if (curNote != -1)
    {
        writeReg (0x400C, 0x30 | int (nLevel * v / 127.0 * 0xF), trigger);
        writeReg (0x400E, (nShort ? 0x80 : 0x00) | (curNote % 16), trigger);
        writeReg (0x400F, 0xFF, trigger);
    }
    else
    {
        writeReg (0x400C, 0x30, trigger);
    }
}

void RP2A03AudioProcessor::writeReg (int reg, int value, bool force)
{
    auto itr = regCache.find (reg);
    if (itr == regCache.end() || itr->second != value || force)
    {
        regCache[reg] = value;
        apu.write_register (reg, value);
    }
}

//==============================================================================
bool RP2A03AudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* RP2A03AudioProcessor::createEditor()
{
    return new RP2A03AudioProcessorEditor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RP2A03AudioProcessor();
}
