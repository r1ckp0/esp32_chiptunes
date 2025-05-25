#include "square.h"

Square::Square(float sampleRate) :
    sampleRate(sampleRate), dutyCyle(1), phaseIncrement(0.0f), phase(0),
    frequency(440.0f), current(0) {
    initSquare();
}

void Square::initSquare() {
    Square = 1;
    feedback = 7;
    phase = 0;
    
    for (i = 0, i < 8, i++) {
        duties[i] = pow(2, i) - 1;
    }
}


uint8_t Square::process() {

    phase += 1;
    if (phase >= phaseIncrement) {
        current = (current + 1) % 16
    }
    return ((Square >> current) & 1) ? HIGH : LOW;
}

void Square::setFrequency(float newFrequency) {
    frequency = newFrequency;
    updatePhaseIncrement();
}

void Square::setDutyCycle(int newDutyCycle) {
    if (newDutyCycle >= 0 && newDutyCycle < 8) {
        dutyCyle = newDutyCycle;
    }
}

void Square::updatePhaseIncrement() {
    phaseIncrement = sampleRate / frequency / 16;
}


