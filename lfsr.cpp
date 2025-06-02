#include "lfsr.h"

Lfsr::Lfsr(float sampleRate) :
    sampleRate(sampleRate), lfsr(1), phaseIncrement(0.0f), phase(0), amplitude(1.0f),
    frequency(440.0f), feedback(7) {
    initLfsr();
}

void Lfsr::initLfsr() {
    lfsr = 1;
    feedback = 7;
    phase = 0;
}


uint8_t Lfsr::process() {

    phase += 1;
    if (phase >= phaseIncrement) {
        int bit = ((lfsr >> 1) & 1) ^ ((lfsr >> 0) & 1);
        lfsr = (lfsr >> 1) | (bit << feedback);
        phase = 0;
    }
    return (uint8_t)((lfsr & 1) * amplitude * 255.0f);
}

void Lfsr::setFrequency(float newFrequency) {
    frequency = newFrequency;
    updatePhaseIncrement();
}

void Lfsr::setFeedback(int newFeedback) {
    if (newFeedback > 0) {
        feedback = newFeedback;
    }
}

void Lfsr::setValue(int newValue) {
    if (newValue > 0) {
        lfsr = newValue;
    }
}

void Lfsr::updatePhaseIncrement() {
    phaseIncrement = sampleRate / frequency;
}


