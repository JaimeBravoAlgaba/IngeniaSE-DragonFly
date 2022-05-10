#ifndef __MOTOR_SERVICE__
    #define __MOTOR_SERVICE__

    #define SPEED  150

    // PINOUT:
    #define MOTOR_A D3  // Motor, input A.
    #define MOTOR_B D4  // Motor, input B.
    #define MOTOR_S D5  // Motor, speed (PWM).

    // FUNCTIONS:
    void setupMotor();
    void moveMotor(int16_t speed);
#endif