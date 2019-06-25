/*
  ==============================================================================

    SynthVoice.h
    Created: 23 Jun 2019 3:42:25am
    Author:  user

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"
#include <vector>
using namespace std;

class SynthVoice : public SynthesiserVoice {
public:
	bool canPlaySound(SynthesiserSound *sound) {
		return dynamic_cast <SynthSound *> (sound) != NULL;
	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {
		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		tableSize = getSampleRate() / frequency;
		for (int i = 0; i < tableSize; ++i) {
			waveTable.push_back(osc1.noise());
		}

		for (int i = 0; i < 100000; ++i) {
			outputWave[i] = waveTable[0];
			waveTable.push_back(0.995 * 0.5 * (waveTable[0] + waveTable[1]));
			waveTable.erase(waveTable.begin());
		}
		pointer = 0;
	}

	void stopNote(float velocity, bool allowTailOff) {
		clearCurrentNote();
		level = 0;
		waveTable.clear();
	}

	void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {
		for (int sample = startSample; sample < numSamples; ++sample) {
			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
				outputBuffer.addSample(channel, sample, outputWave[pointer] * level);
			}
			pointer = (pointer + 1) % 100000;
		}
	}

	void pitchWheelMoved(int newPitchWheelValue) {
	}

	void controllerMoved(int controllerNumber, int newControllerValue) {
	}

private:
	double outputWave[100000];
	double level;
	double frequency;
	int tableSize;
	int pointer = 0;
	vector<double> waveTable;
	maxiOsc osc1;

};