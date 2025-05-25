#include "tri.h"
#include "lfsr.h"
#include "square.h"
#include <driver/dac.h>

#define DAC1_GPIO 17
#define DAC2_GPIO 18
#define LFSR_OUT 3
#define SQR_OUT 5

const float SAMPLE_RATE = 44100.0;
//Tri triangle(SAMPLE_RATE);
//Lfsr noise(SAMPLE_RATE);
Square sqr(SAMPLE_RATE);
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  //uint8_t sample = triangle.process();
  //dac_output_voltage(DAC_CHANNEL_1, sample);
  //dac_output_voltage(DAC_CHANNEL_2, sample);

  //digitalWrite(LFSR_OUT, noise.process());

  digitalWrite(SQR_OUT, sqr.process());

  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);

  //pinMode(LFSR_OUT, OUTPUT);

  pinMode(SQR_OUT, OUTPUT);

  //dac_output_enable(DAC_CHANNEL_1);
  //dac_output_enable(DAC_CHANNEL_2);

  //triangle.setFrequency(440.0);
  //triangle.setAmplitude(1.0);

  //noise.setFrequency(440.0);
  sqr.setFrequency(440.0);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000 / SAMPLE_RATE, true);

  timerAlarmEnable(timer);

  //Serial.println("triangle");
}

void loop() {

    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        float freq = input.toFloat();
        if (freq > 20.0 && freq < 5000.0) {
            //triangle.setFrequency(freq);
            sqr.setFrequency(freq);
            Serial.print("Frecuencia cambiada a: ");
            Serial.println(freq);
        }
        int duty = input.toInt();
        if (duty < 8 && duty >= 0) {
            
            sqr.setDutyCycle(duty);
            Serial.print("value: ");
            Serial.println(duty);            
        }
    }
    
    delay(100); 
}
