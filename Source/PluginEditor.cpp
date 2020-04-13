/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail (p), mADSR (p), processor (p)
{
    addAndMakeVisible (mWaveThumbnail);
    addAndMakeVisible (mADSR);
    
    startTimerHz (30);
    
    setSize (600, 400);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void HelloSamplerAudioProcessorEditor::resized()
{
    mWaveThumbnail.setBoundsRelative (0.0f, 0.25f, 1.0f, 0.5);
    mADSR.setBoundsRelative (0.0f, 0.75f, 1.0f, 0.25f);
}

void HelloSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}



