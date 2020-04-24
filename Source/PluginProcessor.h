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
class HelloSamplerAudioProcessor  : public AudioProcessor,
                                    public ValueTree::Listener
{
public:
    //==============================================================================
    HelloSamplerAudioProcessor();
    ~HelloSamplerAudioProcessor();

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
    
    void loadFile();
    void loadFile (const String& path);
    
    int getNumSamplerSounds() { return mSampler.getNumSounds(); }
    AudioBuffer<float>& getWaveForm() { return mWaveForm; }
    
    void updateADSR();
    ADSR::Parameters& getADSRParams() { return mADSRParams; }
    
    AudioProcessorValueTreeState& getValueTree() { return mAPVTS; }
    std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; }
    std::atomic<int>& getSampleCount() { return mSampleCount; }

private:
    Synthesiser mSampler;
    const int mNumVoices { 3 };
    AudioBuffer<float> mWaveForm;
    
    ADSR::Parameters mADSRParams;
    
    AudioFormatManager mFormatManager;
    
    
    AudioProcessorValueTreeState mAPVTS;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;
    
    std::atomic<bool> mShouldUpdate { false };
    std::atomic<bool> mIsNotePlayed { false };
    std::atomic<int> mSampleCount { 0 };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloSamplerAudioProcessor)
};
