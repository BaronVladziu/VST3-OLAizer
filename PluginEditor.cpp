/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OlaizerAudioProcessorEditor::OlaizerAudioProcessorEditor (OlaizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(350, 150);

    float windowLengthDefault = 20.0;
    windowLength.setName("windowLength");
    windowLength.setSliderStyle(Slider::Rotary);
    windowLength.setRange(1, 100.0, 1.0);
    windowLength.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    windowLength.setPopupDisplayEnabled(true, false, this);
    windowLength.setTextValueSuffix(" (Window length) [ms]");
    windowLength.setValue(windowLengthDefault);
    addAndMakeVisible(&windowLength);
    windowLength.addListener(this);
    processor.olaizer->updateWindowLength(windowLengthDefault);

    float jumpDefault = 20.0;
    jump.setName("jump");
    jump.setSliderStyle(Slider::Rotary);
    jump.setRange(10, 100.0, 5.0);
    jump.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    jump.setPopupDisplayEnabled(true, false, this);
    jump.setTextValueSuffix(" (Jump) [%]");
    jump.setValue(jumpDefault);
    addAndMakeVisible(&jump);
    jump.addListener(this);
    processor.olaizer->updateJump(jumpDefault / 100);

    float diffDefault = 20.0;
    diff.setName("diff");
    diff.setSliderStyle(Slider::Rotary);
    diff.setRange(0, 100.0, 5.0);
    diff.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    diff.setPopupDisplayEnabled(true, false, this);
    diff.setTextValueSuffix(" (Shift) [%]");
    diff.setValue(diffDefault);
    addAndMakeVisible(&diff);
    diff.addListener(this);
    processor.olaizer->updateDiff(diffDefault/100);

    addAndMakeVisible(&turnOn);
    turnOn.setButtonText("On");
    turnOn.setToggleState(true, true);
    turnOn.onClick = [this] {OlaizerAudioProcessorEditor::onStateSwitch(); };
}

OlaizerAudioProcessorEditor::~OlaizerAudioProcessorEditor()
{
}

//==============================================================================
void OlaizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText("OLAizer", 0, 0, getWidth(), 30, Justification::centred, 1);

}

void OlaizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    windowLength.setBounds(30, 30, 100, 100);
    jump.setBounds(120, 30, 100, 100);
    diff.setBounds(210, 30, 100, 100);
    turnOn.setBounds(getWidth() - 80, 30, 80, 30);
}

void OlaizerAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider->getName() == "windowLength") {
        processor.olaizer->updateWindowLength(windowLength.getValue());
    }
    else if (slider->getName() == "jump") {
        processor.olaizer->updateJump(float(jump.getValue()) / 100);
    }
    else if (slider->getName() == "diff") {
        processor.olaizer->updateDiff(float(diff.getValue()) / 100);
    }
}

void OlaizerAudioProcessorEditor::onStateSwitch()
{
    auto state = turnOn.getToggleState();
    processor.turnedOn = (bool)state;
}
