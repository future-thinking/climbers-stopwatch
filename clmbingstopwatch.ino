/*
 * Code for the climbing stop watch.
 * 7-segment display info: http://thomas.bibby.ie/using-the-kyx-5461as-4-digit-7-segment-led-display-with-arduino/
 * Pin assignment in XLSX file in repo
 */

#include <SevenSeg.h>
// 7seg pinout: A:12, B:8, C:4, D:6, E:7, F:11, G:A2
SevenSeg disp(12, 8, 4, 6, 7, 11, A2);
const int numOfDigits = 4;
// 7seg pinout: Seg1:13, Seg2:10, Seg3:9, Seg4:2
int digitPins[numOfDigits] = {13, 10, 9, 2};  

volatile long start = -1;
long Zeit = 0;
float i = 0; 
#define BOUNCE 500

#define PEDAL_PIN 3
#define TASTER_PIN A1
#define BUZZER_PIN A0

void setup() {
  disp.setDigitPins(numOfDigits, digitPins);
  Serial.begin(9600);
  attachInterrupt(PEDAL_PIN, pedal, FALLING);
   disp.setCommonCathode(); // common cathode display
   disp.setDPPin(5);
}

void loop()
{
  if (digitalRead(BUZZER_PIN) == HIGH)
  {
    if (start != -1)
    {
      Zeit = millis() - start;
      Serial.println(Zeit);
    }
  }
  disp.write((millis() - start) / 1000.0);
  if(digitalRead(TASTER_PIN) == LOW)
  {
    
  }
}

void pedal() {
  if (millis() - start > BOUNCE) {
    start = millis();
  }
}
