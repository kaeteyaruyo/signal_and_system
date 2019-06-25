/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <cmath>

//==============================================================================
/**
*/
class FinalProjectAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener
{
public:
	FinalProjectAudioProcessorEditor(FinalProjectAudioProcessor&);
	~FinalProjectAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	FinalProjectAudioProcessor & processor;
	Slider bands[6];
	Label bandLabels[6];

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FinalProjectAudioProcessorEditor)
};