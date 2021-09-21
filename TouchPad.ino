#include <Synaptics.h>
#include <Mouse.h>

#define DATAPIN 5
#define CLKPIN 6

Synaptics pad(CLKPIN, DATAPIN);

uint8_t pos;
uint8_t mode;
bool info;
bool l, r;
int x, y;
int vertValue, horzValue;
const int sensitivity = 1;
int responseDelay = 2;
int start = 1;

void pad_init(){ // Initiate the touchpad
  info = pad.reset();
  Serial.print("Reset status: ");
  Serial.println(info);
  pad.set_remote_mode(); // remote mode
  delayMicroseconds(100);
}

void setup() {
  Serial.begin(9600);
  Serial.println("SETUP");
  pad_init();
  Mouse.begin(); // Start mouse HID protocol
}

void loop() { // put your main code here, to run repeatedly:
  if (start < 10) { // Prints loop 10 times to show it has started
    Serial.println("LOOP");
    start = start+1;
  }
  pad.read_data(); // Tell pad to read and store data
  vertValue = -(pad.getY()); // read vertical offset
  horzValue = pad.getX(); // read horizontal offset

  if(vertValue != 0 || horzValue != 0)  { // Print movement
    Serial.print(vertValue); // X Movement Data
    Serial.print(",");
    Serial.print(horzValue);
    Serial.println();
  }
  Mouse.move(horzValue, vertValue, 0); // Move mouse cursor
  delay(responseDelay);

  if (pad.leftClicked()==1) { // Check if left button is clicked
    if (!Mouse.isPressed(MOUSE_LEFT)){
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)){ //release if no longer pressed
      Mouse.release(MOUSE_LEFT);
    }
   }
  if (pad.rightClicked()==1) { // Check if right button is clicked
    if (!Mouse.isPressed(MOUSE_RIGHT)){
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)){ //release if no longer pressed
      Mouse.release(MOUSE_RIGHT);
    }
  }
}
