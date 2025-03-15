/*********** Motor_mng.h ************/

/* ============ INCLUDES ============ */
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <unistd.h> //For usleep(microseconds) function

/* ============ DEFINES ============ */
//Motor driver pins
#define PWM_MOTOR_1 (int)18
#define MOTOR_1A    (int)23
#define MOTOR_1B    (int)24

#define PWM_MOTOR_2 (int)19
#define MOTOR_2A    (int)27
#define MOTOR_2B    (int)22


//PWM control values
#define PWM_MIN     (int)0
#define PWM_MAX     (int)100
#define PWM_20      (int)20
#define PWM_25      (int)25
#define PWM_50      (int)50
#define PWM_75      (int)75

/* ============ GLOBAL FUNCTIONS ============ */
extern void Motor_Init(void);
extern void Motor_Control(int command);

/* ============ LOCAL FUNCTIONS ============ */
static void Motor_SetOutPins(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
