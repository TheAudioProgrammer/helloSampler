/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessor::HelloSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS (*this, nullptr, "Parameters", createParameters())
#endif
{
    mFormatManager.registerBasicFormats();
    mAPVTS.state.addListener (this);
    
    for (int i = 0; i < mNumVoices; i++)
    {
        mSampler.addVoice (new SamplerVoice());
    }
}

HelloSamplerAudioProcessor::~HelloSamplerAudioProcessor()
{
    mAPVTS.state.removeListener (this);
}

//==============================================================================
const String HelloSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HelloSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HelloSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HelloSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HelloSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HelloSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HelloSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HelloSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String HelloSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void HelloSamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HelloSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampler.setCurrentPlaybackSampleRate (sampleRate);
    updateADSR();
}

void HelloSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void HelloSamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (mShouldUpdate)
    {
        updateADSR();
    }
    
    MidiMessage m;
    MidiBuffer::Iterator it { midiMessages };
    int sample;
    
    while (it.getNextEvent (m, sample))
    {
        if (m.isNoteOn())
            mIsNotePlayed = true;
        else if (m.isNoteOff())
            mIsNotePlayed = false;
    }
    
    mSampleCount = mIsNotePlayed ? mSampleCount += buffer.getNumSamples() : 0;

    mSampler.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool HelloSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HelloSamplerAudioProcessor::createEditor()
{
    return new HelloSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void HelloSamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HelloSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void HelloSamplerAudioProcessor::loadFile()
{
    mSampler.clearSounds();
    
    FileChooser chooser { "Please load a file" };
    
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        // the reader can be a local variable here since it's not needed by the SamplerSound after this
        std::unique_ptr<AudioFormatReader> reader{ mFormatManager.createReaderFor(file) };
        if (reader)
        {
            BigInteger range;
            range.setRange(0, 128, true);
            mSampler.addSound(new SamplerSound("Sample", *reader, range, 60, 0.1, 0.1, 10.0));
        }
        
    }
    
    
}

void HelloSamplerAudioProcessor::loadFile (const String& path)
{
    mSampler.clearSounds();
    
    auto file = File (path);
    // the reader can be a local variable here since it's not needed by the other classes after this
    std::unique_ptr<AudioFormatReader> reader{ mFormatManager.createReaderFor(file) };
    if (reader)
    {
        BigInteger range;
        range.setRange(0, 128, true);
        mSampler.addSound(new SamplerSound("Sample", *reader, range, 60, 0.1, 0.1, 10.0));
        updateADSR();
    }
    
}

AudioBuffer<float>& HelloSamplerAudioProcessor::getWaveForm()
{
    // get the last added synth sound as a SamplerSound*
    auto sound = dynamic_cast<SamplerSound*>(mSampler.getSound(mSampler.getNumSounds() - 1).get());
    if (sound)
    {
        return *sound->getAudioData();
    }
}

void HelloSamplerAudioProcessor::updateADSR()
{
    mShouldUpdate = false;
    
    mADSRParams.attack = mAPVTS.getRawParameterValue ("ATTACK")->load();
    mADSRParams.decay = mAPVTS.getRawParameterValue ("DECAY")->load();
    mADSRParams.sustain = mAPVTS.getRawParameterValue ("SUSTAIN")->load();
    mADSRParams.release = mAPVTS.getRawParameterValue ("RELEASE")->load();
    
    for (int i = 0; i < mSampler.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<SamplerSound*>(mSampler.getSound(i).get()))
        {
            sound->setEnvelopeParameters (mADSRParams);
        }
    }
}

AudioProcessorValueTreeState::ParameterLayout HelloSamplerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.0f));
    params.push_back (std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 5.0f, 2.0f));
    params.push_back (std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    params.push_back (std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 5.0f, 0.0f));
    
    return { params.begin(), params.end() };
}

void HelloSamplerAudioProcessor::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    mShouldUpdate = true;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloSamplerAudioProcessor();
}
