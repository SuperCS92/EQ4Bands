/*
  ==============================================================================

    LowPass.cpp
    Created: 17 Apr 2020 10:45:57am
    Author:  Carlos Segovia

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LowPass.h"

//==============================================================================
LowPass::LowPass(EqSoABandPassAudioProcessor &p): processor (p)
{
    
    
    setSize(200, 200);
    
    cutOff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutOff.setRange(20.0, 20000.0);
    cutOff.setValue(20000.0);
    cutOff.setDoubleClickReturnValue(true, 20000.0f);
    cutOff.setSkewFactorFromMidPoint(1500.0);
    cutOff.setNumDecimalPlacesToDisplay (0);
    cutOff.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    cutOff.setTextBoxIsEditable(true);
    cutOff.setTextValueSuffix( "Hz");
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

LowPass::~LowPass()
{
}

void LowPass::paint (Graphics& g)
{
    
    
    Rectangle<int> titleArea (5,5,getWidth(),20);
    //g.fillAll(Colours::black);
    g.setColour(Colours::lightgrey);
    g.drawText( "Low Pass",titleArea,Justification::centredTop);
    
    Rectangle<float> area(10,25,65,200);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
    
    //g.fillRect(titleArea);
    //g.drawText( "Low Pass",10,10,20,20, Justification::centredTop);
    
    /*
     Rectangle<int> rect = getLocalBounds().reduced(10);
     g.fillAll(Colours::pink);
     g.setColour(Colours::aliceblue);
     g.drawRect( rect, 10);
     //g.setColour(Colours::pink);
     g.fillRect(rect);
     g.setColour(Colours::black);
     */
    
    
}

void LowPass::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    
    cutOff.setBounds(area.removeFromTop(130).reduced(10));
    Q.setBounds(area.removeFromTop(80).reduced(13));
    //stateButton.setBounds(area.removeFromTop(30));
    stateButton.setBounds(23, 203, 40, 20);
    
    
}

void LowPass::sliderValueChanged(Slider* slider)
{
    if(slider == &cutOff)
    {
        processor.LPfreq = cutOff.getValue();
    }
    
    if(slider == &Q)
    {
        processor.LPQ = Q.getValue();
    }
    
    
}

void LowPass::buttonClicked(Button* button)
{
    if(button == &stateButton)
    {
        if(state == State::Off)
            stateButton.onClick = [this](){  on();};
        else if(state == State::On)
            stateButton.onClick = [this](){ off();} ;
    }
}

void LowPass::on()
{
    state = State::On;
    stateButton.setToggleState(true, NotificationType::dontSendNotification);
    processor.isOn = true;
}

void LowPass::off()
{
    state = State::Off;
    stateButton.setToggleState(false, NotificationType::dontSendNotification);
    processor.isOn = false;
}


