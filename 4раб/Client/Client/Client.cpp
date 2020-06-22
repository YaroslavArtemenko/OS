#include "pch.h"
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable: 4996)

using namespace std;

SOCKET Connection;

void ClientHandler() {
	char msg[256];
	while (true) {
		recv(Connection, msg, sizeof(msg), NULL);
		cout << msg << endl;
	}
}

int main(int argc, char* argv[])
{
	//WSAStartup
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Library error" << endl;
		exit(1);
	}
	//інформація про адресу сокета
	SOCKADDR_IN addr;//для збереження адреси(для ІР)
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//Зберігає ІР адресу
	addr.sin_port = htons(1111);//Порт для ідентифікації програми
	addr.sin_family = AF_INET; //сімейство протоколів

	//з'єднання з сервером
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Error. Failed connect to server.\n";
		return 1;
	}
	cout << "Connected\n";
	

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	char msg1[256];
	while (true) {
		cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}