#include <Arduino.h>
#include <MotorService.h>

/**
 * @brief Intializes motor pins.
 * 
 */
void setupMotor(){
    // Setup Left Motor:
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    pinMode(MOTOR_S, OUTPUT);
}

/**
 * @brief Stablishes the PWM of the motor.
 * 
 * @param speed   Value between -255 y 255.
 */
void moveMotor(int16_t speed){
    // Backwards
    if (speed < 0)
    {
        digitalWrite(MOTOR_A, HIGH);
        digitalWrite(MOTOR_B, LOW);
        speed = -speed;
    }

    // Forward
    else if(speed > 0)
    {
        digitalWrite(MOTOR_A, LOW);
        digitalWrite(MOTOR_B, HIGH);
    }

    // Stop
    else
    {
        digitalWrite(MOTOR_A, LOW);
        digitalWrite(MOTOR_B, LOW);
    }

    // Speed
    analogWrite(MOTOR_S, speed);
}