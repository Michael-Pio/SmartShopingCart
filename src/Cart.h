#include<iostream>
#include<Motor.h>
#include<Arduino.h>
#include <WString.h>

class Cart{
public:
    int MotorLPinA = D4;
    int MotorLPinB = D5;
    int MotroLPinSpeed = D6;
    int MotorRPinA = D3;
    int MotorRPinB = D2;
    int MototRPinSpeed = D6;


// Define the motor pins
// #define ENA D6
// #define LM1 D3
// #define LM2 D2
// #define RM1 D4
// #define RM2 D5
// #define ENB D6


public:
    int TrigPin = D1;
    int EchoPin = D0;

    int obstacleInFront = 100;

private:
    int previousMillis = 0;
    int interval = 3000;

public:
    Motor MotorLeft = Motor(MotorLPinA,MotorLPinB ,MotroLPinSpeed);
    Motor MotorRight = Motor(MotorRPinA,MotorRPinB ,MototRPinSpeed);

public:
    Cart();
    void Move(String direction, int speed);
    void loop();

  private:
  long getDistance();
};