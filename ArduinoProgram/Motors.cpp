#include "Motors.h"
#include "Data.h"

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>

#define IN1  7    // K1,K2 motor direction
#define IN2  8    // K1,K2 motor direction
#define IN3  9    // K3,K4 motor direction
#define IN4  10   // K3,K4 motor direction
#define ENA  5    // Needs to be a PWM pin to be able to control motor speed
#define ENB  6    // Needs to be a PWM pin to be able to control motor speed

// Speed control ------------------------------------------

void clamp(int* x, int min, int max) {
  if(*x < min) *x = min;
  if(*x > max) *x = max;
}

//Sets the speed of each motor (an integer between -255 and 255)
void setSpeed(int leftSpeed, int rightSpeed) {

  //The speed shoud always be between -255 and 255
  clamp(&leftSpeed, -255, 255);
  clamp(&rightSpeed, -255, 255);

  //Sets the speed for each motor
  analogWrite(ENA, abs(leftSpeed));
  analogWrite(ENB, abs(rightSpeed));

  //Sets the direction of rotation for each motor
  digitalWrite(IN1, leftSpeed > 0);
  digitalWrite(IN2, leftSpeed < 0);
  digitalWrite(IN3, rightSpeed > 0);
  digitalWrite(IN4, rightSpeed < 0);
}

// High level control functions -----------------------------

// With corrections due to imperfections
// in the cardboard robot and bad cabling

void forward() {
  setSpeed(-252, 255);
}

void backward() {
  setSpeed(252, -255);
}

void turnLeft() {
  setSpeed(-255,-255);
}

void turnRight() {
  setSpeed(255,255);
}

// Init ----------------------------------------------------

void initMotors() {
  
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);

}

// Update -------------------------------------------------

//Updates the motors speeds according to the forwardInput and the turnInput
void updateMotors() {

   if(fabsf(turnInput) > 0.1f) {
     if(turnInput > 0)
       turnRight();
     else
       turnLeft();
   } 
   else {
     if(forwardInput > 0)
       forward();
     else
       backward();
   }
}
