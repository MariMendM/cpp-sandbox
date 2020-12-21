//============================================================================
// Name        : GenericAlgorithms.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of generic algorithms:
//					find, find_if, sort, count, count_if, equal, lambda functions
//					min, max, minmax, min/max/minmax_element, upper/lower_bound, pair
//					iota, accumulate, partial_sum, adjacent_difference, inner_product
//					fill, replace, replace_if, for_each
//					copy, copy_n, copy_if, transform, replace_copy, replace_copy_if
//					reverse, reverse_copy, remove, remove_if, erase, unique,
//					set_intersection, next_permutation
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream> //print() only
#include <iomanip> //printIdx() only

using namespace std;

//Print functions -----------------------------------------

template <class T> string print(T var) {
	ostringstream out;
	for (auto it : var) { out << it << " "; }
	return out.str();
};

string printIdx(int index) {
	ostringstream out;
	out << std::setfill('0') << std::setw(3) << index << ". ";
	return out.str();
}

//Predicates ----------------------------------------------

bool function_sort_alphabetical(char c1, char c2) {
	return (std::tolower(c1) < std::tolower(c2) ? true : false);
}

bool function_if_has_exclamation(string s) {
	auto itS = find(s.cbegin(),s.cend(),'!');
	return (itS != s.cend());
}

class functor_if_longer_than {
	private:
		size_t n;
	public:
		functor_if_longer_than(int number) : n(number) {}
		bool operator() (const string &str) {
			return (str.size() > n);
		}
};

bool function_if_even(int n1) {
	return (n1 % 2 == 0);
}

class functor_if_even {
	public:
		bool operator() (int n1) {
			return (n1 % 2 == 0);
		}
};

class functor_even_numbers {
	private:
		int n;
	public:
		functor_even_numbers(int number) { n = (number%2==0) ? number : number-1; }
		int operator() (void) {
			n += 2;
			return n;
		}
};

//----------------------------------------------------------

int main() {

	int idx = 1;	//Only to organize couts!
	
	//----------------------------------------------------------------------------------------------------------
	//GENERIC ALGORITHMS
	//----------------------------------------------------------------------------------------------------------
	//PS.1:  This section uses lambda functions; details can be seen in "LambdaFunctions.cpp"
	//PS.2:  This section uses functors; details can be seen in "Functor.cpp"
	//----------------------------------------------------------------------------------------------------------
	
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "FIND, FIND_IF ................................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//FIND
		string strS1 = "Estamos voltando ao C++! Uhu!";
		cout << printIdx(idx++) << "String <" << strS1 << "> using standard FIND\n";
		auto itFind = find(strS1.cbegin(), strS1.cend(), '+'); //cbegin/cend: only to clarify the read-only idea
		if (itFind != strS1.cend())
			cout << "\tFound <" << *itFind << "> at pos: " << (itFind - strS1.cbegin()) << endl;

	//FIND_IF (function predicate)
		vector<string> vecS1 {"Estamos","voltando","ao","C++!", "Uhu!"};
		cout << printIdx(idx++) << "Vector { " << print(vecS1) << "} using FIND_IF with 'function_if_has_exclamation'\n";
		auto itFindIf = find_if(vecS1.cbegin(), vecS1.cend(), function_if_has_exclamation);
		if (itFindIf != vecS1.cend())
			cout << "\tFound <" << *itFindIf << "> at pos: " << (itFindIf - vecS1.cbegin()) << endl;

	//FIND_IF (functor predicate)
		int lgnThan = 7;
		cout << printIdx(idx++) << "Vector { " << print(vecS1) << "} using FIND_IF with 'functor_if_longer_than(" << lgnThan << ")'\n";
		itFindIf = find_if(vecS1.cbegin(), vecS1.cend(), functor_if_longer_than(lgnThan));
		if (itFindIf != vecS1.cend())
			cout << "\tFound <" << *itFindIf << "> at pos: " << (itFindIf - vecS1.begin()) << endl;

	//FIND_IF (lambda predicate)
		cout << printIdx(idx++) << "Vector { " << print(vecS1) << "} using FIND_IF with lambda 's.size()>lgnThan' in place and lgnThan(" << lgnThan << ")'\n";
		//const size_t n{7}; //variable to be "captured" (the term used) inside lambda function
		//itFindIf = find_if(vecS1.cbegin(), vecS1.cend(), [n](string s){return s.size() > n;});
		itFindIf = find_if(vecS1.cbegin(), vecS1.cend(), [lgnThan](string s){return s.size() > (size_t)lgnThan;});
		if (itFindIf != vecS1.cend())
			cout << "\tFound <" << *itFindIf << "> at pos: " << (itFindIf - vecS1.begin()) << endl;

	//FIND_IF (lambda predicate)
		//size_t num{8}; //captured  variable
		lgnThan = 5;
		cout << printIdx(idx++) << "Vector { " << print(vecS1) << "} using FIND_IF with 'lambda_is_longer_than' declared and lgnThan(" << lgnThan << ")'\n";
		//auto lambda_is_lower_than = [&num](string s) {return s.size() < num;};
		auto lambda_is_longer_than = [lgnThan](string s) {return s.size() > (size_t)lgnThan;};
		itFindIf = find_if(vecS1.cbegin(), vecS1.cend(), lambda_is_longer_than);
		if (itFindIf != vecS1.cend())
			cout << "\tFound <" << *itFindIf << "> at pos: " << (itFindIf - vecS1.begin()) << endl;

	cout << endl;
	
	//----------------------------------------------------------------------------------------------------------
	cout << "SORT .........................................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//SORT
		string strS2 = "O que AconTecerá com Esta string?";
		cout << printIdx(idx++) << "String <" << strS2 << "> using standard SORT;\n";
		sort(strS2.begin(), strS2.end());
		cout << "\tResult in same string <" << strS2 << ">\n";

	//SORT (function predicate)
		string strS3 = "O que AconTecerá com Esta string?";
		cout << printIdx(idx++) << "String <" << strS2 << "> using SORT with 'function_sort_alphabetical';\n";
		sort(strS3.begin(), strS3.end(), function_sort_alphabetical);
		cout << "\tResult in same string <" << strS3 << ">\n";
		
	//SORT
		vector<int> vecI0 {2, 1, 3, 6, 5, 1, 9, 7, 8, 2, 3};
		cout << printIdx(idx++) << "Vector { " << print(vecI0) << "} using standard SORT;\n";
		sort(vecI0.begin(), vecI0.end());
		cout << "\tResult in same vector { " << print(vecI0) << "}\n";

	//SORT (standard functional object predicate)
		cout << printIdx(idx++) << "Vector { " << print(vecI0) << "} using SORT with greater<int>();\n";
		sort(vecI0.begin(), vecI0.end(), greater<int>());
		cout << "\tResult in same vector { " << print(vecI0) << "}\n";

	cout << endl;
	
	//----------------------------------------------------------------------------------------------------------
	cout << "COUNT, COUNT_IF ..............................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//COUNT
		vector<int> vecI1 {1, 2, 3, 4, 5, 2, 1, 7, 8, 2, 3};
		auto counter = count(vecI1.begin(), vecI1.end(), 2);
		cout << printIdx(idx++) << "Vector { " << print(vecI1) << "} using standard COUNT;\n\tFound (2) in vector " << counter << " times\n";

	//COUNT_IF (function predicate)
		counter = count_if(vecI1.begin(), vecI1.end(), function_if_even);
		cout << printIdx(idx++) << "Vector { " << print(vecI1) << "} using COUNT_IF with 'function_if_even';\n\tFound " << counter << " even numbers\n";

	//COUNT_IF (functor predicate)
		counter = count_if(vecI1.begin(), vecI1.end(), functor_if_even());
		cout << printIdx(idx++) << "Vector { " << print(vecI1) << "} using COUNT_IF with 'functor_if_even';\n\tFound " << counter << " even numbers\n";

	//COUNT_IF (lambda predicate)
		counter = count_if(vecI1.begin(), vecI1.end(), [](int n){return (n % 2 == 0);});
		cout << printIdx(idx++) << "Vector { " << print(vecI1) << "} using COUNT_IF with lambda 'n % 2 == 0' in place;\n\tFound " << counter << " even numbers\n";

	cout << endl;


	//----------------------------------------------------------------------------------------------------------
	cout << "EQUAL ........................................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//EQUAL
		vector<int> vecI2 {1, 2, 3, 4, 5, 1, 7, 8, 2};
		cout << printIdx(idx++) << "Vectors { " << print(vecI1) << "} and { " << print(vecI2) << "} using standard EQUAL; Are equal? ";
		cout << std::boolalpha << equal(vecI1.cbegin(),vecI1.cend(), vecI2.cbegin(),vecI2.cend()) << endl;

	//EQUAL (lambda predicate)
		string strS5 = "Testando";
		string strS6 = "testAndO";
		string strS7 = "testAdO";
		auto lambda_if_equal_case = [](char c1, char c2){ return toupper(c1)==toupper(c2); };
		cout << printIdx(idx++) << "Strings <" << strS5 << "> and <" << strS6 << "> using EQUAL with 'lambda_if_equal_case'; Are equal? ";
		cout << std::boolalpha << equal(strS5.cbegin(),strS5.cend(), strS6.cbegin(),strS6.cend(), lambda_if_equal_case) << endl;
		cout << printIdx(idx++) << "Strings <" << strS5 << "> and <" << strS7 << "> using EQUAL with 'lambda_if_equal_case'; Are equal? ";
		cout << std::boolalpha << equal(strS5.cbegin(),strS5.cend(), strS7.cbegin(),strS7.cend(), lambda_if_equal_case) << endl;

	cout << endl;


	//----------------------------------------------------------------------------------------------------------
	cout << "PAIR .........................................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	//#include <utility>
	
		pair<string,string> pairStrStr("Mari","MM");
		cout << printIdx(idx++) << "pairStrStr.first = <" << pairStrStr.first << "> and pairStrStr.second = <" << pairStrStr.second << ">" << endl;
		pair<int,string> pairIntStr(1,"Mari MM");
		cout << printIdx(idx++) << "pairIntStr.first = <" << pairIntStr.first << "> and pairIntStr.second = <" << pairIntStr.second << ">" << endl;
		auto pairFltStr = make_pair(1.5,"Float");
		cout << printIdx(idx++) << "pairFltStr.first = <" << pairFltStr.first << "> and pairFltStr.second = <" << pairFltStr.second << ">" << endl;

	cout << endl;


	//----------------------------------------------------------------------------------------------------------
	cout << "MIN, MAX, MINMAX .............................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------

	//MIN (lambda predicate)
		auto lambda_minor_size = [](string s1, string s2) {return s1.size() < s2.size();};
		string strS8 = "Mariane";
		string strS9 = "Medeiros";
		cout << printIdx(idx++) << "Strings <" << strS8 << "> and <" << strS9 << "> using MIN with 'lambda_minor_size';\n\tMin = " << min(strS8,strS9, lambda_minor_size) << endl;
	
	//MIN (lambda predicate): collection not declared
		cout << printIdx(idx++) << "Collection {\"agora\", \"hum\", \"vamos\", \"testar\"} using MIN with 'lambda_minor_size';\n\tMin = " << min({"agora", "hum", "vamos", "testar"}, lambda_minor_size) << endl;
	
	//MAX
		cout << printIdx(idx++) << "Strings <" << strS8 << "> and <" << strS9 << "> using standard MAX;\n\tMax = " << max(strS8,strS9) << endl;
	
	//MAX: collection not declared
		cout << printIdx(idx++) << "Collection {\"agora\", \"hum\", \"vamos\", \"testar\"} using standard MAX;\n\tMax = " << max({"agora", "hum", "vamos", "testar"}) << endl;

	//MIN (lambda predicate): collection not declared
		auto lambda_higher_size = [](string s1, string s2) {return s1.size() > s2.size();};
		cout << printIdx(idx++) << "Collection {\"agora\", \"hum\", \"vamos\", \"testar\"} using MAX with 'lambda_higher_size';\n\tMax = " << max({"agora", "hum", "vamos", "testar"}, lambda_higher_size) << endl;

	//MINMAX (lambda predicate)
		auto pairVar = minmax({"agora", "hum", "vamos", "testar"}, lambda_minor_size);
		cout << printIdx(idx++) << "Collection {\"agora\", \"hum\", \"vamos\", \"testar\"} using MINMAX with 'lambda_minor_size';\n\tMin (pair.first) = " << pairVar.first << "; Max (pair.second) = " << pairVar.second << endl;

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "MIN/MAX/MINMAX_ELEMENT .......................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------

	//MIN_ELEMENT (lambda predicate)
		vector<string> vecS10{"agora", "hum", "vamos", "testar"};
		cout << printIdx(idx++) << "Vector { " << print(vecS10) << "} using MIN_ELEMENT with 'lambda_minor_size';\n";
		auto itMinMax = min_element(vecS10.cbegin(), vecS10.cend(), lambda_minor_size);
		if (itMinMax != vecS10.cend())
			cout << "\tFound <" << *itMinMax << "> at pos: " << (itMinMax - vecS10.begin()) << endl;

	//MAX_ELEMENT
		cout << printIdx(idx++) << "Vector { " << print(vecS10) << "} using standard MAX_ELEMENT;\n";
		itMinMax = max_element(vecS10.cbegin(), vecS10.cend());
		if (itMinMax != vecS10.cend())
			cout << "\tFound <" << *itMinMax << "> at pos: " << (itMinMax - vecS10.begin()) << endl;
		
	//MINMAX_ELEMENT
		auto pairMinMax = minmax_element(vecS10.cbegin(), vecS10.cend());
		cout << printIdx(idx++) << "Vector { " << print(vecS10) << "} using standard MINMAX_ELEMENT;\n\tMin (pair.first) = " << *pairMinMax.first << "; Max (pair.second) = " << *pairMinMax.second << endl;
		
	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "UPPER_BOUND, LOWER_BOUND .....................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	//UPPER_BOUND: returns iterator to first element that is GREATER THAN parameter
	//LOWER_BOUND: returns iterator to first element that is NOT LESS THAN parameter (take care! see 1st example below!)
	
	//UPPER_BOUND
		vector<int> vecI40 {2, 4, 1, 9, 7, 6, 0, 8, 7, 3, 2};
		cout << printIdx(idx++) << "Vector { " << print(vecI40) << "} using standard UPPER_BOUND with parameter 5 (greater than 5);\n";
		auto itBounds = upper_bound(vecI40.begin(), vecI40.end(), 5);
		if (itBounds != vecI40.end())
			cout << "\tFound upper bound <" << *itBounds << "> at pos: " << (itBounds - vecI40.begin()) << endl;

	//LOWER_BOUND
		cout << printIdx(idx++) << "Vector { " << print(vecI40) << "} using standard LOWER_BOUND with parameter 1 (not less than 1);\n";
		itBounds = lower_bound(vecI40.begin(), vecI40.end(), 1);
		if (itBounds != vecI40.end())
			cout << "\tFound lower bound <" << *itBounds << "> at pos: " << (itBounds - vecI40.begin()) << endl;

	//LOWER_BOUND
		sort(vecI40.begin(),vecI40.end());
		cout << printIdx(idx++) << "Vector { " << print(vecI40) << "} using standard LOWER_BOUND with parameter 4 (not less than 4);\n";
		itBounds = lower_bound(vecI40.begin(), vecI40.end(), 4);
		if (itBounds != vecI40.end())
			cout << "\tFound lower bound <" << *itBounds << "> at pos: " << (itBounds - vecI40.begin()) << endl;

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "IOTA, FILL, GENERATE_N .......................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	//#include <numeric> for IOTA
	
	//IOTA
		vector<int> vecI3(10);
		iota(vecI3.begin(), vecI3.end(), 3);
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "}, size 10, fullfiled by IOTA with parameter 3;\n";

	//FILL
		vector<int> vecI4(5);
		fill(vecI4.begin(), vecI4.end(), 3);
		cout << printIdx(idx++) << "Vector { " << print(vecI4) << "}, size 5, fulfilled by FILL with parameter 3;\n";
		
	//GENERATE_N (functor predicate) - useful for random number generation (example in "RandomNumbers.cpp")
		vector<int> vecI41(5);
		generate_n(vecI41.begin(), 5, functor_even_numbers(3));
		cout << printIdx(idx++) << "Vector { " << print(vecI41) << "}, size 5, fulfilled by GENERATE_N with 'functor_even_numbers(3)';\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "ACCUMULATE, PARTIAL_SUM, ADJACENT_DIFFERENCE, INNER_PRODUCT ..................................\n\n";
	//----------------------------------------------------------------------------------------------------------

	//ACCUMULATE
		auto x = accumulate(vecI3.begin(), vecI3.end(), 0);
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using standard ACCUMULATE with parameter 0 (vector sum + 0) = " << x << endl;
		x = accumulate(vecI3.begin(), vecI3.end(), 10);
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using standard ACCUMULATE with parameter 10 (vector sum + 10) = " << x << endl;
	
	//ACCUMULATE (lambda function)
		auto lambda_even_numbers = [](int sum, int n){ return (n % 2 == 0 ? sum+n : sum); };
		x = accumulate(vecI3.begin(),vecI3.end(), 10, lambda_even_numbers);
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using ACCUMULATE with 'lambda_even_numbers' and parameter 10 (vector sum of even + 10) = " << x << endl;

	//PARTIAL_SUM
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using standard PARTIAL_SUM from begin;\n";
		partial_sum(vecI3.begin(), vecI3.end(), vecI3.begin()); //can use other operators than sum; see doc;
		cout << "\tResult in same vector { " << print(vecI3) << "}\n";

	//ADJACENT_DIFFERENCE (inverse of partial_sum)
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using standard ADJACENT_DIFFERENCE from begin (inverse of partial_sum);\n";
		adjacent_difference(vecI3.begin(),vecI3.end(),vecI3.begin()); //can use other operators; see doc;
		cout << "\tResult in same vector { " << print(vecI3) << "}\n";

	//INNER_PRODUCT (scalar multiplication of containers)
		vector<int> vecI5(10); iota(vecI5.begin(), vecI5.end(), 0);
		int innProd = inner_product(vecI3.begin(), vecI3.end(), vecI5.begin(), 0); //can use other operators; see doc;
		cout << printIdx(idx++) << "Vector { " << print(vecI5) << "} using standard INNER_PRODUCT with parameter 0 = " << innProd << endl;

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "FOR_EACH .....................................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------

	//FOR_EACH (lambda predicate)
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using FOR_EACH with lambda 'return (n%3==0)?n=1:n=0' in place;\n";
		for_each(vecI3.begin(), vecI3.end(), [](int &n){ return (n%3 == 0) ? n=1 : n=0; });
		cout << "\tResult in same vector ( " << print(vecI3) << "}\n";

	//FOR_EACH (lambda predicate)
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using FOR_EACH with lambda 'cout<<((n==0)?\"false\":\"true\"' in place;\n\tResult {";
		for_each(vecI3.begin(), vecI3.end(), [](int n){ cout << ((n==0)?"false":"true") << " "; });
		cout << "}\n";
		
	//FOR_EACH (lambda predicate)
		string strS10 = "TeStAnDo!";
		cout << printIdx(idx++) << "String <" << strS10 << "> using FOR_EACH with lambda 'return c=toupper(c)' in place;\n";
		for_each(strS10.begin(), strS10.end(), [](char &c){ return c=toupper(c); });
		cout << "\tResult in same string <" << strS10 << ">\n";

	//FOR_EACH (lambda predicate)
		cout << printIdx(idx++) << "Vector { " << print(vecI3) << "} using FOR_EACH with lambda 'cout<<n<<" ";' in place;\n\tResult {";
		for_each(vecI3.begin(), vecI3.end(), [](int n){ cout << n << " "; });
		cout << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "REPLACE, REPLACE_IF ..........................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------

	//REPLACE
		vector<int> vecI6(10); iota(vecI6.begin(), vecI6.end(), 1);
		cout << printIdx(idx++) << "Vector { " << print(vecI6) << "} using standard REPLACE (5 by 6);\n";
		replace(vecI6.begin(), vecI6.end(), 5, 6);
		cout << "\tResult in same vector { " << print(vecI6) << "}\n";

	//REPLACE_IF (function predicate)
		cout << printIdx(idx++) << "Vector { " << print(vecI6) << "} using REPLACE_IF with 'function_if_even' (even by 0);\n";
		replace_if(vecI6.begin(), vecI6.end(), function_if_even, 0);
		cout << "\tResult in same vector { " << print(vecI6) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "COPY, COPY_N, COPY_IF ........................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//COPY
		vector<int> vecI10 = {1, 2, 3, 4, 5};
		vector<int> vecI11(vecI10.size());
		copy(vecI10.begin(), vecI10.end(), vecI11.begin());
		cout << printIdx(idx++) << "Vector { " << print(vecI10) << "} using standard COPY;\n\tResult in new vector { " << print(vecI11) << "};\n";

	//COPY
		vector<int> vecI12;
		copy(vecI10.begin(), vecI10.end(), back_inserter(vecI12));
		cout << printIdx(idx++) << "Vector { " << print(vecI10) << "} using standard COPY with back_inserter;\n\tResult in new vector { " << print(vecI12) << "}\n";

	//COPY_N
		vector<int> vecI13;
		copy_n(vecI10.begin(), 3, back_inserter(vecI13));
		cout << printIdx(idx++) << "Vector { " << print(vecI10) << "} using standard COPY with parameter 3 and back_inserter;\n\tResult in new vector { " << print(vecI13) << "}\n";

	//COPY_IF (lambda predicate)
		vector<int> vecI14;
		auto lambda_if_odd = [](int n){ return (n % 2) == 0 ? false : true; };
		copy_if(vecI10.begin(), vecI10.end(), back_inserter(vecI14), lambda_if_odd);
		cout << printIdx(idx++) << "Vector { " << print(vecI10) << "} using COPY_IF with 'lambda_if_odd' and back_inserter;\n\tResult in new vector { " << print(vecI14) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "REPLACE_COPY, REPLACE_COPY_IF ................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//REPLACE_COPY
		vector<int> vecI15{3, 1, 4, 2, 3};
		vector<int> vecI16;
		replace_copy(vecI15.begin(), vecI15.end(), back_inserter(vecI16), 3, 0);
		cout << printIdx(idx++) << "Vector { " << print(vecI15) << "} using standard REPLACE_COPY (3 by 0) with back_inserter;\n\tResult in new vector { " << print(vecI16) << "}\n";

	//REPLACE_COPY_IF (lambda predicate)
		vector<int> vecI17;
		replace_copy_if(vecI15.begin(), vecI15.end(), back_inserter(vecI17), lambda_if_odd, 0);
		cout << printIdx(idx++) << "Vector { " << print(vecI15) << "} using REPLACE_COPY_IF with 'lambda_if_odd' (odd by 0) and back_inserter;\n\tResult in new vector { " << print(vecI17) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "TRANSFORM ....................................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
	//TRANSFORM (lambda predicate)
		string strS11{"Uma string para ser testada!"};
		string strS12;
		transform(strS11.begin(), strS11.end(), back_inserter(strS12), [](char c){ return toupper(c); });
		cout << printIdx(idx++) << "String <" << strS11 << "> using TRANSFORM with lambda 'return toupper(c)' in place and back_inserter;\n\tResult in new string <" << strS12 << ">\n";

	//TRANSFORM (lambda predicate)
		vector<int> vecI18{1, 2, 3, 4, 5};
		vector<int> vecI19;
		auto lambda_sum_up = [](int n1, int n2){ return n1+n2; };
		transform(vecI15.begin(),vecI15.end(), vecI18.begin(), back_inserter(vecI19), lambda_sum_up);
		cout << printIdx(idx++) << "Vectors { " << print(vecI15) << "} + { "<< print(vecI18) << "} using TRANSFORM with 'lambda_sum_up' and back_inserter;\n\tResult in new vector { " << print(vecI19) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "REVERSE, REVERSE_COPY ........................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
		
	//REVERSE
		cout << printIdx(idx++) << "Vector { " << print(vecI15) << "} using standard REVERSE;\n";
		reverse(vecI15.begin(), vecI15.end());
		cout << "\tResult in same vector { " << print(vecI15) << "}\n";

	//REVERSE_COPY
		vector<int> vecI20;
		cout << printIdx(idx++) << "Vector { " << print(vecI15) << "} using standard REVERSE_COPY and back_inserter;\n";
		reverse_copy(vecI15.begin(), vecI15.end(), back_inserter(vecI20));
		cout << "\tResult in new vector { " << print(vecI20) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "REMOVE, REMOVE_IF (both + ERASE) .............................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	//REMOVE + ERASE
	/*As instruções REMOVE / REMOVE_IF movem os elementos sendo "removidos" para o fim do container, os invalida,
	  mas ainda os mantém na estrutura, tanto que seu indicador SIZE continua com o mesmo valor de antes da remoção;
	  acessar estes elementos pode trazer um comportamento inesperado; portanto, não devem ser usadas sozinhas, mas
	  em conjunto com ERASE; este remove de fato os elementos */

	//REMOVE + ERASE
		vector<int> vecI30{1, 2, 1, 3, 1, 4};
		cout << printIdx(idx++) << "Vector { " << print(vecI30) << "} using standard REMOVE and ERASE to remove 1's;\n";
		auto iterFirstRemoved = remove(vecI30.begin(),vecI30.end(),1); //remove 1's
		vecI30.erase(iterFirstRemoved, vecI30.end());
		cout << "\tResult in same vector { " << print(vecI30) << "}\n";

	//REMOVE_IF + ERASE (lambda predicate)
		vector<int> vecI31{1, 2, 1, 3, 1, 4};
		cout << printIdx(idx++) << "Vector { " << print(vecI31) << "} using REMOVE_IF with 'lambda_if_odd' and ERASE;\n";
		iterFirstRemoved = remove_if(vecI31.begin(), vecI31.end(), lambda_if_odd);
		vecI31.erase(iterFirstRemoved, vecI31.end());
		cout << "\tResult in same vector { " << print(vecI31) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "UNIQUE (+ ERASE) .............................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	//UNIQUE + ERASE
	//Unique has the same behavior that REMOVE when "deleting" elements; shall be used always with erase

	//UNIQUE - remove <adjacent> repetitions
		vector<int> vecI32{1, 1, 2, 2, 2, 1, 3, 3, 1, 4, 3};
		cout << printIdx(idx++) << "Vector { " << print(vecI32) << "} using standard UNIQUE and ERASE;\n";
		iterFirstRemoved = unique(vecI32.begin(), vecI32.end());
		vecI32.erase(iterFirstRemoved, vecI32.end());
		cout << "\tResult in same vector { " << print(vecI32) << "}\n";
	
	//UNIQUE - remove <adjacent> repetitions
		vector<int> vecI33{1, 1, 2, 2, 2, 1, 3, 3, 1, 4, 3};
		sort(vecI33.begin(), vecI33.end());
		cout << printIdx(idx++) << "Vector { " << print(vecI33) << "} using standard UNIQUE and ERASE;\n";
		iterFirstRemoved = unique(vecI33.begin(), vecI33.end());
		vecI33.erase(iterFirstRemoved, vecI33.end());
		cout << "\tResult in same vector { " << print(vecI33) << "}\n";
		
	//UNIQUE (lambda predicate) - remove <adjacent> repetitions conditionally (random condition used for testing, not necessarily to unique things!)
		vector<int> vecI34{1, 1, 2, 2, 2, 1, 3, 3, 1, 4, 3};
		cout << printIdx(idx++) << "Vector { " << print(vecI34) << "} using UNIQUE with lambda 'return n>m' in place, and ERASE;\n";
		iterFirstRemoved = unique(vecI34.begin(), vecI34.end(), [](int n, int m){ return n>m; });
		vecI34.erase(iterFirstRemoved, vecI34.end());
		cout << "\tResult in same vector { " << print(vecI34) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "SET_INTERSECTION .............................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------

		vector<int> vecI35 {1, 3, 5};
		vector<int> vecI36;
		sort(vecI32.begin(),vecI32.end());
		sort(vecI35.begin(),vecI35.end());
		set_intersection(vecI35.begin(), vecI35.end(), vecI32.begin(), vecI32.end(), back_inserter(vecI36));
		cout << printIdx(idx++) << "Vectors { " << print(vecI35) << "} and { " << print(vecI32) << "} using standard SET_INTERSECTION and back_inserter;\n\tResult in new vector { " << print(vecI36) << "}\n";

	cout << endl;
	
	
	//----------------------------------------------------------------------------------------------------------
	cout << "NEXT_PERMUTATION .............................................................................\n\n";
	//----------------------------------------------------------------------------------------------------------
	
		string strS20 = "ABC";
		cout << printIdx(idx++) << "String <" << strS20 << "> using standard NEXT_PERMUTATION in loop;\n\tResult";
		do
			cout << " <" << strS20 << ">";
		while (next_permutation(strS20.begin(), strS20.end()));
		cout << endl;



	cout << "END OF PROGRAM" << endl;
	return 0;
}
