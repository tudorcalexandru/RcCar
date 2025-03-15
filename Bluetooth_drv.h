/*********** Bluetooth_drv.h ************/

/* ============ INCLUDES ============ */
#include <iostream>
#include <cstring>
#include <stdbool.h>
#include <unistd.h> //For usleep(microseconds) function
#include <ncurses.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>



/* ============ DEFINES ============ */

/* ============ GLOBAL FUNCTIONS ============ */
void Bluetooth_Init(void);
void Bluetooth_EstablishConnection(void);
void Bluetooth_ReadData(void);
void Bluetooth_CloseConnection(void);

/* ============ LOCAL FUNCTIONS ============ */

/* ============ LOCAL VARIABLES ============ */
static struct sockaddr_rc local_addr;
static struct sockaddr_rc remote_addr;
static socklen_t opt;
static char   client_addr[18];
static char   buffer[1024];
static int    server_sock;
static int 	  client_sock;
