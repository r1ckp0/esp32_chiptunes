#ifndef SAW_H
#define SAW_H

#include <Arduino.h>

class Saw {
public:
    Saw(float sampleRate);
    void initSaw();
    uint8_t process();
    void setFrequency(float newFrequency);
    void setAmount(int newAmount);


private:
    float phase;
    float sampleRate;
    int amount;
    float frequency;
    float phaseIncrement;
    int counter;
    float amplitude;

    float transform();
    void updatePhaseIncrement();

};

#endif