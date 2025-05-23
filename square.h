#ifndef SQUARE_H
#define SQUARE_H

#include <Arduino.h>

class Square {
public:
    Square(float sampleRate);
    void initSquare();
    uint8_t process();
    void setFrequency(float newFrequency);
    void setFeedback(int newFeedback);
    void setValue(int newValue);

private:

    int Square;
    int phase;
    int feedback;
    float phaseIncrement;
    float sampleRate;
    float frequency;
    int duties[8];


    void updatePhaseIncrement();
};

#endif
