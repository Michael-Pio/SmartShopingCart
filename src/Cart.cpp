#pragma once

#include<Arduino.h>
#include<Cart.h>

Cart::Cart()
{
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
}

void Cart::Move(String direction, int speed){
    speed = map(speed, 0, 100, 0, 255); // Scale speed from 0-100 to 0-255

    if(direction == "FWD"){
        if(obstacleInFront>20){
            MotorLeft.Forward(speed);
            MotorRight.Forward(speed);
        }
    } else if (direction == "BWD"){
        MotorLeft.Backward(speed);
        MotorRight.Backward(speed);
    } else if (direction == "LFT"){
        MotorLeft.Backward(speed);
        MotorRight.Forward(speed);
    } else if (direction == "RGT"){
        MotorLeft.Forward(speed);
        MotorRight.Backward(speed);
    } else {
        MotorLeft.Forward(0);
        MotorRight.Forward(0);
    }
}

void Cart::loop(){
    unsigned long currentMillis = millis();
    MotorLeft.updateMotor();
    MotorRight.updateMotor();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        obstacleInFront = getDistance();
    }
}

long Cart::getDistance() {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    long duration = pulseIn(EchoPin, HIGH);
    Serial.print("Distance Measured : ");
    Serial.println(duration * 0.034 / 2);
    return duration * 0.034 / 2;  // Convert to distance in cm
}