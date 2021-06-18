/*
  Tank Bot
  Justin C Kirk

  info@makerinchief.com
  https://www.makerinchief.com/12
  https://github.com/makerinchief/TankBot

  Tank Bot Parts:

  4 x DC Hobby Motors Motors + Tires
  1 x L298N DC Motor Driver
  1 x Arduino Nano
  1 x Nano Breakout Board with headers for NRF2401 Module
  1 x NRF24l01 2.4GHz RF Transceiver
  1 x 5 AA Battery Holder
  5 x 1.2V NiMh AA Batteries
  1 x Breadboard Half Size
*/

//NRFLite is used to make communication easy
//https://github.com/dparson55/NRFLite
#include <SPI.h>
#include <NRFLite.h>

NRFLite tank_radio;
const static uint8_t TANK_BOT_ID = 0;
const static uint8_t RADIO_CE = 10;
const static uint8_t RADIO_CSN = 9;

struct ControllerPacket {

  int16_t left_x;
  int16_t left_y;
  int16_t left_b;

  int16_t right_x;
  int16_t right_y;
  int16_t right_b;

};

ControllerPacket controller_data;

int lx_val = 0;
int ly_val = 0;
int lb_val = 0;
int rx_val = 0;
int ry_val = 0;
int rb_val = 0;

//The joystick data can be noisy so we can create a threshold for each axis
int16_t axis_threshold = 25;

//Use a timer instead of delay() in order to multitask
unsigned long tank_current;
unsigned long tank_previous;
unsigned long range_check_previous;
//Interval for main loop
long tank_interval = 10;
//Interval to check if controller is in range
long range_check_interval = 500;

void setup() {

  Serial.begin(115200);

  if (!tank_radio.init(TANK_BOT_ID, RADIO_CE, RADIO_CSN)) {
    Serial.println("NO RADIO FOUND!!!!");
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }

  SetupMotors();
  LeftStop();
  RightStop();

  Serial.println("Tank Bot!");
  delay(2000);

}


void loop() {

  tank_current = millis();

  if (tank_current - tank_previous >= tank_interval) {

    if (tank_radio.hasData()) {
      Serial.println("Found Data!");
      tank_radio.readData(&controller_data);
      //Reset range check timer
      range_check_previous = tank_current;
    }

    //If the controller is out of range or is off, Tank Bot has no data to read
    if (tank_current - range_check_previous > range_check_interval) {
      Serial.println("No Data Found.....");
      ly_val = 0;
      ry_val = 0;
      LeftStop();
      RightStop();
    }

    else {

      //Get the controller data
      ly_val = controller_data.left_y;
      ry_val = controller_data.right_y;

      //Remap the data for motor driver
      ly_val = map(ly_val, 1023, 0, -255, 255);
      ry_val = map(ry_val, 1023, 0, -255, 255);

      //Print the data we want
      Serial.print(ly_val);
      Serial.print("  :  ");
      Serial.println(ry_val);

      //Control Left Side
      if (ly_val > axis_threshold) {
        LeftForward(ly_val);
      } else if (ly_val < -axis_threshold) {
        LeftBackward(abs(ly_val));
      } else {
        LeftStop();
      }

      //Control Right Side
      if (ry_val > axis_threshold) {
        RightForward(ry_val);
      } else if (ry_val < -axis_threshold) {
        RightBackward(abs(ry_val));
      } else {
        RightStop();
      }

    }

    //End of loop
    tank_previous = tank_current;

  }
}
