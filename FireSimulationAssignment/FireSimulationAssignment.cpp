#include "Console.h"

#include <iostream>

#include "Forest.h"

using namespace std;

int main()
{
	//int firstvalue = 5;
	//int secondvalue = 15;
	//int* p1 = &firstvalue;
	//int* p2 = &secondvalue;

	//cout << "firstvalue: " << firstvalue << endl;
	//cout << "secondvalue: " << secondvalue << endl;
	//cout << "p1: " << p1 << endl;
	//cout << "p2: " << p2 << endl;
	//cout << "*p1: " << *p1 << endl;
	//cout << "*p2: " << *p2 << endl;

	//cout << "-------------" << endl;
	//
	//p1 = &firstvalue;  // p1 = address of firstvalue
	//cout << "p1: " << p1 << endl;
	//cout << "-------------" << endl;
	//
	//p2 = &secondvalue; // p2 = address of secondvalue
	//cout << "p2: " << p2 << endl;
	//cout << "-------------" << endl;
	//
	//*p1 = 10;          // value pointed to by p1 = 10
	//cout << "*p1: " << *p1 << endl;
	//cout << "-------------" << endl;
	//
	//*p2 = *p1;         // value pointed to by p2 = value pointed to by p1
	//cout << "*p2: " << *p2 << endl;
	//cout << "-------------" << endl;
	//
	//p1 = p2;           // p1 = p2 (value of pointer is copied)
	//cout << "p1: " << p1 << endl;
	//cout << "-------------" << endl;
	//
	//*p2 = 20;          // value pointed to by p2 = 20
	//cout << "*p2: " << *p2 << endl;
	//cout << "-------------" << endl;
	//cout << "*p1: " << *p1 << endl;
	//cout << "-------------" << endl;

	Forest map = Forest();
	
	map.CreateForest();
	map.Print();

	getchar();
}
