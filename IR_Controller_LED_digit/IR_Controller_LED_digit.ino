#include <DIYables_IRcontroller.h> // DIYables_IRcontroller library
#define IR_RECEIVER_PIN 10 // The Arduino pin connected to IR controller
const int PIN_RED   = 11;
const int PIN_GREEN = 12;
const int PIN_BLUE  = 9; // ideally 13, but 13 didn't seem to work for me
#include "SevSeg.h"
SevSeg sevseg; 
DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200); // debounce time is 200ms
int curr_num = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irController.begin();
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}


void loop() {
  // put your main code here, to run repeatedly:
  Key21 key = irController.getKey();

  // switch-case statements for each input
  if (key != Key21::NONE) {
    switch (key) {
      case Key21::KEY_VOL_MINUS:
        if (curr_num > 0)
        {
          curr_num -= 1;
          sevseg.setNumber(curr_num);
        }
        break;

      case Key21::KEY_VOL_PLUS:
        if (curr_num < 9)
        {
          curr_num += 1;
          sevseg.setNumber(curr_num);
        }
        break;

      case Key21::KEY_0:
        Serial.println("0");
        sevseg.setNumber(0);
        sevseg.refreshDisplay();
        curr_num = 0;
        setColor(LOW, LOW, LOW);
        break;

      case Key21::KEY_1:
        Serial.println("1");
        sevseg.setNumber(1);
        sevseg.refreshDisplay();
        curr_num = 1;
        setColor(HIGH, LOW, LOW);
        break;

      case Key21::KEY_2:
        Serial.println("2");
        sevseg.setNumber(2);
        sevseg.refreshDisplay();
        curr_num = 2;
        setColor(LOW, HIGH, LOW);
        break;

      case Key21::KEY_3:
        Serial.println("3");
        sevseg.setNumber(3);
        sevseg.refreshDisplay();
        curr_num = 3;
        setColor(LOW, LOW, HIGH);
        break;

      case Key21::KEY_4:
        Serial.println("4");
        sevseg.setNumber(4);
        sevseg.refreshDisplay();
        curr_num = 4;
        setColor(HIGH, HIGH, LOW);
        break;

      case Key21::KEY_5:
        Serial.println("5");
        sevseg.setNumber(5);
        sevseg.refreshDisplay();
        curr_num = 5;
        setColor(LOW, HIGH, HIGH);
        break;

      case Key21::KEY_6:
        Serial.println("6");
        sevseg.setNumber(6);
        sevseg.refreshDisplay();
        curr_num = 6;
        setColor(HIGH, LOW, HIGH);
        break;

      case Key21::KEY_7:
        Serial.println("7");
        sevseg.setNumber(7);
        sevseg.refreshDisplay();
        curr_num = 7;
        setColor(LOW, HIGH, LOW);
        break;

      case Key21::KEY_8:
        Serial.println("8");
        sevseg.setNumber(8);
        sevseg.refreshDisplay();
        curr_num = 8;
        setColor(HIGH, LOW, LOW);
        break;

      case Key21::KEY_9:
        Serial.println("9");
        sevseg.setNumber(9);
        sevseg.refreshDisplay();
        curr_num = 9;
        setColor(HIGH, HIGH, HIGH);
        break;

      default:
        break;

      delay(1000);
    }
  }
}


void setColor(bool R, bool G, bool B)
{
    digitalWrite(PIN_RED, R);
    digitalWrite(PIN_GREEN, G);
    digitalWrite(PIN_BLUE, B);
}
