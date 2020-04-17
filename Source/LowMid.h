/*
  ==============================================================================

    LowMid.h
    Created: 16 Apr 2020 11:56:23am
    Author:  Carlos Segovia

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LowMid    : public Component,
public Slider::Listener,
public TextButton::Listener
{
public:
    LowMid(EqSoABandPassAudioProcessor&);
    ~LowMid();

    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button* button) override;
    void on();
    void off();

   
private:
    
    Slider freq;
    Slider Q;
    Slider gain;
    
    enum class State
    {
        On,
        Off
    };
    
    State state{State::Off};
    TextButton stateButton {"I/O"};
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqSoABandPassAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowMid)
};
