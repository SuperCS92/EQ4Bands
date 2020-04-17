/*
  ==============================================================================

    HighPass.cpp
    Created: 17 Apr 2020 10:45:46am
    Author:  Carlos Segovia

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HighPass.h"

//==============================================================================
HighPass::HighPass(EqSoABandPassAudioProcessor &p): processor (p)
{
    setSize(200, 200);
    
    cutOff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutOff.setRange(20.0, 20000.0);
    cutOff.setSkewFactorFromMidPoint(1500.0);
    cutOff.setValue(20.0);
    cutOff.setDoubleClickReturnValue(true, 20.0f);
    cutOff.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    cutOff.setTextBoxIsEditable(true);
    cutOff.setTextValueSuffix( "Hz");
    cutOff.setNumDecimalPlacesToDisplay (0);
    cutOff.addListener(this);
    addAndMakeVisible(cutOff);
    
    
    Q.setSliderStyle(Slider::SliderStyle::IncDecButtons);
    Q.setRange(6.0,12.0, 6.0);
    Q.setValue(6.0);
    Q.setTextBoxStyle(Slider::TextBoxBelow, true, 55, 20);
    Q.setTextValueSuffix( "dB/Oct");
    Q.addListener(this);
    addAndMakeVisible(Q);
    
    
    stateButton.setToggleState(false, NotificationType::dontSendNotification);
    stateButton.addListener(this);
    stateButton.setColour(TextButton::ColourIds::buttonColourId, Colours::red);
    stateButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::limegreen);
    addAndMakeVisible(&stateButton);
}

HighPass::~HighPass()
{
}

void HighPass::paint (Graphics& g)
{
    Rectangle<int> titleArea (5,5,getWidth(),20);
    //g.fillAll(Colours::black);
    g.setColour(Colours::lightgrey);
    g.drawText( "High Pass",titleArea,Justification::centredTop);
    
    Rectangle<float> area(10,25,65,200);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void HighPass::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    
    cutOff.setBounds(area.removeFromTop(130).reduced(10));
    Q.setBounds(area.removeFromTop(80).reduced(13));
    stateButton.setBounds(23, 203, 40, 20);
}


void HighPass::sliderValueChanged(Slider* slider)
{
    if(slider == &cutOff)
    {
        processor.HPfreq = cutOff.getValue();
    }
    
    if(slider == &Q)
    {
        processor.HPQ = Q.getValue();
    }
    
    
}

void HighPass::buttonClicked(Button* button)
{
    if(button == &stateButton)
    {
        if(state == State::Off)
            stateButton.onClick = [this](){  on();};
        else if(state == State::On)
            stateButton.onClick = [this](){ off();} ;
    }
}

void HighPass::on()
{
    state = State::On;
    stateButton.setToggleState(true, NotificationType::dontSendNotification);
    processor.HPisOn = true;
}

void HighPass::off()
{
    state = State::Off;
    stateButton.setToggleState(false, NotificationType::dontSendNotification);
    processor.HPisOn = false;
}

