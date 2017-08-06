#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "slUtil.h"

//==============================================================================
void applyGain (AudioSampleBuffer& buffer, LinearSmoothedValue<float>& gain);

