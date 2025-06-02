#ifndef LFSR_H
#define LFSR_H

#include <Arduino.h>

class Lfsr {
public:
    Lfsr(float sampleRate);
    void initLfsr();
    uint8_t process();
    void setFrequency(float newFrequency);
    void setFeedback(int newFeedback);
    void setValue(int newValue);

private:

    int lfsr;
    float phase;
    int feedback;
    float phaseIncrement;
    float sampleRate;
    float frequency;
    float amplitude;


    void updatePhaseIncrement();
};

#endif
