//Created by Michael Pio @14/11/2024

#pragma once
#include<Motor.h>
#include<Arduino.h>

Motor::Motor(int PinA ,int PinB ,int SpeedPin){
    this->PinA = PinA;
    this->PinB = PinB;
    this->SpeedPin = SpeedPin;

    pinMode(PinA, OUTPUT);
    pinMode(PinB, OUTPUT);
    pinMode(SpeedPin , OUTPUT);
    resetMotor();
}

// Motor states
enum MotorState { STOPPED, FORWARD, BACKWARD };
MotorState motorState = STOPPED;

unsigned long motorStartTime = 0;
const unsigned long motorRunDuration = 500;  // Duration in milliseconds

void Motor::Forward(int speed) {
    motorState = FORWARD;
    digitalWrite(SpeedPin,speed);
    digitalWrite(PinA, HIGH);
    digitalWrite(PinB, LOW);
    motorStartTime = millis();
}

void Motor::Backward(int speed) {
    motorState = BACKWARD;
    digitalWrite(SpeedPin,speed);
    digitalWrite(PinA, LOW);
    digitalWrite(PinB, HIGH);
    motorStartTime = millis();
}

void Motor::updateMotor() {
    if (motorState != STOPPED && millis() - motorStartTime >= motorRunDuration) {
        resetMotor();
    }
}

void Motor::resetMotor() {
    digitalWrite(PinA, 0);
    digitalWrite(PinB, 0);
    digitalWrite(SpeedPin , 0);
    motorState = STOPPED;
}