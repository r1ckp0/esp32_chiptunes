#ifndef SQUARE_H
#define SQUARE_H

#include <Arduino.h>

class Square {
public:
    Square(float sampleRate);
    void initSquare();
    uint8_t process();
    void setFrequency(float newFrequency);
    void setPulseWidth(float newPulseWidth);


private:
    float phase;
    float phaseIncrement;
    float sampleRate;
    float frequency;
    int pulseWidth;


    void updatePhaseIncrement();
};

#endif
