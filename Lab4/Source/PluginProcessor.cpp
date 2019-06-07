/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>
#include <iostream>
using namespace std;

//==============================================================================
Lab4AudioProcessor::Lab4AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Lab4AudioProcessor::~Lab4AudioProcessor()
{
}

//==============================================================================
const String Lab4AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Lab4AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Lab4AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Lab4AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Lab4AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Lab4AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Lab4AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Lab4AudioProcessor::setCurrentProgram (int index)
{
}

const String Lab4AudioProcessor::getProgramName (int index)
{
    return {};
}

void Lab4AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Lab4AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Lab4AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Lab4AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Lab4AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

		for (int i = 0; i < buffer.getNumSamples(); i++) {
			yh[channel] = buffer.getSample(channel, i) - prev_yl[channel] - Q1 * prev_yb[channel];
			yb[channel] = F1 * yh[channel] + prev_yb[channel];
			yl[channel] = F1 * yb[channel] + prev_yl[channel];
			Fc += delta;
			if (Fc >= maxf) {
				Fc = maxf;
				delta = -delta;
			}
			else if (Fc <= minf) {
				Fc = minf;
				delta = -delta;
			}
			F1 = 2 * sin(PI * Fc / Fs);
			channelData[i] = yb[channel];
			Q1 = 2 * damp;
			delta = (Fw / Fs) * (delta / abs(delta));
			prev_yb[channel] = yb[channel];
			prev_yh[channel] = yh[channel];
			prev_yl[channel] = yl[channel];
		}
    }
}

//==============================================================================
bool Lab4AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Lab4AudioProcessor::createEditor()
{
    return new Lab4AudioProcessorEditor (*this);
}

//==============================================================================
void Lab4AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Lab4AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Lab4AudioProcessor();
}
