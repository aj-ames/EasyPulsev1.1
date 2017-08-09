/*
  Program to calculate BPM using EasyPulse Sensor v1.1
  This is achieved by calculating 3 peaks of pulses and averaging the values.
 */

int sensorValue = 0;
bool pulse = false;
bool done = false;
int peak1 = 0, peak2 = 0, peak3 = 0;
float bpm = 0;
void setup() {
  Serial.begin(115200);
}

void loop() {
  bpmCalculator();
}

int peakFinder() {
  while(true) {
    sensorValue = analogRead(A0);
    delay(75);
    if(sensorValue > 1000) {
      while(true) {
        sensorValue = analogRead(A0);
        delay(75);
        if(sensorValue < 10) {
          pulse = true;
          return millis();
        }
      }
    }
  }
}

void bpmCalculator() {
  peak1 = peakFinder();
  if(pulse) {
    pulse = false;
    peak2 = peakFinder();
  }
  if(pulse) {
    pulse = false;
    peak3 = peakFinder();
    done = true;
  }
  if(done) {
    //Serial.println("Pulse 1: ");
    //Serial.println(peak1);
    //Serial.println("Pulse 2: ");
    //Serial.println(peak2);
    //Serial.println("Pulse 3: ");
    //Serial.println(peak3);
    float pulse1 = (peak2 - peak1)/1000.0;;
    float pulse2 = (peak3 - peak2)/1000.0;
    float avg = (pulse1 + pulse2)/2.0;
    bpm = 60.0/avg;
    Serial.println("BPM:");
    Serial.println(bpm);
  }
}
