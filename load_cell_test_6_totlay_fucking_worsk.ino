#include <Q2HX711.h>
#include <RotaryEncoder.h>

// load cell sensor
const byte left_data_pin = A2;
const byte left_clock_pin = A3;
const byte right_data_pin = A4;
const byte right_clock_pin = A5;

const float left_cal = 8.82;
const float right_cal = 8.87;

float left_load;
float right_load;

// rotary encoder
int rotary_pin_a = 19;
int rotary_pin_b = 18;
RotaryEncoder encoder(rotary_pin_a, rotary_pin_b);

// load cell
Q2HX711 left(left_data_pin, left_clock_pin);
Q2HX711 right(right_data_pin, right_clock_pin);
int left_startload ;
int right_startload;



void rotary_isr() {
  encoder.tick();
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(rotary_pin_a), rotary_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotary_pin_b), rotary_isr, CHANGE);
  left_startload = left.read();
  right_startload = right.read();
  Serial.begin(9600);
}

void loop() {

// load cell


  float left_lode = left.read() - (left_startload+8388567);
  float right_lode = right.read() - (right_startload+8454110);


  float left_gramsload =left_lode /left_cal;
  float right_gramsload =right_lode /right_cal;
  
// rotary encoder
  static int pos = 0;
  int newpos = encoder.getPosition();
  /*
  if (pos != newpos) {
    Serial.print(newpos);
    Serial.println();
    pos = newpos;
  } // if
  */
/*
  //lode cells 
  Serial.print("left.read(): ");
  Serial.println(left.read());
  Serial.print("left_startload: ");
  Serial.println(left_startload);
  Serial.print("left_lode: ");
  Serial.println(left_lode);
  Serial.println ("---------------");
  */
  //encoder 
  Serial.print (left_gramsload);
  Serial.print ("\t");
   Serial.print(right_gramsload);
  Serial.print ("\t");
  Serial.println (newpos);
  

  
//  Serial.println(gramsload);
//  delay(500);
}
