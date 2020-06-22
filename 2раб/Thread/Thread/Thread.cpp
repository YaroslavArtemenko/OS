#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h>

using namespace std;
float counter;
int i;
CRITICAL_SECTION cs;
int counter_for_flag = 0;
long double function_rozenbrok(double x, double y);
long double diff_central_po_x(float x, float y);
long double diff_central_po_y(float x, float y);
DWORD WINAPI SynchThread(LPVOID pvoid);
DWORD WINAPI AsynchThread(LPVOID pvoid);
HANDLE stopped1, stopped2;

void ShowMenu()
{
	system("cls");
	printf("1 - Synch threads\n");
	printf("2 - Asynch threads\n");
	printf("3 - Quit\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	//int a;
	HANDLE hndl1, hndl2;
	int q;
	int iItem;
	ShowMenu();
	cin >> iItem;
	
	while (TRUE)
	{
		switch (iItem)
		{
		case 1:
			InitializeCriticalSection(&cs);
			hndl1 = CreateThread(NULL, 0, SynchThread, NULL, 0, NULL);
			hndl2 = CreateThread(NULL, 0, SynchThread, NULL, 0, NULL);
			WaitForSingleObject(hndl1, INFINITE);
			WaitForSingleObject(hndl2, INFINITE);
			CloseHandle(hndl1);
			CloseHandle(hndl2);
			_getch();
			DeleteCriticalSection(&cs);
			break;
			break;
		case 2:
			printf_s("Enter thread priority ( 0 or 1, 0 - default)");
			scanf_s("%d", &q);
			hndl1 = CreateThread(NULL, 0, AsynchThread, NULL, 0, NULL);
			SetThreadPriority(hndl1, q);
			hndl2 = CreateThread(NULL, 0, AsynchThread, NULL, 0, NULL);
			CloseHandle(hndl1);
			CloseHandle(hndl2);
			_getch();
			break;
			break;
				
		case 3:
			return 0;
		}
	}
	
	return 0;
}
DWORD WINAPI SynchThread(LPVOID pvoid)
{
	char symbol_to_stop;
	char symbol_to_resume;
	bool bool_flag = true;
	HANDLE temporary_value = NULL;
	counter = 0.1;
	counter_for_flag = 0;
	while (counter <= 2)
	{	
		if (bool_flag = false) {
			counter_for_flag++;
			if (counter_for_flag == 1) {
				printf("Pause");
				break;
				SuspendThread(temporary_value);
				stopped1 = temporary_value;
				bool_flag = true;
			}
		}
		while (!TryEnterCriticalSection(&cs));
		cout << "Thread " << GetCurrentThreadId() << ": Gradient function (" << counter << "," << counter << ") = " << diff_central_po_x(counter, counter)<< diff_central_po_y(counter, counter) << endl;

		if (_kbhit()) {
			symbol_to_stop = _getch();
			if (symbol_to_stop == 'q') {
				printf("Pause\n");
				bool_flag = false;
				symbol_to_resume = _getch();
				if (symbol_to_resume == 'w') {
					printf("Resume\n");
					bool_flag = true;
				}
			}
		}
		LeaveCriticalSection(&cs);
		counter = counter + 0.1;
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI AsynchThread(LPVOID pvoid)
{
	counter = 0;
	while (counter <= 2)
	{
		cout << "Thread " << GetCurrentThreadId() << ": Gradient function (" << counter << "," << counter << ") = " << diff_central_po_x(counter, counter) << diff_central_po_y(counter, counter) << endl;
		counter = counter + 0.1;
		Sleep(500);
	}
	return 0;
}

long double function_rozenbrok(double x, double y)
{
	return 100 * pow((pow(x, 2) - y), 2) + pow((x - 1), 2);
}

long double diff_central_po_x(float x, float y) {
	double i = 0.00001;
	long double diff = (function_rozenbrok(x + i, y) - function_rozenbrok(x - i, y)) / 2;
	return diff;
}
long double diff_central_po_y(float x, float y) {
	double i = 0.00001;
	long double diff = (function_rozenbrok(x, y + i) - function_rozenbrok(x, y - i)) / 2;
	return diff;
}