	
//============================================================================
// Name        : GenericAlgorithms.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of lambda functions
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> //for print() only

using namespace std;


//To print whichever container used
template <class T> string print (T var) {
	ostringstream out;
	for (auto it : var) { out << it << " "; }
	return out.str();
};

//Lambda function from a regular one
auto gerar_aumento_salario(double percent){
	return [percent](double salario) {return salario * percent;};
}

	
int main()
{
	//----------------------------------------------------------------------------------------------------------
	//LAMBDA FUNCTIONS
	//----------------------------------------------------------------------------------------------------------
	//PS.:  This section uses some of the generic algorithms that can be seen also in "GenericAlgorithms.cpp"
	//		Several examples of lambda functions are found there!
	//----------------------------------------------------------------------------------------------------------
	//To simplify and avoid work creating functions or functors that will be only used once or twice
	//along the code, predicates can be implemented by lambda functions (c++ 11 or higher) instead;
	//The compiler internally transforms them into functors with unique name, instancing it when needed;
	//
	//Structure:
	//		[] () { instr1; instr2; return ; }
	//where the brackets consider the variables of the code to be captured inside function:
	//		[]:  variable passed to the function
	//		[=]: all local variables passed by value
	//		[&]: all local variables passed by reference
	//		[a, &b]: a by value, b by reference
	//		[&, =a]: all by reference, except a by value... and so on
	//the parenthesis consider the input arguments (with type definition):
	//		(): no variable
	//		(char c, int n) : etc
	//the curly-braces define the body of the function, having a return for the result.
	
	//When used as predicates, the input parameters and the result shall reflect the behavior of generic
	//algorithm using the function. A counter algorithm may use a single argument, but a comparison one
	//probably takes two. The return is usually a bool of tested conditions.


	//They can be used exactly in place (single use):
			vector<int> vecV1 {10, 3, 4, 2, 5, 7, 9, 6, 1};
			auto counter = count_if(vecV1.begin(), vecV1.end(), [](int n){return (n % 2 == 0);});
			cout << "Ex.10. Vector { " << print (vecV1) << "} counted " << counter << " even numbers\n\n";
	
	//But they also can be declared for reuse:
			auto if_even = [](int n){ return (n % 2 == 0); };
			
			counter = count_if(vecV1.begin(), vecV1.end(), if_even);
			cout << "Ex.20. Vector { " << print (vecV1) << "} counted " << counter << " even numbers\n\n";

			cout << "Ex.30. Vector { " << print (vecV1) << "} replaced even numbers by 0 = { ";
			replace_if(vecV1.begin(),vecV1.end(), if_even, 0);
			cout << print(vecV1) << "}\n\n";


	//Capturing variables to USE inside lambda, by VALUE:
			vector<string> vecS5 {"Estamos","voltando","ao","C++!","Uhu!"};
			size_t num{8}; //captured  variable inside lambda

			//passing captured variable <num> by reference in order to provide changes of value in local scope...
				auto is_lower_than = [&num] (string s) {return s.size() < num;};
		
				cout << "Ex.40. Vector { " << print (vecS5) << "}; num <" << num << ">;\n";
				auto itFind = find_if(vecS5.cbegin(),vecS5.cend(), is_lower_than);
				if (itFind != vecS5.cend())
					cout << "Ex.40. Found <" << *itFind << "> at pos " << (itFind - vecS5.begin()) << " with 'is_lower_than' and 'num' <" << num << ">\n\n";

				num = 5;
				cout << "Ex.50. Vector { " << print (vecS5) << "}; num <" << num << ">;\n";
				itFind = find_if(vecS5.cbegin(),vecS5.cend(), is_lower_than);
				if (itFind != vecS5.cend())
					cout << "Ex.50. Found <" << *itFind << "> at pos " << (itFind - vecS5.begin()) << " with 'is_lower_than' and 'num' <" << num << ">\n\n";


	//Capturing variables to CHANGE inside lambda (MUTABLE lambda):
			int i{0}; //second variable to be captured (and in this case, changed)
			
			//passing captured variable <i> by value to lambda that is going to change it...
				//auto is_lower_than_v2 = [&num, i](string s) {cout << "i(" << ++i << ") "; return s.size() < num;};
				//ERROR compiling above line: increment of readonly variable!
		
			//solving it with MUTABLE...
				auto is_lower_than_v2 = [&num, i](string s) mutable { cout << "Ex.... ++i inside lambda <" << ++i << ">\n"; return s.size() < num; };
				
				cout << "Ex.60. Vector { " << print (vecS5) << "}; num <" << num << ">; i <" << i << "> in local scope before lambda execution;\n";
				itFind = find_if(vecS5.cbegin(),vecS5.cend(), is_lower_than_v2);
				if (itFind != vecS5.cend())
					cout << "Ex.60. Found <" << *itFind << "> at pos " << (itFind - vecS5.begin()) << " with 'is_lower_than' and 'i' <" << i << "> in local scope after lambda\n\n";

			//yet, nothing changed in local scope, after all, <i> was passed by value; so
			//passing captured variable <i> by reference to lambda that is going to change it, still using MUTABLE...
				auto is_lower_than_v3 = [&num, &i](string s) mutable { cout << "Ex.... ++i inside lambda <" << ++i << ">\n"; return s.size() < num; };
				
				cout << "Ex.70. Vector { " << print (vecS5) << "}; num <" << num << ">; i <" << i << "> in local scope before lambda execution;\n";
				itFind = find_if(vecS5.cbegin(),vecS5.cend(), is_lower_than_v3);
				if (itFind != vecS5.cend())
					cout << "Ex.70. Found <" << *itFind << "> at pos " << (itFind - vecS5.begin()) << " with 'is_lower_than' and 'i' <" << i << "> in local scope after lambda\n\n";


	//LAMBDA FUNCTIONS can also be returnde by regular functions. The function 'gerar_aumento_salario'
	//is an external function and its content is like this (real function before 'main'):
	//
	//	auto gerar_aumento_salario(double percent)
	//		return [percent](double salario) {return salario * percent;};
	
			auto calcula_aumento_05 = gerar_aumento_salario(1.05); // Awn, 5%!
			cout << "Ex.80. R$4000,00 with raise of 05% = " << calcula_aumento_05(4000.00) << endl;
			cout << "Ex.80. R$3000,00 with raise of 05% = " << calcula_aumento_05(3000.00) << endl;
			auto calcula_aumento_15 = gerar_aumento_salario(1.15); // Yeay, 15%!
			cout << "Ex.80. R$3000,00 with raise of 15% = " << calcula_aumento_15(3000.00) << endl << endl;


	//As said before, several examples of lambda functions with generic algorithms can be seen in file "GenericAlgorithms.cpp"
	//Bye!
	

	cout << "END OF PROGRAM" << endl;
	return 0;
}