/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OlaizerAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    OlaizerAudioProcessorEditor (OlaizerAudioProcessor&);
    ~OlaizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void onStateSwitch();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OlaizerAudioProcessor& processor;

    Slider windowLength;
    Slider jump;
    Slider diff;
    ToggleButton turnOn;

    void sliderValueChanged(Slider* slider) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OlaizerAudioProcessorEditor)
};
