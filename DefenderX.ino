/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define INCLUDE_DABBLEINPUTS_MODULE

/*
  For Arduino Mega library uses SoftwareSerial,hence pin 13 and pin 14 are used
  as RX and TX pins respectively on SoftwareSerial.Hence with arduino Mega
  follow below connections for bluetooth.
  Mega  - BLUETOOTH
  14    - TX
  15    - RX

   You can reduce the size of library compiled by enabling only those modules that you want
   to use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more: https://thestempedia.com/docs/dabble/motor-control-module/
*/

// These are the libraries for Bluetooth
#include <Dabble.h>
#include <HC05.h>

// This is the library for the servo that contains the class Servo and all the
// functions
#include <Servo.h>

// This is the library for the motor SparkFun TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// One SparkFun TB6612
// These motors are for wheels
// Motor 1
#define PWMA 2
#define AIN1 4
#define AIN2 3

// Motor 2
#define PWMB 5
#define BIN1 6
#define BIN2 7

// Another SparkFun TB6612
// Motor 3
// This motor is for gun 
#define PWMC 9
#define CIN1 10
#define CIN2 11

// The exception of STBY which the Redbot controls with a physical switch
#define STBY1 8
#define STBY2 12

// These constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;
const int offsetC = 1;

// Servo 1
#define servoPin1 22

// Servo 2
#define servoPin2 23

// Create Servo objects
Servo servo1;
Servo servo2;

// Position of gun
int pos = 65;

// RGB-LED 1
int red_light_pin1 = 30;
int green_light_pin1 = 31;
int blue_light_pin1 = 32;

// RGB-LED 2
int red_light_pin2 = 33;
int green_light_pin2 = 34;
int blue_light_pin2 = 35;

// RGB-LED 3
int red_light_pin3 = 36;
int green_light_pin3 = 37;
int blue_light_pin3 = 38;

// RGB-LED 4
int red_light_pin4 = 39;
int green_light_pin4 = 40;
int blue_light_pin4 = 41;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY1);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY1);
Motor motor3 = Motor(CIN1, CIN2, PWMC, offsetC, STBY2);

void setup() 
    {
       // make sure your Serial Monitor is also set at this baud rate.
       Serial.begin(2000000);
       //set bluetooth name of your device
       Dabble.begin(9600);
       //set RGB-LED
       pinMode(red_light_pin1, OUTPUT);
       pinMode(green_light_pin1, OUTPUT);
       pinMode(blue_light_pin1, OUTPUT);
       pinMode(red_light_pin2, OUTPUT);
       pinMode(green_light_pin2, OUTPUT);
       pinMode(blue_light_pin2, OUTPUT);
       pinMode(red_light_pin3, OUTPUT);
       pinMode(green_light_pin3, OUTPUT);
       pinMode(blue_light_pin3, OUTPUT);
       pinMode(red_light_pin4, OUTPUT);
       pinMode(green_light_pin4, OUTPUT);
       pinMode(blue_light_pin4, OUTPUT);
       //Attaches the pin to the servo object
       servo1.attach(servoPin1);
       servo2.attach(servoPin2);
       servo2.write(65);
    }

void loop() 
    {
        //this function is used to refresh data obtained from smartphone.Hence calling this 
        //function is mandatory in order to get data properly from your mobile.
        Dabble.processInput();

        //
        servo1.write(170);

        if (GamePad.isUpPressed())
          {
             Serial.print("KeyPressed: ");
             Serial.print("Up"); 
             forward(motor1, motor2, 255);
          }

        else if (GamePad.isDownPressed())
          {
             Serial.print("KeyPressed: ");
             Serial.print("Down");
             back(motor1, motor2, -255);
          }

        else if (GamePad.isLeftPressed())
          {
             Serial.print("KeyPressed: ");
             Serial.print("Left");
             forward(motor1, motor1, 255);
             forward(motor2, motor2, -255);
          }

        else if (GamePad.isRightPressed())
          {
             Serial.print("KeyPressed: ");
             Serial.print("Right");
             forward(motor2, motor2, 255);
             forward(motor1, motor1, -255);
          }
          
        else if (GamePad.isStartPressed())
        {
          Serial.print("KeyPressed: ");
          Serial.print("Start");
          analogWrite(red_light_pin1, 255);
          analogWrite(green_light_pin1, 255);
          analogWrite(blue_light_pin1, 0);
          analogWrite(red_light_pin2, 255);
          analogWrite(green_light_pin2, 255);
          analogWrite(blue_light_pin2, 0);
          analogWrite(red_light_pin3, 255);
          analogWrite(green_light_pin3, 255);
          analogWrite(blue_light_pin3, 0);
          analogWrite(red_light_pin4, 255);
          analogWrite(green_light_pin4, 255);
          analogWrite(blue_light_pin4, 0);
        }
        // Lights
        else if (GamePad.isSelectPressed())
        {
          Serial.print("KeyPressed: ");
          Serial.print("Select");
          analogWrite(red_light_pin1, LOW);
          analogWrite(green_light_pin1, LOW);
          analogWrite(blue_light_pin1, LOW);
          analogWrite(red_light_pin2, LOW);
          analogWrite(green_light_pin2, LOW);
          analogWrite(blue_light_pin2, LOW);
          analogWrite(red_light_pin3, LOW);
          analogWrite(green_light_pin3, LOW);
          analogWrite(blue_light_pin3, LOW);
          analogWrite(red_light_pin4, LOW);
          analogWrite(green_light_pin4, LOW);
          analogWrite(blue_light_pin4, LOW);  
        }
        
        else if (GamePad.isTrianglePressed())
        {
          Serial.print("Triangle");
          forward(motor3, motor3, 255);
        }
        
        else if (GamePad.isCrossPressed())
        {
          Serial.print("Cross");
          servo1.write(0);
        }

        else if (GamePad.isSquarePressed())
        {
          Serial.print("Square");
          pos += 2;
          servo2.write(pos);
        }

        else if (GamePad.isCirclePressed())
        {
          Serial.print("Circle");
          pos -= 2;
          servo2.write(pos);
        }
        
        else 
        {
             brake(motor1, motor2);
             brake(motor1, motor1);
             brake(motor2, motor2);
             brake(motor3, motor3);
        }
          
        delay(10);   
     }
     
