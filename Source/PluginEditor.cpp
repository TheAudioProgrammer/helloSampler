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
    g.fillAll (Colours::black);
    
    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    if (processor.getNumSamplerSounds() > 0)
    {
        g.fillAll (Colours::red);
        g.drawText ("Sound Loaded", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, Justification::centred);
    }
    else
    {
        g.drawText ("Load a Sound", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, Justification::centred);
    }
}

void HelloSamplerAudioProcessorEditor::resized()
{
    //mLoadButton.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}

bool HelloSamplerAudioProcessorEditor::isInterestedInFileDrag (const StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains (".wav") || file.contains (".mp3") || file.contains (".aif"))
        {
            return true;
        }
    }
    
    return false;
}

void HelloSamplerAudioProcessorEditor::filesDropped (const StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag (file))
        {
            processor.loadFile (file);
        }
    }
    
    repaint();
}
