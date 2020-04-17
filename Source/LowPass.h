/*
  ==============================================================================

    LowPass.h
    Created: 17 Apr 2020 10:45:57am
    Author:  Carlos Segovia

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
 */
class LowPass    :  public Component,
public Slider::Listener,
public Button::Listener
{
public:
    LowPass(EqSoABandPassAudioProcessor&);
    ~LowPass();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button* button) override;
    void on();
    void off();
    
private:
    
    Slider cutOff;
    Slider Q;
    
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
    
    
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowPass)
};

