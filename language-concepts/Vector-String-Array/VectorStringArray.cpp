/============================================================================
// Name        : VectorStringArray.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of Vector / Array / BuiltIn Array / String / C-Style String
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cctype>
using namespace std;

int main() {

	//-------------------------------------------------------------------------------------
	cout << "VECTOR .........." << endl;
	//-------------------------------------------------------------------------------------
	//- Allocated into HEAP
	//-------------------------------------------------------------------------------------
	vector<int> V1 {10, 20, 30, 40};

	//Iterating
		//OU ... - menos recomendado
		cout << "\n#";
		for (size_t i=0; i<V1.size(); i++) cout << V1[i] << " "; //remember! V1.size() is unsigned; better not use int to declare 'i'

		//... OU ...
		cout << "\n@";
		for (vector<int>::iterator iter = V1.begin(); iter != V1.end(); iter++) cout << (*iter) << " ";

		//... OU
		cout << "\n*";
		for (auto v: V1) cout << v << " ";

	//Acessing
		V1[2] = 25;			//ok
		//cout << V1[10];	//undefined behavior; prints something!
		//V1[10] = 0;		//error; program stops working!
		
	cout << "\n\n";
	//-------------------------------------------------------------------------------------
	
	

	//-------------------------------------------------------------------------------------
	cout << "ARRAY ..........." << endl;
	//-------------------------------------------------------------------------------------
	//- Lower level version of vector
	//- More efficient than vector and string cause it is allocated into STACK;
	//- Less flexible: size shall be decided on declaration and cannot be changed
	//- Can cause overflow depending of the size; STACK changes according to OS
	//- Shall be used when extra efficiency needs outweighs the disadvantages
	//-------------------------------------------------------------------------------------
	array<int,4> A1 {10, 20, 30, 40};

	//Iterating
		//OU ... - menos recomendado
		cout <<"\n#";
		for (string::size_type i=0; i<A1.size(); i++) cout << A1[i] << " ";
		
		//... OU
		cout <<"\n@";
		for (auto a: A1) cout << a << " ";

	//Acessing
		A1[2] = 25;			//ok
		//cout << A1[10];	//undefined behavior; prints something!
		//A1[10] = 0;		//undefined behavior!

	cout << "\n\n";
	//-------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------
	cout << "BUILT-IN ARRAY .........." << endl;
	//-------------------------------------------------------------------------------------
	//- Inherited from C, have the same structure as ARRAY
	//- Do not have SIZE member function
	//- Can be stored into HEAP or STACK
	//-------------------------------------------------------------------------------------
	//STACK
		int BIA1[] = {10, 20, 30};
		int BIA2[3]; BIA2[0] = 40; BIA2[1] = 50; BIA2[2] = 60;
	//HEAP
		int *BIA3 = new int[3]; BIA3[0] = 40; BIA3[1] = 50; BIA3[2] = 60; delete [] BIA3;

	//Calculating size
		int BIA1Size = sizeof(BIA1)/sizeof(BIA1[0]);

	//Iterating
		//OR ...
		cout << "\n#";
		for (int i=0; i<BIA1Size; i++) cout << BIA1[i] << " ";

		//... OR
		cout << "\n@";
		for (auto bia: BIA1) cout << bia << " ";
		
		cout << "\n*";
		for (auto bia: BIA2) cout << bia << " ";

	//Acessing
		BIA1[1] = 25;		//ok
		//cout << BIA1[10];	//undefined behavior; prints something!
		//BIA1[10] = 0;		//undefined behavior!

	cout << "\n\n";
	//-------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------
	cout << "STRING .........." << endl;
	//-------------------------------------------------------------------------------------
	//- Allocated into HEAP
	//-------------------------------------------------------------------------------------
	string S1 {'M','a','r','i'};
	string S2 {"OLHA"};
	string S3 = S2;

	//Iterating
		//OU ... - menos recomendado
		cout << "\n#";
		for (size_t i=0; i<S1.size(); i++) cout << S1[i];
		cout << "\n@";
		for (size_t i=0; i<S2.size(); i++) cout << S2[i];

		//... OU
		cout << "\n*";
		for (auto s: S1) cout << s;
		cout << "\n$ ";
		for (auto s: S2) cout << s;

	//Accessing
		cout << "S3: " << S3 << endl;

		S2[2] = 'I'; cout << "S2: " << S2 << endl;

		cout << "S1 + S2: " << S1 + S2 << endl;

		cout << "S1 > S2: " << (S1 > S2) << endl;

		S1 += S3; cout << "S1: " << S1 << endl;

		//cout << S1[10];	//undefined behavior; prints something!
		//S1[10] = 'A';		//undefined behavior

	//Operations
		size_t posFind = S1.find('r');
		if (posFind != string::npos)
			cout << "uooou!" << endl;

		S1.append(S2); cout << "S1: " << S1 << endl;
		S1.append(S2,2,3); cout << "S1: " << S1 << endl;
		S1.insert(4,"!"); cout << "S1: " << S1 << endl;
		S1.erase(4,1); cout << "S1: " << S1 << endl;
		S1.erase(8,7); cout << "S1: " << S1 << endl;
		S1.append(to_string(123)); cout << "S1: " << S1 << endl;
		cout << "stoi: " << stoi("1234.5") << endl;
		cout << "stod: " << stod("1234.5") << endl;

	cout << "\n\n";
	//-------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------
	cout << "C-STYLE STRING .........." << endl;
	//-------------------------------------------------------------------------------------
	//- Array of char plus NULL ('\0'); while not found, the search in memory by NULL continues!
	//- Do not have SIZE member function
	//- In general, can be very dangerous (catastrophic) if not well managed! Used by some hacker attacks!
	//-------------------------------------------------------------------------------------
	char CS1[] = {'M','a','r','i','\0'};
	char CS2[] = "OLHA"; //NULL added by compiler
	int CSSize = sizeof(CS1)/sizeof(CS1[0]);

	//Iterating
		//OU ...
		cout << "\n#";
		for (int i=0; i<CSSize-1; i++) cout << CS1[i]; //Remember of NULL: always i<CSSize-1
		cout << "\n@";
		for (int i=0; i<CSSize-1; i++) cout << CS2[i]; //Same size, ok reuse CSSize!

		//... OU
		cout << "\n*";
		for (auto cs: CS1) cout << cs; //Considers last NULL as part of it!
		cout << "\n&";
		for (auto cs: CS2)  cout << cs; 

	//Accessing
		CS2[2] = 'I'; cout << CS2 << endl;

		cout << "CS1 > CS2: " << (CS1 > CS2) << endl;

		//cout << S1[10];	//undefined behavior; prints something!
		//S1[10] = 'A';		//undefined behavior

	//Operations
		const char *CS3 = S1.c_str();
		cout << "CS3: " << CS3 << endl;

		//#include <cctype>
		char c[] = "1aB !"; cout << "<" << c << ">" << endl;
		cout << "<" << c[0] << "> isdigit(c[0]) =0 is false; !0 is true: " << isdigit(c[0]) << endl;
		cout << "<" << c[1] << "> islower(c[1]) =0 is false; !0 is true: " << islower(c[1]) << endl;
		cout << "<" << c[2] << "> isupper(c[2]) =0 is false; !0 is true: " << isupper(c[2]) << endl;
		cout << "<" << c[3] << "> isspace(c[3]) =0 is false; !0 is true: " << isspace(c[3]) << endl;
		cout << "<" << c[4] << "> ispunct(c[4]) =0 is false; !0 is true: " << ispunct(c[4]) << endl;
		cout << "<" << c[1] << "> toupper(c[1]): " << (char) toupper(c[1]) << endl;
		cout << "<" << c[2] << "> tolower(c[2]): " << (char) tolower(c[2]) << endl;

	cout << "\n\n";
	//-------------------------------------------------------------------------------------
	
	
	
	cout << "END OF PROGRAM";
	return 0;
}
