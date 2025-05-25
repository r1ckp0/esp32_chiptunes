#ifndef SAW_H
#define SAW_H

#include <Arduino.h>

class Saw {
public:
    Saw(float sampleRate);
    void initSaw();
    float process();
    void setFrequency(float newFrequency);
    void setAmount(float newAmount);


private:
    float phase;
    float sampleRate;
    int amount;
    float frequency;
    float phaseIncrement;
    int counter;

    float transform();
    void updatePhaseIncrement();

};

#endif