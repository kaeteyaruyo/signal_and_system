/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
using namespace std;

//==============================================================================
Lab7AudioProcessorEditor::Lab7AudioProcessorEditor(Lab7AudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 400);

	delay.setSliderStyle(Slider::LinearBarVertical);
	delay.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	delay.setPopupDisplayEnabled(true, false, this);
	delay.setTextValueSuffix(" second delay");
	delay.setRange(0.0, 0.99, 0.01);
	delay.setValue(0.5);
	delay.addListener(this);
	addAndMakeVisible(delay);

	gain.setSliderStyle(Slider::LinearBarVertical);
	gain.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	gain.setPopupDisplayEnabled(true, false, this);
	gain.setTextValueSuffix(" volumn");
	gain.setRange(0.0, 1.0);
	gain.setValue(0.5);
	gain.addListener(this);
	addAndMakeVisible(gain);
}

Lab7AudioProcessorEditor::~Lab7AudioProcessorEditor()
{
}

//==============================================================================
void Lab7AudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Lab7AudioProcessorEditor::resized()
{
	delay.setBounds(280, 30, 40, getHeight() - 60);
	gain.setBounds(80, 30, 40, getHeight() - 60);
}

void Lab7AudioProcessorEditor::sliderValueChanged(Slider *slider) {
	if (slider == &delay)
		processor.delay = delay.getValue() * 100;
	else if (slider == &gain)
		processor.gain = gain.getValue();
}