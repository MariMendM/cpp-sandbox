//============================================================================
// Name        : Functor.cpp
// Author      : Mari
// Version     :
// Copyright   : Your copyright notice
// Description : Examples of functors
//============================================================================

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//-----------------------------------------------------------------------------------------
//FUNCTOR
//-----------------------------------------------------------------------------------------
// Classes (usually very simple ones) which overload function call operator "()"; for that,
// they are allowed to be called like a function.
// Used to pass functions as arguments to other functions.
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//Functor EXAMPLE 1
	class functor_evenp {
		public:
			bool operator () (int n) { //overloads c++ call function, represented by the operator "()"
				return (n % 2 == 0);
			}

			bool operator () (string s) { //overloads c++ call function, represented by the operator "()"
				return (s.size() % 2 == 0);
			}
	};
//Functor EXAMPLE 2
	class functor_divisible {
		private:
			int divisor{1};
		public:
			functor_divisible(int d) : divisor(d) {}
			
			bool operator () (int n) {
				return (n % divisor == 0);
			}
	};
//-----------------------------------------------------------------------------------------
//Auxiliar function EXAMPLE 1
	void do_it(const vector<int> &vec, functor_evenp is_even) {
		for (auto v: vec) cout << "\t" << v << " is even? " << (is_even(v) ? "yes" : "no") << endl;
	}
//Auxiliar function EXAMPLE 2
	void do_it(const vector<int> &vec, functor_divisible is_div) {
		for (auto v: vec) cout << "\t" << v << " is divisible? " << (is_div(v) ? "yes" : "no") << endl;
	}
//-----------------------------------------------------------------------------------------
//Print function
template <class T> string print(T var) {
	ostringstream out;
	for (auto it : var) out << it << " ";
	return out.str();
};
//-----------------------------------------------------------------------------------------

int main() {

	//EXAMPLE 1
		functor_evenp is_even;

		int n = 6;
		if (is_even(n))
			cout << "Example 1a: int <" << n << "> is even!\n";
		else
			cout << "Example 1a: int <" << n << "> is not even!\n";

		string s = "Mariane";
		if (is_even(s))
			cout << "Example 1b: string <" << s << "> has even size!\n";
		else
			cout << "Example 1b: string <" << s << "> does not have even size!\n";

		vector<int> intVec{1, 2, 3, 4, 5, 7, 9, 8};
		cout << "Example 1c: Passing vector { " << print(intVec) << "} and 'functor_evenp' as argument for function 'do_it':'\n";
		do_it(intVec, is_even);

	cout << endl;
	

	//EXAMPLE 2
		functor_divisible divByThree{3};
		vector<int> intVec2{1, 3, 4, 9, 33, 7};
		cout << "Example 2a: Passing vector { " << print(intVec2) << "} and 'functor_divisible' (by 3) as argument for function 'do_it':'\n";
		do_it(intVec2, divByThree);

		functor_divisible divByFive{5};
		vector<int> intVec3{1, 10, 32, 40, 50, 7};
		cout << "Example 2b: Passing vector { " << print(intVec3) << "} and 'functor_divisible' (by 5) as argument for function 'do_it':'\n";
		do_it(intVec3, divByFive);


	cout << "END OF PROGRAM" << endl;
	return 0;
}
