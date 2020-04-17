/*
  ==============================================================================

    MidHigh.h
    Created: 17 Apr 2020 10:45:22am
    Author:  Carlos Segovia

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
 */
class MidHigh    : public Component,
public Slider::Listener,
public TextButton::Listener
{
public:
    MidHigh(EqSoABandPassAudioProcessor&);
    ~MidHigh();
    
    void paint (Graphics&) override;
    void resized() override;
    
    //SLiders related function's
    void sliderValueChanged(Slider*) override;
    
    //State Button related function's
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidHigh)
};

