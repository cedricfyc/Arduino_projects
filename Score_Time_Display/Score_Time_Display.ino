#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

int32_t delayStart = 0;
int32_t score = 0;
int32_t time = 1000;
bool delayRunning = true; // not finished yet
int32_t score_timer = 30;


// will be setup in the future to start at the same time
// as other arduino
void setup() {
    byte numDigits = 4;  
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
    delayStart = millis();  // start delay
    Serial.begin(9600);
}
void loop() {
    if (delayRunning) {
    sevseg.setNumber(score_timer, -1);
    sevseg.refreshDisplay(); // Must run repeatedly
    }

    if (!(delayRunning)) {
    sevseg.setNumber(0, 2); // dp seperates score from countdown timer
    sevseg.refreshDisplay();
    Serial.println("Time out!");}

    // countdown timer + score counter
    // score will be incremented by bool from other arduino
    if (delayRunning && ((millis() - delayStart) >= time))
    {
      if (delayRunning && ((millis() - delayStart) >= 30000)) {delayRunning = false;}

      // increment score every 2 s
      // comment out when receiving bool
      if (delayRunning && ((time/1000) % 2 == 0) && score < 9) {score += 1;}

      score_timer = score*100 + (30000 - time)/1000;
      Serial.println(score_timer);

      // increment time passed by 1000 milliseconds
      time += 1000;
    }
}