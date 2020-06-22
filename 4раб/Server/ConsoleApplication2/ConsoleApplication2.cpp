// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable: 4996)

using namespace std;
SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int index) {//приймає індекс з'єднання сокет в масиві
	char msg[256];
	while (true) {
		recv(Connections[index], msg, sizeof(msg), NULL);
		for (int i = 0; i < Counter; i++) {
			if (i == index) {//щоб у клієнта, який відправив повідомлення, е вивело його ще раз
				continue;
			}
			send(Connections[i], msg, sizeof(msg), NULL);
		}
	}
}

int main(int argc, char* argv[])
{
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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);//SOCK_STREAM вказує на протокол, який встановлює з'єднання
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));//прив'язка адреси сокету; sListen(створений сокет0)
	listen(sListen, SOMAXCONN);//прослухвування сокету, (2 - максимальне допустиме число запитів)

	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);//(SOCKADDR*)&addr буде містити дані про ІР адрес клієнта

		if (newConnection == 0) {
			cout << "User connect Error\n" << endl;
		}
		else {
			cout << "Client connected" << endl;
			char msg[256] = "Hello. This is server";
			send(newConnection, msg, sizeof(msg), NULL);

			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);//створюємо потік, яким виконується функція відправки повідомлень	
		}
	}
	system("pause");
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
