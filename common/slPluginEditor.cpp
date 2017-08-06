#include "slPluginEditor.h"

slAudioProcessorEditor::slAudioProcessorEditor (slProcessor& p, int cx_, int cy_) noexcept
  : AudioProcessorEditor (p), cx (cx_), cy (cy_)
{
    setLookAndFeel (&lf);
}

void slAudioProcessorEditor::paint (Graphics& g)
{
    if (slLookAndFeel* lf = dynamic_cast<slLookAndFeel*> (&getLookAndFeel()))
    {
        g.fillAll (Colours::black);
    }
}

void slAudioProcessorEditor::resized()
{
    
}

Rectangle<int> slAudioProcessorEditor::getControlsArea()
{
    return getLocalBounds();
}

Rectangle<int> slAudioProcessorEditor::getGridArea (int x, int y, int w, int h)
{
    return Rectangle<int> (inset + x * cx, headerHeight + y * cy + inset, w * cx, h * cy);
}

ParamComponent* slAudioProcessorEditor::componentForId (const String& uid)
{
    for (auto* c : controls)
    {
        if (c->getUid() == uid)
            return c;
    }
    return nullptr;
}

void slAudioProcessorEditor::setGridSize (int x, int y)
{
    setSize (x * cx + inset * 2, y * cy + inset * 2 + headerHeight);
}
