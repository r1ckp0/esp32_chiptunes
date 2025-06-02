#include "tri.h"
#include "lfsr.h"
#include "square.h"
#include "saw.h"
#include <driver/dac.h>

#define DAC1_GPIO 17
#define DAC2_GPIO 18
#define DOUT_PIN 2
#define SCK_PIN 3

const float SAMPLE_RATE = 44100.0;
const uint32_t TIMER_INTERVAL = 2000000UL / (uint32_t)SAMPLE_RATE;
//Tri triangle(SAMPLE_RATE);
Tri tri(SAMPLE_RATE);
//Lfsr noise(SAMPLE_RATE);
//Square tri(SAMPLE_RATE);
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  //uint8_t sample = triangle.process();
  //dac_output_voltage(DAC_CHANNEL_1, sample);
  //dac_output_voltage(DAC_CHANNEL_2, sample);

  uint8_t sample = tri.process();
  dac_output_voltage(DAC_CHANNEL_1, sample);
  dac_output_voltage(DAC_CHANNEL_2, sample);

  portEXIT_CRITICAL_ISR(&timerMux);
}

long readHX710B() {
  long value = 0;
  
  // Esperar a que DOUT esté listo (LOW)
  while(digitalRead(DOUT_PIN) == HIGH);
  
  // Leer 24 bits
  for(int i = 0; i < 24; i++) {
    digitalWrite(SCK_PIN, HIGH);
    value = value << 1;
    digitalWrite(SCK_PIN, LOW);
    if(digitalRead(DOUT_PIN) == HIGH) {
      value++;
    }
  }
  
  // Pulso adicional para configurar ganancia
  digitalWrite(SCK_PIN, HIGH);
  digitalWrite(SCK_PIN, LOW);
  
  return value;
}

int clip(int value, int low, int high) {
  if (value < low) {
    value = low;
  } else if (value > high) {
    value = high;
  } else {
    value = value;
  }
  return value;
}

void setup() {
  Serial.begin(115200);

  pinMode(SCK_PIN, OUTPUT);
  pinMode(DOUT_PIN, INPUT);
  digitalWrite(SCK_PIN, LOW);

  dac_output_enable(DAC_CHANNEL_1);
  dac_output_enable(DAC_CHANNEL_2);

  tri.setFrequency(440.0);
  //sqr.setAmount(42);

  //triangle.setFrequency(440.0);
  //triangle.setAmplitude(1.0);

  //noise.setFrequency(440.0);
  //noise.setAmplitude(1.0);

  //sqr.setFrequency(440.0);
  //sqr.setAmplitude(1.0);

  timer = timerBegin(0, 40, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMER_INTERVAL, true);

  timerAlarmEnable(timer);

}

void loop() {
  long pressure = readHX710B();


  int mapValue = clip(map(pressure, 2700000, 5000000, 0, 255), 0, 255);

  
  tri.setAmplitude(mapValue);


  tri.setFrequency(1200);
  
  
  Serial.println(mapValue);
  delay(20);
  tri.setFrequency(1300);
}

/*void loop() {

    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        float freq = input.toFloat();
        if (freq > 50.0 && freq < 5000.0) {
          //sawtooth.setFrequency(freq);
          //tri.setFrequency(freq);
          Serial.print("Frecuencia cambiada a: ");
          Serial.println(freq);
        }
        int pw = input.toInt();
        if (pw >= 0 && pw <= 45) {
          //sawtooth.setAmount(pw);
          //tri.setPulseWidth(pw);
          Serial.print("amount cambiada a: ");
          Serial.println(pw);         
        }
    }
    
    delay(100); 
}*/
