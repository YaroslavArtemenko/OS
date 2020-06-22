﻿// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;


int main()
{
	typedef void(*f_class) ();
	HMODULE hlib = LoadLibrary(TEXT("Dll1.dll"));
	if (hlib == NULL)
	{
		cout << "Library don`t download\n";
	}
	if (hlib != NULL)
	{
		cout << "Library downloaded\n";
	}
	_getch();

	f_class first_dll = (f_class)GetProcAddress(hlib, "first_dll");

	if (hlib == NULL)
	{
		cout << "Library don`t download\n";
	}
	if (hlib != NULL)
	{
		first_dll();
	}
	FreeLibrary(hlib);	
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
