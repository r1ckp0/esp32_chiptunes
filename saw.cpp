#include "saw.h"

Saw::Saw(float sampleRate) : 
    sampleRate(sampleRate), frequency(440.0f), amount(42), phase(0.0f), phaseIncrement(0.0f), counter(0) { 
    initSaw();
}

void Saw::initSaw() {
    phase = 0.0f;
    amount = 42;
}

float Saw::process() {
    phase+=1;

    if (phase >= phaseIncrement) {
        counter+=1;
        phase = 0;
    }

    if (counter >= 14) {
        counter = 0;
    }

    return transform();
}

void Saw::setAmount(int newAmount) {
    if (newAmount > 0) {
        amount = newAmount;
    }
}

void Saw::setFrequency(float newFrequency) {
    frequency = newFrequency;
    updatePhaseIncrement();
}

float Saw::transform() {
    int value;

    if ((counter % 2) == 0) {
        value = amount * counter;
    } else {
        value = amount * (counter - 1);
    }

    int out = ((value >> 3) & 1)
            + (((value >> 4) & 1) << 1)
            + (((value >> 5) & 1) << 2)
            + (((value >> 6) & 1) << 3)
            + (((value >> 7) & 1) << 4);

    // Normalizar a [-1.0, 1.0]
    return ((float)out / 31.0f) * 2.0f - 1.0f;
}

void Saw::updatePhaseIncrement() {
    phaseIncrement = sampleRate / frequency;
}