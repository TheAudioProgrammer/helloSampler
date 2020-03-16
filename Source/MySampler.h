/*
  ==============================================================================

    MySampler.h
    Created: 14 Mar 2020 1:41:28pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MySampler : public Synthesiser
{
public:
    void handleMidiEvent (const MidiMessage &m) override
    {
        const int channel = m.getChannel();
        
        if (m.isNoteOn())
        {
            noteOn (channel, m.getNoteNumber(), m.getFloatVelocity());
            mADSR.noteOn();
        }
        else if (m.isNoteOff())
        {
            noteOff (channel, m.getNoteNumber(), m.getFloatVelocity(), true);
            mADSR.noteOff();
        }
    }

    //public methods
    
    void prepareToPlay (int sampleRate)
    {
        setCurrentPlaybackSampleRate (sampleRate);
        mADSR.setSampleRate (sampleRate);
        mADSR.setParameters (mADSRParams);
    }
    
    void getNextAudioBlock (AudioBuffer<float>& buffer, const MidiBuffer& midiMessages, int startSample, int numSamples)
    {
        renderNextBlock (buffer, midiMessages, startSample, numSamples);
        mADSR.applyEnvelopeToBuffer (buffer, startSample, numSamples);
    }
    
    //Access methods
    ADSR& getADSR() { return mADSR; }
    ADSR::Parameters& getADSRParams() { return mADSRParams; }
    
private:
    ADSR mADSR;
    ADSR::Parameters mADSRParams;
};
