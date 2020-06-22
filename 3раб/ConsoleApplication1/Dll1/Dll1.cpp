// Dll1.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

extern "C" __declspec(dllexport) 
void first_dll() {
	cout << "This is dll function" << endl;
	int a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	c = a + b;
	cout << "sum = " << c << endl;
}