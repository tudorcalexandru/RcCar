/*********** Motor_mng.cpp ************/

/* ============ INCLUDES ============ */
#include "Motor_mng.h"



/* ============ GLOBAL FUNCTIONS ============ */
//Initialize GPIO pins
void Motor_Init()
{
    /* Digital output pins */
    pinMode(MOTOR_1A, OUTPUT);
    pinMode(MOTOR_1B, OUTPUT);
    pinMode(MOTOR_2A, OUTPUT);
    pinMode(MOTOR_2B, OUTPUT);

    /* PWM output pins */
    softPwmCreate(PWM_MOTOR_1, PWM_MIN, PWM_MAX);
    softPwmCreate(PWM_MOTOR_2, PWM_MIN, PWM_MAX);
}

//Motor control commands
void Motor_Control(int command)
{
    switch(command)
    {
        case 'f':   //forward
            Motor_SetOutPins(HIGH, LOW, HIGH, LOW, PWM_25);
            break;
        case 'b':   //backward
            Motor_SetOutPins(LOW, HIGH, LOW, HIGH, PWM_25);
            break;
        case 'g':
            Motor_SetOutPins(LOW, HIGH, LOW, HIGH, PWM_25);
            sleep(2);
            Motor_SetOutPins(LOW, HIGH, LOW, HIGH, PWM_50);
            sleep(2);
            Motor_SetOutPins(LOW, HIGH, LOW, HIGH, PWM_75);
            sleep(2);
            break;
        case 's':   //Stop
            Motor_SetOutPins(LOW, LOW, LOW, LOW, PWM_MIN);
            break;
        default:   //Stop
            Motor_SetOutPins(LOW, LOW, LOW, LOW, PWM_MIN);
            break; 
    }
}

/* ============ LOCAL FUNCTIONS ============ */
//Set the output pins that control the motor
static void Motor_SetOutPins(uint8_t cmd_1A, uint8_t cmd_1B, uint8_t cmd_2A, uint8_t cmd_2B, uint8_t speed)
{
    digitalWrite(MOTOR_1A, cmd_1A);
    digitalWrite(MOTOR_1B, cmd_1B);
    softPwmWrite(PWM_MOTOR_1, speed);

    digitalWrite(MOTOR_2A, cmd_2A);
    digitalWrite(MOTOR_2B, cmd_2B);
    softPwmWrite(PWM_MOTOR_2, speed);
}