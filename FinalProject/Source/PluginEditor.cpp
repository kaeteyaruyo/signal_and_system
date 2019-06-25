/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FinalProjectAudioProcessorEditor::FinalProjectAudioProcessorEditor (FinalProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (810, 400);
	int centerFrequency[6] = { 125, 250, 500, 1000, 2000, 4000 };
	for(int i = 0; i < 6; ++i){
		bands[i].setRange(-12, 12, 0.01);
		bands[i].setTextValueSuffix(" dB");
		bands[i].setSliderStyle(Slider::LinearVertical);
		bands[i].setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
		bands[i].setColour(Slider::textBoxOutlineColourId, Colour(0));
		bandLabels[i].setText(String(centerFrequency[i]) + String(" Hz"), dontSendNotification);
		bandLabels[i].attachToComponent(&bands[i], false);
		bandLabels[i].setJustificationType(Justification::centred);
		bands[i].addListener(this);
		addAndMakeVisible(bands[i]);
	}
}

FinalProjectAudioProcessorEditor::~FinalProjectAudioProcessorEditor()
{
}

//==============================================================================
void FinalProjectAudioProcessorEditor::paint (Graphics& g)
{
}

void FinalProjectAudioProcessorEditor::resized()
{
	for (int i = 0; i < 6; ++i) {
		bands[i].setBounds(30 + 130 * i, 50, 100, getHeight() - 100);
	}
}

void FinalProjectAudioProcessorEditor::sliderValueChanged(Slider *slider) {
	if (slider == &bands[0])
		processor.bandGains[0] = pow(10, bands[0].getValue() / 20);
	else if (slider == &bands[1])
		processor.bandGains[1] = pow(10, bands[1].getValue() / 20);
	else if (slider == &bands[2])
		processor.bandGains[2] = pow(10, bands[2].getValue() / 20);
	else if (slider == &bands[3])
		processor.bandGains[3] = pow(10, bands[3].getValue() / 20);
	else if (slider == &bands[4])
		processor.bandGains[4] = pow(10, bands[4].getValue() / 20);
	else if (slider == &bands[5])
		processor.bandGains[5] = pow(10, bands[5].getValue() / 20);
}