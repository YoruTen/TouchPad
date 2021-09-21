#include <Synaptics.h>
#include <Mouse.h>

#define DATAPIN 5 
#define CLKPIN  6 

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

void pad_init()
{
  info = pad.reset();
  Serial.print("Reset status: ");
  Serial.println(info);
  pad.set_remote_mode();  // remote mode
  //Serial.println("Hello PAD2");
  //pad.read();  // ack
  //Serial.println("Hello PAD3");
  delayMicroseconds(100);
  //info = pad.isRelative();
  //Serial.println(info);
  //mode = pad.read_modes();
  //Serial.println(mode); 
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("SETUP");
  pad_init();
  Mouse.begin();
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (start < 10) {
    Serial.println("LOOP");
    start = start+1;
  }
  pad.read_data();
//  pos = pad.read();
//  Serial.println(pos);
  
//  y=pad.getY();
//  x=pad.getX();
//  l=pad.leftClicked();
//  r=pad.rightClicked();
//  Serial.print(x); // X Movement Data
//  Serial.print(",");
//  Serial.print(y);
//  Serial.print(":");
//  Serial.print(l);
//  Serial.print(",");
//  Serial.print(r);

  vertValue = -(pad.getY());  // read vertical offset
  horzValue = pad.getX();  // read horizontal offset
//  Serial.print(":");
  if(vertValue != 0 || horzValue != 0){
    Serial.print(vertValue); // X Movement Data
    Serial.print(",");
    Serial.print(horzValue);
    Serial.println();
  }
  Mouse.move(horzValue, vertValue, 0);

  delay(responseDelay);
  if (pad.leftClicked()==1)  {
    if  (!Mouse.isPressed(MOUSE_LEFT)){
      Mouse.press(MOUSE_LEFT);
    }
  }
  else  {
    if  (Mouse.isPressed(MOUSE_LEFT)){
      Mouse.release(MOUSE_LEFT);
    }
  }
  if (pad.rightClicked()==1)  {
    if  (!Mouse.isPressed(MOUSE_RIGHT)){
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else  {
    if  (Mouse.isPressed(MOUSE_RIGHT)){
      Mouse.release(MOUSE_RIGHT);
    }
  }
}
