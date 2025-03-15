/*********** Bluetooth_drv.cpp ************/

/* ============ INCLUDES ============ */
#include "Bluetooth_drv.h"

/* ============ GLOBAL FUNCTIONS ============ */
void Bluetooth_Init(void)
{
	bdaddr_t any_addr = {{0, 0, 0, 0, 0, 0}};

    local_addr = {0};
	remote_addr = {0};
	opt = sizeof(remote_addr);
	memset(client_addr, 0, sizeof(client_addr));
	memset(buffer     , 0, sizeof(buffer));

	system("sudo sdptool add --channel=1 SP"); //Add SPP (Serial Port Profile) advertisment service
	//system("sudo rfcomm watch hci0");
	//Create RFCOMM socket
						/* Domain        Type        Protocol   */
	server_sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	client_sock = -1;

	local_addr.rc_family  = AF_BLUETOOTH;
	bacpy(&local_addr.rc_bdaddr, &any_addr);
	local_addr.rc_channel = (uint8_t)1;  //Bluetooth channel 1

	bind(server_sock, (struct sockaddr *) &local_addr, sizeof(local_addr));
	listen(server_sock, 1);

	std::cout << "Waiting for connection...\n";
	//printw("[WAITING] Waiting for connection...\n");
}

void Bluetooth_EstablishConnection(void)
{
	std::cout << "[WAITING] Waiting for Bluetooth client to connect...\n";
	//printw("[WAITING] Waiting for Bluetooth client to connect...\n");
	client_sock = accept(server_sock, (struct sockaddr *) &remote_addr, &opt);

	if(client_sock < 0) // client socket not yet connected
	{
		std::cout << "[ERROR] Accept failed" << "\n";
		//printw("[ERROR] Accept failed!\n");
	}
	else
	{
		ba2str(&remote_addr.rc_bdaddr, client_addr);
		std::cout << "[CONNECTED] Client connected: " << client_addr << "\n";
		//printw("[CONNECTED] Client connected: %s\n", client_addr);
	}
}

void Bluetooth_ReadData(void)
{
	int bytes_read = read(client_sock, buffer, sizeof(buffer));

	if(bytes_read > 0)
	{
		std::cout << "Received: " << buffer << "\n";
		//printw("Received:  %s\n", buffer);
	}
	else{}
}

void Bluetooth_CloseConnection(void)
{
	close(client_sock);
	close(server_sock);
}
