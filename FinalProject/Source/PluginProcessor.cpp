/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define LOW 0
#define BAND 1
#define HIGH 2
#define PI 3.14159265

//==============================================================================
FinalProjectAudioProcessor::FinalProjectAudioProcessor()
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
	for (int band = 0; band < 6; ++band) {
		vector<vector<vector<double>>> bandData;
		output.push_back(bandData);
		for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel) {
			vector<vector<double>> channelData;
			output[band].push_back(channelData);
			for (int filter = 0; filter < 3; ++filter) {
				vector<double> filterData;
				output[band][channel].push_back(filterData);
				for (int time = 0; time < 2; ++time) {
					output[band][channel][filter].push_back(0.0);
				}
			}
		}
	}
}

FinalProjectAudioProcessor::~FinalProjectAudioProcessor()
{
}

//==============================================================================
const String FinalProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FinalProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FinalProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FinalProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FinalProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FinalProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FinalProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FinalProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String FinalProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void FinalProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FinalProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FinalProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FinalProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

    // This checks if the input layout matches the output[band] layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FinalProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
		for (int i = 0; i < buffer.getNumSamples(); i++) {
			double sound = 0.0;
			for (int band = 0; band < 6; ++band) {
				double f1 = 2 * sin(PI * centerFrequency[band] / getSampleRate());
				output[band][channel][HIGH][0] = buffer.getSample(channel, i) - output[band][channel][LOW][1] - Q * output[band][channel][BAND][1];
				output[band][channel][BAND][0] = f1 * output[band][channel][HIGH][0] + output[band][channel][BAND][1];
				output[band][channel][LOW][0] = f1 * output[band][channel][BAND][0] + output[band][channel][LOW][1];
				output[band][channel][HIGH][1] = output[band][channel][HIGH][0];
				output[band][channel][BAND][1] = output[band][channel][BAND][0];
				output[band][channel][LOW][1] = output[band][channel][LOW][0];
				sound += output[band][channel][BAND][0] * bandGains[band];
			}
			channelData[i] = sound;
		}
	}

}

//==============================================================================
bool FinalProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FinalProjectAudioProcessor::createEditor()
{
    return new FinalProjectAudioProcessorEditor (*this);
}

//==============================================================================
void FinalProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FinalProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FinalProjectAudioProcessor();
}
