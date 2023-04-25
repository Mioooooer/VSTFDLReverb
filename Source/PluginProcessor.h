/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyDSP.h"
#include "WaveTable.h"
#include <vector>

//==============================================================================
/**
*/
class FDLReverbAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FDLReverbAudioProcessor();
    ~FDLReverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;


    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================


private:
    juce::AudioProcessorValueTreeState parameters;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    std::atomic<float>* mixParameter = nullptr;
    int waveTableIndex = 0;
    int currentTableIndex = 0;
    WaveTable::AllWaveTable myWaveTable;
    juce::AudioSampleBuffer filterBuffer;
    juce::AudioSampleBuffer tempBuffer;
    DSP::MyUtils myUtils;
    std::vector<std::vector<double> > toProcess;
    std::vector<std::vector<double> > toPass;
    double currentSampleRate;
    std::vector<DSP::MyUtils> reverbVector;
    /*
    using FilterArray = std::array<DSP::BandPassFilter, 48>;
    std::vector<FilterArray> filterMatrix;
    std::array<float, 48> freqList{
        185.00f,
        196.00f,
        207.65f,
        220.00f,
        233.08f,
        246.94f,
        261.63f,
        277.18f,
        293.66f,
        311.13f,
        329.63f,
        349.23f,
        369.99f,
        392.00f,
        415.30f,
        440.00f,
        466.16f,
        493.88f,
        523.25f,
        554.37f,
        587.33f,
        622.25f,
        659.25f,
        698.46f,
        739.99f,
        783.99f,
        830.61f,
        880.00f,
        932.33f,
        987.77f,
        1046.50f,
        1108.73f,
        1174.66f,
        1244.51f,
        1318.51f,
        1396.91f,
        1479.98f,
        1567.98f,
        1661.22f,
        1760.00f,
        1864.66f,
        1975.53f,
        2093.00f,
        2217.46f,
        2349.32f,
        2489.02f,
        2637.02f,
        2793.83f,
    };
    */
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FDLReverbAudioProcessor)
};
