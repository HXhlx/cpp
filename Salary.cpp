#include<iostream>
#include "Salary.h"
using namespace std;
void Salary::Input()
{
	cin >> basic >> duty >> bonus;
}
void Salary::Print()
{
	Staff::Print();
	cout << basic << ends << duty << ends << bonus << ends << endl;
}
