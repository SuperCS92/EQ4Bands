/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class EqSoABandPassAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EqSoABandPassAudioProcessor();
    ~EqSoABandPassAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    //==============================================================================
    void updateFilterLowPass();
    void updateFilterHighPass();
    void updateFilterLowMid();
    void updateFilterHighMid();
    
    //Low Pass Filter Parameters//
    float LPfreq{20000.0f};         //Frequency
    float LPQ{6.0f};            //Q Factor
    bool isOn = false;          //Bypass
    
    //High Pass Filter Parameters//
    float HPfreq{20.0f};         //Frequency
    float HPQ{6.0f};            //Q Factor
    bool HPisOn = false;          //Bypass
    
    //LM Filter Pararameters
    bool LMisOn = false;         //Bypass
    float LMfreq {1000.0f};      //Frequency
    float LMQ {1.0f};            //Q Factor
    float LMGain {1.0f};         //Gain
    
    //HM Filter Pararameters
    bool HMisOn = false;         //Bypass
    float HMfreq {1000.0f};      //Frequency
    float HMQ {1.0f};            //Q Factor
    float HMGain {1.0f};         //Gain
    
    
    
private:
    
    // Low Pass Filter Parameters //
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>,
    dsp::IIR::Coefficients<float>> LPFilter;
    
    // High Pass Filter Parameters //
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>,
    dsp::IIR::Coefficients<float>> HPFilter;
    
    // Low Mid Filter Parameters //
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>,
    dsp::IIR::Coefficients<float>> LowMidFilter;
    
    // High Mid Filter Parameters //
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>,
    dsp::IIR::Coefficients<float>> HighMidFilter;
    
    double lastSampleRate;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqSoABandPassAudioProcessor)
};
