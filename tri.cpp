#include "tri.h"

Tri::Tri(float sampleRate) :
    sampleRate(sampleRate), phase(0.0f), phaseIncrement(0.0f),
    frequency(440.0f), amplitude(1.0f) {
    initTri();
}

//void Tri::initTri() {
    //for (int i = 0; i < TABLE_SIZE / 2; i++) {
    //    wavetable[i] = 128 + int(127.0f * (-1.0f + (2.0f * i / (TABLE_SIZE / 2))));
    //}
    //for (int i = TABLE_SIZE / 2; i < TABLE_SIZE; i++) {
    //    wavetable[i] = 128 + int(127.0f * (1.0f - (2.0f * (i - TABLE_SIZE / 2) / (TABLE_SIZE / 2))));
    //}
void Tri::initTri() {
    for (int i = 0; i < TABLE_SIZE / 2; i++) {
        wavetable[i] = i / float(TABLE_SIZE / 2 - 1); // Normalizado 0.0 a 1.0
    }
    for (int i = TABLE_SIZE / 2; i < TABLE_SIZE; i++) {
        wavetable[i] = (TABLE_SIZE - i - 1) / float(TABLE_SIZE / 2 - 1); // Baja 1.0 a 0.0
    }
}


uint8_t Tri::process() {
    //int index1 = static_cast<int>(phase);
    //int index2 = (index1 + 1) % TABLE_SIZE;
    //float fractional = phase - index1;

    //float value = wavetable[index1] * (1.0f - fractional) + wavetable[index2] * fractional;
    int index = static_cast<int>(phase);
    float value = wavetable[index] * 255.0f;

    phase += phaseIncrement;
    while (phase >= TABLE_SIZE) {
        phase -= TABLE_SIZE;
    }

    return static_cast<uint8_t>(value * amplitude);
}

void Tri::setFrequency(float newFrequency) {
    frequency = newFrequency;
    updatePhaseIncrement();
}

void Tri::setAmplitude(float newAmplitude) {
    amplitude = newAmplitude;
}

void Tri::updatePhaseIncrement() {
    phaseIncrement = frequency * TABLE_SIZE / sampleRate;
}