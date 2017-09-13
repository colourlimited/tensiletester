#include <Q2HX711.h>
#include <RotaryEncoder.h>

// load cell sensor
const byte left_data_pin = A2;
const byte left_clock_pin = A3;
const byte right_data_pin = A4;
const byte right_clock_pin = A5;

/* 89.2 kg test: 17493562.00 raw */
/* 00.0 kg test: 16857478.00 raw */

/*
    rotary encoder:
    15 ticks per rotation
    each rotation of the encoder is 1/4 rotation of the main shaft, which is M16.
    M16 is 2mm per turn.
*/
const float travel_per_step = (2.0 / 4.0) / 15.0;


const float cal = (17493562.0 - 16857478.0) / 89.2;
const float left_cal = cal;
const float right_cal = cal;

float left_load;
float right_load;

// rotary encoder
int rotary_pin_a = 19;
int rotary_pin_b = 18;
RotaryEncoder encoder(rotary_pin_a, rotary_pin_b);

// load cell
Q2HX711 left(left_data_pin, left_clock_pin);
Q2HX711 right(right_data_pin, right_clock_pin);
float left_startload;
float right_startload;



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


  float left_load = left.read() - (left_startload/*+8388567*/);
  float right_load = right.read() - (right_startload/*+8454110*/);


  float left_gramsload = left_load / left_cal;
  float right_gramsload = right_load / right_cal;

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
  /*  Serial.print (left_gramsload);
    Serial.print ("\t");
     Serial.print(right_gramsload);
    Serial.print ("\t"); */
  Serial.print  (left_gramsload + right_gramsload);
  Serial.print  (" kg\t");
  Serial.print  (newpos * travel_per_step);
  Serial.println(" mm\t");



  //  Serial.println(gramsload);
  //  delay(500);
}
