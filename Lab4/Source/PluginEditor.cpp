/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lab4AudioProcessorEditor::Lab4AudioProcessorEditor(Lab4AudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 400);

	damp.setSliderStyle(Slider::LinearBarVertical);
	damp.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	damp.setPopupDisplayEnabled(true, false, this);
	damp.setTextValueSuffix(" damping");
	damp.setRange(0.0, 1.0);
	damp.setValue(0.05);
	damp.addListener(this);
	addAndMakeVisible(damp);

	wahFrequency.setSliderStyle(Slider::LinearBarVertical);
	wahFrequency.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	wahFrequency.setPopupDisplayEnabled(true, false, this);
	wahFrequency.setTextValueSuffix(" Hz wah frequency");
	wahFrequency.setRange(500, 2500);
	wahFrequency.setValue(1000);
	wahFrequency.addListener(this);
	addAndMakeVisible(wahFrequency);
}

Lab4AudioProcessorEditor::~Lab4AudioProcessorEditor()
{
}

//==============================================================================
void Lab4AudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Lab4AudioProcessorEditor::resized()
{
	damp.setBounds(280, 30, 40, getHeight() - 60);
	wahFrequency.setBounds(80, 30, 40, getHeight() - 60);
}

void Lab4AudioProcessorEditor::sliderValueChanged(Slider *slider) {
	if (slider == &damp)
		processor.damp = damp.getValue();
	else if (slider == &wahFrequency)
		processor.Fw = wahFrequency.getValue();
}