/*
  ==============================================================================

    SynthSound.h
    Created: 23 Jun 2019 3:42:12am
    Author:  user

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound {
public:
	bool appliesToNote(int midiNoteNumber) {
		return true;
	}

	bool appliesToChannel(int midiChannel) {
		return true;
	}
};