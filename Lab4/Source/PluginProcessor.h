/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#define PI 3.14159265

//==============================================================================
/**
*/
class Lab4AudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	Lab4AudioProcessor();
	~Lab4AudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;
	double damp = 1;
	double Fw = 1000;
	double minf = 100;
	double maxf = 2000;
	double Fs = 44100;
	double delta = Fw / Fs;
	double Q1 = 2 * damp;
	double Fc = minf;
	double F1 = 2 * sin(PI * Fc / Fs);
	double yh[4] = { 0 };
	double yb[4] = { 0 };
	double yl[4] = { 0 };
	double prev_yh[4] = { 0 };
	double prev_yb[4] = { 0 };
	double prev_yl[4] = { 0 };

private:
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Lab4AudioProcessor)
};