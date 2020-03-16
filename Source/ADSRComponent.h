/*
  ==============================================================================

    ADSRComponent.h
    Created: 14 Mar 2020 2:52:49pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSRComponent : public Component,
                      public Slider::Listener
{
public:
    ADSRComponent (HelloSamplerAudioProcessor& p);
    ~ADSRComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider *slider) override;
    
    Slider& getAttackSlider() { return mAttackSlider; }
    Slider& getDecaySlider() { return mDecaySlider; }
    Slider& getSustainSlider() { return mSustainSlider; }
    Slider& getReleaseSlider() { return mReleaseSlider; }

private:
    Slider mAttackSlider;
    Slider mDecaySlider;
    Slider mSustainSlider;
    Slider mReleaseSlider;
    
    HelloSamplerAudioProcessor& processor;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
