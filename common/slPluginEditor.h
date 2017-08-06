#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "slProcessor.h"
#include "slComponents.h"
#include "slLookAndFeel.h"

//==============================================================================
class slAudioProcessorEditor : public AudioProcessorEditor
{
public:
    slAudioProcessorEditor (slProcessor&, int cx = 100, int cy = 100) noexcept;
    
protected:
    Rectangle<int> getControlsArea();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    Rectangle<int> getGridArea (int x, int y, int w = 1, int h = 1);
    
    const int cx;
    const int cy;
    
    OwnedArray<ParamComponent> controls;

    ParamComponent* componentForId (const String& uid);
    
    slLookAndFeel lf;
};
