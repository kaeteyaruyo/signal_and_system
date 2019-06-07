/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lab3AudioProcessorEditor::Lab3AudioProcessorEditor(Lab3AudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(600, 400);

	// slider for distort argument
	distortArg.setSliderStyle(Slider::LinearBarVertical);
	distortArg.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	distortArg.setPopupDisplayEnabled(true, false, this);
	distortArg.setTextValueSuffix(" a");
	distortArg.setRange(0.0, 1.0);
	distortArg.setValue(0);
	distortArg.addListener(this);
	addAndMakeVisible(distortArg);

	// slider for upperBound slider
	upperBound.setSliderStyle(Slider::LinearBarVertical);
	upperBound.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	upperBound.setPopupDisplayEnabled(true, false, this);
	upperBound.setTextValueSuffix(" upperbound");
	upperBound.setRange(0.6, 1.0);
	upperBound.setValue(0.9);
	upperBound.addListener(this);
	addAndMakeVisible(upperBound);

	// slider for upperBound slider
	lowerBound.setSliderStyle(Slider::LinearBarVertical);
	lowerBound.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	lowerBound.setPopupDisplayEnabled(true, false, this);
	lowerBound.setTextValueSuffix(" lowerbound");
	lowerBound.setRange(0.0, 0.4);
	lowerBound.setValue(0.1);
	lowerBound.addListener(this);
	addAndMakeVisible(lowerBound);

}

Lab3AudioProcessorEditor::~Lab3AudioProcessorEditor()
{
}

//==============================================================================
void Lab3AudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Lab3AudioProcessorEditor::resized()
{
	distortArg.setBounds(280, 30, 40, getHeight() - 60);
	upperBound.setBounds(80, 30, 40, getHeight() - 60);
	lowerBound.setBounds(480, 30, 40, getHeight() - 60);
}

void Lab3AudioProcessorEditor::sliderValueChanged(Slider *slider) {
	if (slider == &distortArg)
		processor.distortArg = distortArg.getValue();
	else if (slider == &upperBound)
		processor.upperBound = upperBound.getValue();
	else if (slider == &lowerBound)
		processor.lowerBound = lowerBound.getValue();
}