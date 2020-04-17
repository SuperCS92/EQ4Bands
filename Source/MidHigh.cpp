/*
  ==============================================================================

    MidHigh.cpp
    Created: 17 Apr 2020 10:45:22am
    Author:  Carlos Segovia

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MidHigh.h"

//==============================================================================
MidHigh::MidHigh(EqSoABandPassAudioProcessor &p): processor (p)
{
    setSize(100, 100);
    
    freq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freq.setRange(50.0, 16000.0);
    freq.setSkewFactorFromMidPoint(2000.0);
    freq.setValue(8000.0);
    freq.setDoubleClickReturnValue(true, 8000.0f);
    freq.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    freq.setTextBoxIsEditable(true);
    freq.setTextValueSuffix( "Hz");
    freq.setNumDecimalPlacesToDisplay (0);
    freq.addListener(this);
    addAndMakeVisible(freq);
    
    Q.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    Q.setRange(0.1, 6.0);
    Q.setValue(1.0f);
    Q.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
    Q.setTextBoxIsEditable(true);
    Q.setTextValueSuffix( "Q");
    Q.setNumDecimalPlacesToDisplay (1);
    Q.setDoubleClickReturnValue(true, 1.0f);
    Q.addListener(this);
    addAndMakeVisible(Q);
    
    gain.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gain.setRange(-18.0f, 18.0f);
    gain.setValue(0.0f);
    gain.setTextBoxStyle(Slider::TextBoxBelow, true, 46, 15);
    gain.setTextBoxIsEditable(true);
    gain.setTextValueSuffix( "dB");
    gain.setNumDecimalPlacesToDisplay (1);
    gain.setDoubleClickReturnValue(true, 0.0f);
    gain.addListener(this);
    addAndMakeVisible(gain);
    
    stateButton.setToggleState(false, NotificationType::dontSendNotification);
    stateButton.addListener(this);
    stateButton.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    stateButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::limegreen);
    addAndMakeVisible(&stateButton);
}

MidHigh::~MidHigh()
{
}

void MidHigh::paint (Graphics& g)
{
    //g.fillAll(Colours::black);
    Rectangle<int> titleArea (5,5,110,15);
    
    g.setColour(Colours::lightgrey);
    g.drawText( "Mid High",titleArea,Justification::centredTop);
    
    
    Rectangle<float> area(5,25,120,200);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void MidHigh::resized()
{
    freq.setBounds(15, 25, 100, 100);
    Q.setBounds(0, 125, 70, 70);
    gain.setBounds(60, 150, 70, 70);
    stateButton.setBounds(15, 200, 40, 20);
}

void MidHigh::sliderValueChanged(Slider* slider)
{
    if(slider == &freq)
    {
        processor.HMfreq = freq.getValue();
    }
    
    if(slider == &Q)
    {
        processor.HMQ = Q.getValue();
    }
    if(slider == &gain)
    {
        processor.HMGain = Decibels::decibelsToGain(gain.getValue());
    }
    
    
}

void MidHigh::buttonClicked(Button* button)
{
    if(button == &stateButton)
    {
        if(state == State::Off)
            stateButton.onClick = [this](){  on();};
        else if(state == State::On)
            stateButton.onClick = [this](){ off();} ;
    }
}

void MidHigh::on()
{
    state = State::On;
    stateButton.setToggleState(true, NotificationType::dontSendNotification);
    processor.HMisOn = true;
}

void MidHigh::off()
{
    state = State::Off;
    stateButton.setToggleState(false, NotificationType::dontSendNotification);
    processor.HMisOn = false;
}


