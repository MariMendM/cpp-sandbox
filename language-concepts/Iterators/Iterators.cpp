//============================================================================
// Name        : Iterators.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of iterators (RW, RO, Reverse, Stream, Inserters)
//============================================================================

#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <iterator> //stream iterators need it; other don't
using namespace std;


//To print whichever container used
template <class T> void print (string separator, T var) {
	cout << separator << " ";
	for (auto it : var) { cout << setw (4) << it << " "; }
	cout << endl;
};


int main() {

	//RW ITERATORS -------------------------------------------
		vector<int> intV = {1, 2, 3};
		vector<int> intV2; //intV2.begin() == intV2.end()

		//Declaring...
		vector<int>::iterator it1 = intV.begin();
		auto it2 = intV.begin();

		//Using in iterations...
		for (size_t i=0; i<intV.size();i++) //Works, but it is not recommended!
			cout << " =" << intV[i];
		cout << endl;
		for (vector<int>::iterator it3=intV.begin(); it3 != intV.end(); it3++)
			cout << " *" << *it3;
		cout << endl;
		for (auto it4: intV)
			cout << " #" << it4;
		cout << endl;

		//Remember that <it = vec.begin()> means <it = 1>, not zero;
		//so notation <*it> means "first element of vec" which is vec[0];
		//but <vec(it)> is actually vec[1]! do not mix notations!

		cout << " %" << (*it1); it1++; cout << " %" << (*it1) << endl;

		//Iterators cannot be printed; but its distance from beginning can:
		for (auto it5 = intV.begin(); it5 != intV.end(); it5++)
			cout << "(" << it5-intV.begin() << ") =" << *it5 << endl;

		*it2 = 15;
		print("!", intV);


	//READONLY ITERATORS -------------------------------------
		vector<int>::const_iterator itV10 = intV.cbegin();
		auto itV11 = intV.cbegin();
		//intV.cend();
		//++itV10; 		//OK
		//*itV10; 		//OK
		//*itV10 = 15;	//NOK, compiler error


	//REVERSE ITERATORS --------------------------------------
	//Like RW ITERATORS, but in reverse order (end to begin)
		vector<int>::reverse_iterator itV20 = intV.rbegin();
		auto itV21 = intV.rbegin();
		//intV.rend();


	//READONLY REVERSE ITERATORS -----------------------------
	//Like READONLY ITERATORS, but in reverse order (end to begin)
		vector<int>::const_reverse_iterator itV30 = intV.crbegin();
		auto itV31 = intV.crbegin();
		//intV.crend();


	//INSERT ITERATORS ---------------------------------------
		vector<int> intV3;

		auto it1_intV3 = back_inserter(intV3); //does the same as push_back through iterators
		for (int i=10; i<40; i+=10)
			*it1_intV3 = i;
		print("-", intV3);

		list<int> intL1 {10, 20, 30}; //vector does not implement push_front!
		auto it1_intL1 = front_inserter(intL1); //does the same as push_front through iterators
		*it1_intL1 = 5;
		print("@", intL1);

		auto it2_intV3_middle = intV3.begin();
		auto it2_intV3 = inserter(intV3, ++it2_intV3_middle); //insert element in any position
		*it2_intV3 = 15;
		print("$", intV3);
		++it2_intV3_middle;
		++it2_intV3_middle;
		it2_intV3 = inserter(intV3, it2_intV3_middle); //insert element in any position
		*it2_intV3 = 25;
		print("~", intV3);


	//STREAM ITERATORS ---------------------------------------
		//#include <iterator>
		ostream_iterator<int> itOS1(cout);
		*itOS1 = 1;
		*itOS1 = 4;
		*itOS1 = 7;
		cout << endl;

		ostream_iterator<int> itOS2(cout,"-");
		*itOS2 = 7;
		*itOS2 = 8;
		*itOS2 = 9;
		cout << endl;

		cout << "Type a digit: ";
		istream_iterator<int> itIS1(cin);
		int x = *itIS1;
		cout << "Typed " << x << endl;

		cout << "Type something (until ENTER + CTRL+Z + ENTER in Win CMD): ";
		vector<string> vecS;
		auto it_vecS = back_inserter(vecS);
		istream_iterator<string> itIS2(cin);
		istream_iterator<string> eof; //empty iterator
		while (itIS2 != eof) {
			it_vecS = *itIS2;
			itIS2++;
		}
		print ("Você digitou ", vecS);


		cout << "END OF PROGRAM" << endl;
		return 0;
}
