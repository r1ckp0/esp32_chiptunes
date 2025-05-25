#ifndef SQUARE_H
#define SQUARE_H

#include <Arduino.h>

class Square {
public:
    Square(float sampleRate);
    void initSquare();
    uint8_t process();
    void setFrequency(float newFrequency);


private:
    int value
    int phase;
    float phaseIncrement;
    float sampleRate;
    float frequency;
    uint16_t dutyCycle;


    void updatePhaseIncrement();
};

#endif
