#ifndef SQUARE_H
#define SQUARE_H

#include <Arduino.h>

class Square {
public:
    Square(float sampleRate);
    void initSquare();
    uint8_t process();
    void setFrequency(float newFrequency);
    void setAmplitude(float newAmplitude);
    void setPulseWidth(float newPulseWidth);


private:
    float phase;
    float phaseIncrement;
    float sampleRate;
    float frequency;
    int pulseWidth;
    float amplitude;


    void updatePhaseIncrement();
};

#endif
