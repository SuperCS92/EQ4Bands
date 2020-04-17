/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EqSoABandPassAudioProcessorEditor::EqSoABandPassAudioProcessorEditor (EqSoABandPassAudioProcessor& p)
    : AudioProcessorEditor (&p), lowPassGui(p),highPassGui(p), lowMidGui(p), midHighgui(p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 250);
    
    addAndMakeVisible(&lowPassGui);
    addAndMakeVisible(&highPassGui);
    addAndMakeVisible(&lowMidGui);
    addAndMakeVisible(&midHighgui);
}

EqSoABandPassAudioProcessorEditor::~EqSoABandPassAudioProcessorEditor()
{
}

//==============================================================================
void EqSoABandPassAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkgrey); 
}

void EqSoABandPassAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    lowPassGui.setBounds(area.removeFromLeft(100).reduced(10));
    highPassGui.setBounds(area.removeFromRight(100).reduced(10));
    lowMidGui.setBounds(area.reduced(10));
    midHighgui.setBounds(area.removeFromRight(155).reduced(10));
    
}
