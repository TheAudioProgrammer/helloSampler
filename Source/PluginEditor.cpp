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
    auto tapImage = ImageCache::getFromMemory (BinaryData::TAP_png, BinaryData::TAP_pngSize);
    
    if (! tapImage.isNull())
        mImageComponent.setImage (tapImage, RectanglePlacement::stretchToFit);
    else
        jassert (! tapImage.isNull());
    
    addAndMakeVisible (mWaveThumbnail);
    addAndMakeVisible (mADSR);
    addAndMakeVisible (mImageComponent);
    
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
    mImageComponent.setBoundsRelative (0.0f, 0.0f, 0.5f, 0.25f);
}

void HelloSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}



