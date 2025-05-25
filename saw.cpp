#include "saw.h"

Saw::Saw(float sampleRate) : 
    sampleRate(sampleRate), frequency(440.0f), amount(42), phase(0.0f), phaseIncrement(0.0f), counter(0) { 
    initSaw();
}

void Saw::initSaw() {
    phase = 0.0f;
    amount = 42;
    counter = 0;
}

uint8_t Saw::process() {
    phase+=phaseIncrement;

    if (phase >= 1.0) {
        phase-=1.0;
        counter+=1;
        if (counter >= 14) {
        counter = 0;
        }
    }

    float value = transform();

    return (uint8_t)(value * 255.0f);
}

void Saw::setAmount(int newAmount) {
    if (newAmount >= 0) {
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


    return ((float)out / 31.0f);

}

void Saw::updatePhaseIncrement() {
    phaseIncrement = (frequency * 14) / sampleRate;
}