#include <iostream>
// #include <chrono>
// #include <thread>
#include <wiringPi.h>
#include <softPwm.h>
#include <ncurses.h>
#include <unistd.h> //For usleep(microseconds) function

/* ============ INCLUDES ============ */
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

/* ============ LOCAL FUNCTIONS ============ */
void Motor_Init(void);
void Motor_Control(int command);
void Motor_SetOutPins(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

//Function to initialize GPIO pins
void Motor_Init()
{
    /* Initialize ncurses mode */
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); //Non-blocking input
    keypad(stdscr, TRUE);  //Enable special keys (arrows, F-keys, etc)
    
    /* Initialize WiringPi */
    if(wiringPiSetupGpio() == -1)
    {
        std::cout << "WiringPi initialization failed!" << std::endl;
    }
    else{}

    /* Digital output pins */
    pinMode(MOTOR_1A, OUTPUT);
    pinMode(MOTOR_1B, OUTPUT);
    pinMode(MOTOR_2A, OUTPUT);
    pinMode(MOTOR_2B, OUTPUT);

    /* PWM output pins */
    softPwmCreate(PWM_MOTOR_1, PWM_MIN, PWM_MAX);
    softPwmCreate(PWM_MOTOR_2, PWM_MIN, PWM_MAX);
}

//Function to set the output pins that control the motor
void Motor_SetOutPins(uint8_t cmd_1A, uint8_t cmd_1B, uint8_t cmd_2A, uint8_t cmd_2B, uint8_t speed)
{
    digitalWrite(MOTOR_1A, cmd_1A);
    digitalWrite(MOTOR_1B, cmd_1B);
    softPwmWrite(PWM_MOTOR_1, speed);

    digitalWrite(MOTOR_2A, cmd_2A);
    digitalWrite(MOTOR_2B, cmd_2B);
    softPwmWrite(PWM_MOTOR_2, speed);
}

//Function to control the motor
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

int main()
{
    int ch;
    bool isRunning = TRUE;
    bool isKeyPressed = FALSE;

    Motor_Init();

    printw("Press 'q' to quit.\nPress 'f' to move the motors forward.\nPress 'b' to move the motors backwards.\nPress 's' to stop the motors.");

    while(isRunning)
    {
        ch = getch(); //Get the current key press (non-blocking)

        switch(ch)
        {
            case 'q':
                isRunning = FALSE;
                break;
            
            case 'f':
                if(!isKeyPressed)
                {
                    isKeyPressed = true;
                    Motor_Control(ch);
                    printw("Forward command.\n");
                }
                else{}
                break;

            case 'b':
                if(!isKeyPressed)
                {
                    isKeyPressed = true;
                    Motor_Control(ch);
                    printw("Backward command.\n");
                }
                else{}
                break;

            case 's':
                if(!isKeyPressed)
                {
                    isKeyPressed = true;
                    Motor_Control(ch);
                    printw("Stop command.\n");
                }
                else{}
                break;

            case ERR:
                if(isKeyPressed)
                {
                    isKeyPressed = FALSE;
                    printw("A key was released.\n");
                }
                else{}
                break;

            default:
                break;
        }

        refresh(); //Refresh screen to show updates
        usleep(100000); //Delay yo reduce CPU usage 100000 us = 0.1s
    }

    endwin(); //End ncurses mode
    return 0;
}