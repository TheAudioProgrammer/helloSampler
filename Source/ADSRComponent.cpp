/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 14 Mar 2020 2:52:49pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent (HelloSamplerAudioProcessor& p) : processor (p)
{
    mAttackSlider.setRange (0.1f, 2.0f, 0.01f);
    mAttackSlider.setValue (0.1f);
    mAttackSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 35, 20);
    addAndMakeVisible (mAttackSlider);
    mAttackSlider.addListener (this);
    
    mDecaySlider.setRange (0.1f, 1.0f, 0.01f);
    mDecaySlider.setValue (0.1f);
    mDecaySlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, 35, 20);
    addAndMakeVisible (mDecaySlider);
    mDecaySlider.addListener (this);
    
    mSustainSlider.setRange (0.1f, 1.0f, 0.01f);
    mSustainSlider.setValue (1.0f);
    mSustainSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 35, 20);
    addAndMakeVisible (mSustainSlider);
    mSustainSlider.addListener (this);
    
    mReleaseSlider.setRange (0.1f, 5.0f, 0.01f);
    mReleaseSlider.setValue (0.4f);
    mReleaseSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 35, 20);
    addAndMakeVisible (mReleaseSlider);
    mReleaseSlider.addListener (this);
    
    setSize (400, 200);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (Graphics& g)
{
    g.fillAll (Colours::orangered);
}

void ADSRComponent::resized()
{
    const auto dialSizeX = 0.25f;
    const auto dialSizeY = 0.6f;
    const auto yPosition = 0.2f;
    
    mAttackSlider.setBoundsRelative (0.0f, yPosition, dialSizeX, dialSizeY);
    mDecaySlider.setBoundsRelative (0.25f, yPosition, dialSizeX, dialSizeY);
    mSustainSlider.setBoundsRelative (0.5f, yPosition, dialSizeX, dialSizeY);
    mReleaseSlider.setBoundsRelative (0.75f, yPosition, dialSizeX, dialSizeY);
}

void ADSRComponent::sliderValueChanged (Slider *slider)
{
    if (slider == &mAttackSlider)
    {
        processor.setADSRAttack (mAttackSlider.getValue());
    }
    
    if (slider == &mDecaySlider)
    {
        processor.setADSRDecay (mDecaySlider.getValue());
    }
    
    if (slider == &mSustainSlider)
    {
        processor.setADSRSustain (mSustainSlider.getValue());
    }
    
    if (slider == &mReleaseSlider)
    {
        processor.setADSRRelease (mReleaseSlider.getValue());
    }
}
