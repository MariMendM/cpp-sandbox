//============================================================================
// Name        : OverloadOstreamOperator.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Overloading << operator (example with classes)
//============================================================================

#include <iostream>
using namespace std;

//----------------------------------------------------------------------------
class refrigerator {
	private:
		double temperature{0.0};
		bool power_on{true};
		bool door_open{false};
	public:
		void change_temperature(double delta);
		void open_door();
		void close_door();
		void print() const;
		void print(ostream & os) const;
};

void refrigerator::change_temperature(double delta) {temperature += delta;}
void refrigerator::open_door() { door_open = true; }
void refrigerator::close_door() { door_open = false; }
void refrigerator::print() const {
	cout << "Temperature: " << temperature << ", ";
	cout << "Power: " << (power_on ? "on" : "off") << ", ";
	cout << "Door: " << (door_open ? "open" : "closed") << endl;
}
void refrigerator::print(ostream & os) const {
	os << "Temperature: " << temperature << ", ";
	os << "Power: " << (power_on ? "on" : "off") << ", ";
	os << "Door: " << (door_open ? "open" : "closed") << endl;
}
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//overload of operator << using print(ostream &os) from class
//----------------------------------------------------------------------------
ostream& operator << (ostream & os, const refrigerator & fridge) {
	fridge.print(os);
	return os;
}
//----------------------------------------------------------------------------



int main() {

	refrigerator fridge1;

	//Let's print out class values with print()...
	cout << "1st fridge values --> ";
	fridge1.print();

	//OK! but to actually overload output ostream
	//		cout << fridge
	//we have to overload print passing ostream as: print(ostream &)
	//and create
	cout << "2nd fridge values --> " << fridge1;
	fridge1.open_door();
	cout << "3rd fridge values --> " << fridge1;


	cout << endl << "END OF PROGRAM";
	return 0;
}