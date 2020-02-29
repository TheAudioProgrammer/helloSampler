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
    : AudioProcessorEditor (&p), processor (p)
{
    mLoadButton.onClick = [&]() { processor.loadFile(); };
    addAndMakeVisible (mLoadButton);
    
    setSize (200, 200);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void HelloSamplerAudioProcessorEditor::resized()
{
    mLoadButton.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}
