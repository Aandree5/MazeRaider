// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	cout << "Objective:-" << endl;
	cout << "User need to complete this maze before 100% complete" << endl;
	for (int i = 0; i <=100; i++)
	{
		cout << "Time Left ";
		cout << i << "%";
		Sleep(6000);
		system("cls");
		
	}
	cout << "Game over!";
}

