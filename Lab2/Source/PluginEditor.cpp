/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lab2AudioProcessorEditor::Lab2AudioProcessorEditor(Lab2AudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(200, 400);

	// these define the parameters of our slider object
	gainSlider.setSliderStyle(Slider::LinearBarVertical);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	gainSlider.setRange(0.0, 1.0);
	gainSlider.setValue(0.5);
	gainSlider.addListener(this);
	addAndMakeVisible(gainSlider);
}

Lab2AudioProcessorEditor::~Lab2AudioProcessorEditor()
{
}

//==============================================================================
void Lab2AudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Lab2AudioProcessorEditor::resized()
{
	gainSlider.setBounds(getLocalBounds());
}

void Lab2AudioProcessorEditor::sliderValueChanged(Slider *slider) {
	processor.rawVolumn = gainSlider.getValue();
}