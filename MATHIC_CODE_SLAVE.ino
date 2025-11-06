#include <Wire.h>
#include <SevSeg.h>


struct Message {

  uint8_t command;
  int16_t value;

};

Message msg;

SevSeg sevseg;

int totalSeconds = -1;
unsigned long lastUpdate = 0;
bool timerDone = false;
int stepVal = -1;


void setup() {
  
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5}; // D1, D2, D3, D4
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // A, B, C, D, E, F, G, DP
  bool resistorsOnSegments = true;
  bool updateWithDelays = false;
  bool leadingZeros = true;
  bool disableDecPoint = false;

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins,
               resistorsOnSegments, updateWithDelays,
               leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
  sevseg.blank();

  Wire.begin(8); // slave address 8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  Serial.begin(9600);
  Serial.println("Slave ready (waiting for command)");
}

void loop() {
  unsigned long now = millis();


  if (totalSeconds >= 0) {
    if (now - lastUpdate >= 1000) {
      lastUpdate = now;

      int minutes = totalSeconds / 60;
      int seconds = totalSeconds % 60;
      int displayValue = minutes * 100 + seconds;
      sevseg.setNumber(displayValue, 2);

      totalSeconds--;

      if (totalSeconds < 0) {
        sevseg.blank();
        timerDone = true; // mark that timer finished
        Serial.println("Timer done!");
      }
    }
  }

  sevseg.refreshDisplay();
}
  

// Called when master sends data
void receiveEvent(int howMany) {
  if (howMany >= 3) {
    msg.command = Wire.read();
    byte low = Wire.read();
    byte high = Wire.read();
    msg.value = word(high, low);

    Serial.print("Received cmd=");
    Serial.print(msg.command);
    Serial.print(" val=");
    Serial.println(msg.value);

    if (msg.command == 0) {
      totalSeconds = msg.value;
      timerDone = false;
      if (totalSeconds >= 0) {
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        int displayValue = minutes * 100 + seconds;
        sevseg.setNumber(displayValue, 2);
      } else {
        sevseg.blank();
      }
    }
  }
}

// Called when master requests data
void requestEvent() {
  byte doneFlag = timerDone ? 1 : 0;
  Wire.write(doneFlag);
}
