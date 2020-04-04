/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 4 Apr 2020 7:35:53pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent (HelloSamplerAudioProcessor& p) : processor (p)
{
    //Attack Slider
    mAttackSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setColour (Slider::ColourIds::thumbColourId, Colours::red);
    //mAttackSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mAttackSlider);
    
    mAttackLabel.setFont (10.0f);
    mAttackLabel.setText ("Attack", NotificationType::dontSendNotification);
    mAttackLabel.setJustificationType (Justification::centredTop);
    mAttackLabel.attachToComponent (&mAttackSlider, false);
    
    mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "ATTACK", mAttackSlider);
    
    //Decay Slider
    mDecaySlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setColour (Slider::ColourIds::thumbColourId, Colours::red);
    //mDecaySlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mDecaySlider);
    
    mDecayLabel.setFont (10.0f);
    mDecayLabel.setText ("Decay", NotificationType::dontSendNotification);
    mDecayLabel.setJustificationType (Justification::centredTop);
    mDecayLabel.attachToComponent (&mDecaySlider, false);
    
    mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "DECAY", mDecaySlider);
    
    //Sustain Slider
    mSustainSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setColour (Slider::ColourIds::thumbColourId, Colours::red);
    //mSustainSlider.setRange (0.0f, 1.0f, 0.01f);
    addAndMakeVisible (mSustainSlider);
    
    mSustainLabel.setFont (10.0f);
    mSustainLabel.setText ("Sustain", NotificationType::dontSendNotification);
    mSustainLabel.setJustificationType (Justification::centredTop);
    mSustainLabel.attachToComponent (&mSustainSlider, false);
    
    mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "SUSTAIN", mSustainSlider);
    
    //Release Slider
    mReleaseSlider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setColour (Slider::ColourIds::thumbColourId, Colours::red);
    //mReleaseSlider.setRange (0.0f, 5.0f, 0.01f);
    addAndMakeVisible (mReleaseSlider);
    
    mReleaseLabel.setFont (10.0f);
    mReleaseLabel.setText ("Release", NotificationType::dontSendNotification);
    mReleaseLabel.setJustificationType (Justification::centredTop);
    mReleaseLabel.attachToComponent (&mReleaseSlider, false);
    
    mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "RELEASE", mReleaseSlider);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void ADSRComponent::resized()
{
    const auto startX = 0.6f;
    const auto startY = 0.2f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.75f;
    
    mAttackSlider.setBoundsRelative (startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative (startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative (startX + (dialWidth * 2), startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative (startX + (dialWidth * 3), startY, dialWidth, dialHeight);
}
