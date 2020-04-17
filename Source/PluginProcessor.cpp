/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EqSoABandPassAudioProcessor::EqSoABandPassAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), LPFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.5f)),
HPFilter(dsp::IIR::Coefficients<float>::makeHighPass(44100, 20.0f, 0.5f)),
LowMidFilter(dsp::IIR::Coefficients<float>::makePeakFilter(44100, 1000.0f,1.0f, 1.0f)),
HighMidFilter(dsp::IIR::Coefficients<float>::makePeakFilter(44100, 8000.0f,1.0f, 1.0f))

#endif
{
}

EqSoABandPassAudioProcessor::~EqSoABandPassAudioProcessor()
{
}

//==============================================================================
const String EqSoABandPassAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EqSoABandPassAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EqSoABandPassAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EqSoABandPassAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EqSoABandPassAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EqSoABandPassAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EqSoABandPassAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EqSoABandPassAudioProcessor::setCurrentProgram (int index)
{
}

const String EqSoABandPassAudioProcessor::getProgramName (int index)
{
    return {};
}

void EqSoABandPassAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EqSoABandPassAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    //Parameters of Low Pass Filter//
    LPFilter.prepare(spec);
    LPFilter.reset();
    updateFilterLowPass();
    
    //Parameters of High Pass Filter//
    HPFilter.prepare(spec);
    HPFilter.reset();
    updateFilterHighPass();
    
    //Parameters of Low Mid Filter//
    LowMidFilter.prepare(spec);
    LowMidFilter.reset();
    updateFilterLowMid();
    
    //Parameters of Low Mid Filter//
    HighMidFilter.prepare(spec);
    HighMidFilter.reset();
    updateFilterHighMid();
    
}

void EqSoABandPassAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EqSoABandPassAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void EqSoABandPassAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    

    

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
   
    dsp::AudioBlock<float>block(buffer);

    if(isOn)            //Check first if Filter is ON
    {
        updateFilterLowPass();
        LPFilter.process(dsp::ProcessContextReplacing<float> (block));
    }
    
    if(HPisOn)          //Check first if Filter is ON
    {
        updateFilterHighPass();
        HPFilter.process(dsp::ProcessContextReplacing<float> (block));
    }
    
    if(LMisOn)          //Check first if Filter is ON
    {
        updateFilterLowMid();
        LowMidFilter.process(dsp::ProcessContextReplacing<float>(block));
    }
    
    if(HMisOn)          //Check first if Filter is ON
    {
        updateFilterHighMid();
        HighMidFilter.process(dsp::ProcessContextReplacing<float>(block));
    }
}

//==============================================================================
bool EqSoABandPassAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EqSoABandPassAudioProcessor::createEditor()
{
    return new EqSoABandPassAudioProcessorEditor (*this);
}

//==============================================================================
void EqSoABandPassAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EqSoABandPassAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EqSoABandPassAudioProcessor();
}

void EqSoABandPassAudioProcessor::updateFilterLowPass()
{
    *LPFilter.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, LPfreq, (LPQ/12.0) );
}


void EqSoABandPassAudioProcessor::updateFilterHighPass()
{
    *HPFilter.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, HPfreq, (HPQ/12.0) );
}

void EqSoABandPassAudioProcessor:: updateFilterLowMid()
{
    *LowMidFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, LMfreq, LMQ,LMGain);
}

void EqSoABandPassAudioProcessor:: updateFilterHighMid()
{
    *HighMidFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, HMfreq, HMQ,HMGain);
}

