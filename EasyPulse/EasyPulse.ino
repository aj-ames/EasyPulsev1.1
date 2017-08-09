/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

int sensorValue = 0;
bool pulse = false;
bool newPulse = false;
long pulseTimer = 0;
long newpulseTimer = 0;
void setup() {
  Serial.begin(115200);
}

void loop() {
  sensorValue = analogRead(A0);
  delay(5);
  if(sensorValue > 1000) {
    pulse = true;
    pulseTimer = millis();
  }
  if(sensorValue < 10 && pulse == true) {
    while(true) {
      sensorValue = analogRead(A0);
      delay(5);
      if(sensorValue > 1000) {
        pulse = false;
        while(true) {
          sensorValue = analogRead(A0);
          delay(5);
          if(sensorValue < 10) {
            newpulseTimer = millis();
            newPulse = true;
            break;
          }
        }
      }
      if(newPulse) {
        Serial.println("BPM: ");
        float bpm = 60.0/((newpulseTimer/1000.0) - (pulseTimer/1000.0));
        Serial.println(bpm);
        newPulse = false;
        break;
      }
    }
  }
}

void delay_x(uint32_t millis_delay)
{
  uint16_t micros_now = (uint16_t)micros();

  while (millis_delay > 0) {
    if (((uint16_t)micros() - micros_now) >= 1000) {
      millis_delay--;
      micros_now += 1000;
    }
  }  
}
