/*********** Main.cpp ************/


/* ============ INCLUDES ============ */
#include "Motor_mng.h"
#include "Bluetooth_drv.h"


/* ============ LOCAL FUNCTIONS ============ */
void App_Init(void)
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
        std::cout << "WiringPi initialization failed!\n";
    }
    else{}

    printw("Press 'q' to quit.\nPress 'f' to move the motors forward.\nPress 'b' to move the motors backwards.\nPress 's' to stop the motors.\n");
}

int main()
{
    int ch;
    bool isRunning = TRUE;
    bool isKeyPressed = FALSE;

    App_Init();
    Bluetooth_Init();
    Bluetooth_EstablishConnection();
    //Motor_Init();

    while(1)
    {
		Bluetooth_ReadData();
		
        /*ch = getch(); //Get the current key press (non-blocking)

        switch(ch)
        {
            case 'q':
                isRunning = FALSE;
                break;
            
            case 'f':
                if(!isKeyPressed)
                {
                    isKeyPressed = TRUE;
                    Motor_Control(ch);
                    printw("Forward command.\n");
                }
                else{}
                break;

            case 'b':
                if(!isKeyPressed)
                {
                    isKeyPressed = TRUE;
                    Motor_Control(ch);
                    printw("Backward command.\n");
                }
                else{}
                break;

            case 's':
                if(!isKeyPressed)
                {
                    isKeyPressed = TRUE;
                    Motor_Control(ch);
                    printw("Stop command.\n");
                }
                else{}
                break;

            case ERR:
                if(isKeyPressed)
                {
                    isKeyPressed = TRUE;
                    printw("A key was released.\n");
                }
                else{}
                break;

            default:
                break;
        }*/

        refresh(); //Refresh screen to show updates
        usleep(100000); //Delay yo reduce CPU usage 100000 us = 0.1s
    }

    endwin(); //End ncurses mode
    Bluetooth_CloseConnection();
    return 0;
}
