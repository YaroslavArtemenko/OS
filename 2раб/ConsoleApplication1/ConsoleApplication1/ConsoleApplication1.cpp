// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void dowork(int a, int b)
{
	this_thread::sleep_for(chrono::milliseconds(3000));
	cout << "===================\t" << "DoWork Started\t=========" << endl;	
	this_thread::sleep_for(chrono::milliseconds(5000));
	cout << "a + b = " << a + b << endl;
	this_thread::sleep_for(chrono::milliseconds(3000));
	cout<< "===================\t" << "DoWork Stopped\t=========" << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");

	thread th(dowork,2,3);
	for (size_t i = 0; i<30; i++)
	{
		cout << "ID потока = " << this_thread::get_id() << "\tmain " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th.join();
	return 0;
}
