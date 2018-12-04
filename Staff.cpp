#include<iostream>
#include<list>
#include "Staff.h"
using namespace std;
void Staff::Input()
{
	static int n;
	cin >> id >> name >> gender >> age >> department >> occupation >> phone >> adress;
	n++;
	wage = 100 * 100 + n;
}
void Staff::Print()
{
	cout << endl;
	cout << wage << ends << id << ends << name << ends << gender << ends << age << ends << department << ends << occupation << ends << phone << ends << adress << ends << flush;
}
