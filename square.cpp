#include "square.h"

Square::Square(float sampleRate) :
    sampleRate(sampleRate), pulseWidth(1), phaseIncrement(0.0f), phase(0), amplitude(1.0f),
    frequency(440.0f) {
    initSquare();
}

void Square::initSquare() {
    phase = 0.5f;
    pulseWidth = 1;
}

uint8_t Square::process() {

    phase+=phaseIncrement;
    if (phase >= 1.0f) {
        phase -=  1.0f;
    }
    if (phase<= (pulseWidth/16.0f)) {
        return (uint8_t)(amplitude * 255.0f);
    } else {
        return 0;
    }
}

void Square::setFrequency(float newFrequency) {
    frequency = newFrequency;
    updatePhaseIncrement();
}

void Square::setPulseWidth(float newPulseWidth) {
    pulseWidth = newPulseWidth;
}

void Square::setAmplitude(float newAmplitude) {
    amplitude = newAmplitude;
}

void Square::updatePhaseIncrement() {
    phaseIncrement = frequency / sampleRate;
}