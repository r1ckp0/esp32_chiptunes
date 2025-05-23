#ifndef TRI_H
#define TRI_H

#include <Arduino.h>

class Tri {
public:
    Tri(float sampleRate);
    void initTri();
    uint8_t process();
    void setFrequency(float newFrequency);
    void setAmplitude(float newAmplitude);

private:
    static const int TABLE_SIZE = 32;
    uint8_t wavetable[TABLE_SIZE];
    float phase;
    float phaseIncrement;
    float sampleRate;
    float frequency;
    float amplitude;

    void updatePhaseIncrement();
};

#endif
