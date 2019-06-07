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
class Lab3AudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener
{
public:
	Lab3AudioProcessorEditor(Lab3AudioProcessor&);
	~Lab3AudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	Lab3AudioProcessor & processor;
	Slider upperBound;
	Slider lowerBound;
	Slider distortArg;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Lab3AudioProcessorEditor)
};