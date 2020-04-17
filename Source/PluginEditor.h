/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LowMid.h"
#include "LowPass.h"
#include "HighPass.h"
#include "MidHigh.h"

//==============================================================================
/**
*/
class EqSoABandPassAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    EqSoABandPassAudioProcessorEditor (EqSoABandPassAudioProcessor&);
    ~EqSoABandPassAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    LowPass lowPassGui;
    HighPass highPassGui;
    LowMid lowMidGui;
    MidHigh midHighgui;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqSoABandPassAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqSoABandPassAudioProcessorEditor)
};
