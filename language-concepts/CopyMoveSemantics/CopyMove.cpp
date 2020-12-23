//============================================================================
// Name        : CopyMove.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge about copy and move constructors/operators:
//					copy elision, lvalues/rvalues, move semantics and rvalue references,
//					std::move, reference collapsing (universal reference), perfect
//					forwarding and std::forward, RAII and move semantics,
//					disabling copy (some of unique_ptr)
//============================================================================

//Several variables declared simply for demo of copy/move constructors, but not
//used indeed; disabling warning
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <iostream>
using namespace std;

//--------------------------------------------------
class X {
	public:
		X(){}
		X(const X &other) { cout << "\t CopyConstr X!\n"; }
};
X function1() {
	return X();
}
//--------------------------------------------------

int main() {

	//---------------------------------------------------------------------------------------------------
	//COPY IN C++
	//---------------------------------------------------------------------------------------------------
	/* Traditional C++ does a lot of copying. Sometimes it can be avoided, sometimes not. Follows some
	cases of copy.

	ARGUMENTS BY VALUE:
		- It causes a call to variable's copy constructor
		- It pushes the copy into stack

				void DoSth(string s) { cout << s; }
				string S1;
				DoSth(S1);	//pushes a copy of S1 into stack

		Argument by reference solves?
		- It shadows the variable, using address to access it;
		- It can be used with 'const' when shall not be modified

				void DoSth(const string &s) { cout << s; }
				string S1;
				DoSth(S1);	//it is shadowed, having its address passed to the function

	RETURNS BY VALUE:
		- It causes variable to be copied into function's return space
		- The copy is delivered into variable receiving return

				string DoSth() { string s{"oi"}; return s; } //s is copied into function's return space
				string S1 = do_sth();	//returned value is copied into S1

		Return by reference solves?:
		- Dangerous, once that variable is copied into function's return space and the released;
		- The address returned is no longer pointing to valid memo

	STORING STL ELEMENTS:
		- Each push into STL containers performs copy of content during the process.

	COPY CONSTUCTOR OF CLASSES:
		- It can bring some overhead due to memory management. */
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//COPY ELISION BY COMPILER
	//---------------------------------------------------------------------------------------------------
	/* Compilers have several functions, being one of them the optimization of code. Due the "as-if"
	rule (the program has to run exactly as it would if not optimized), it cannot remove code even
	if it has side effects of no effect at all:

			void main() {
				int var=0; var++;	//declared, incremented, but never used; it doesn't matter, keep it!
			}

	The only exception to this rule is to assure copy elision, where compiler is allowed to skip
	copy constructors in some cases (even if it has side effects; it can be turned off with compiler
	option -fno-elide-constructors): 

			//class and function are actually outside main; repeated here commented for visualization
			//during explanation!
			class X {
				public:
					X(){}
					X(const X &other) {cout << "CopyConstr X!";}
			};

			X function1()
			{ return X(); }		//here, there is a copy of instance to function's return space
	*/

			//With elision:		g++ -o CopyMove.out CopyMove.cpp
			//Without elision:	g++ -fno-elide-constructors -o CopyMove.out CopyMove.cpp
			std::cout << "\n Outputs from copy elision portion of file...\n";
			X varX = function1();	//Here, there are a copy of returned instance to varX

	/* Running above copy should then print "CopyConstr X!" twice, right? Wrong if copy elision is turned
	on during compile. First, the copy of temporary instance into function's return space was elided
	(return value optimization), creating the instance directly into return space and avoiding one copy
	(and also one destruction of the temporary instance). Then, the copy to initialization of varX was
	elided, creating instance directly into memory object of varX, avoiding creation of a temp instance,
	the initialization of varX and then the destruction of temp.
	
	The same elision occurs when local variables of functions are returned by value (name returned
	value optimization). */
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//LVALUES AND RVALUES
	//---------------------------------------------------------------------------------------------------
	/* In C, an expression is a LeftVALUE if it can appear on the left side of equal sign, a RightVALUE
	otherwise:
			x = 2;		//x = LVALUE; 2 = RVALUE
	
	In traditional C++, an expression is a LeftVALUE if we can take its address in memo using & operator
	(some people are naming it LocatorVALUE instead), being a RightVALUE otherwise:
			x = 2;					//x = LVALUE; 2 = RVALUE
			X varX = function1();	//the returned value is stored in a reserved area and thus, cannot be
									//accessed by address, being RVALUE; the variable varX is a LVALUE

	LVALUES represent 'persistent' instances, occupying memo in either the heap or the stack. They
	remain valid until go out of scope or be deleted.
	RVALUES can be literal values or temporary instances. In either case, we cannot access the memory
	where they are stored once we cannot find the address to do it.

	LVALUES references can bind to RVALUES only if const:
			int &x = 3;			//ERROR: lvalue reference 'x' cannot be bind to rvalue '3'
			const int &x = 3;	//OK; the compiler will create a temp var with 3 to be referenced into x
	
	Modern C++ 11 introduced "value categories":
		- PRVALUES, or Pure RVALUES, like 2 or 'c' that have no name and cannot be referenced again;
		- XVALUES, for temporary RVALUES instances (some cases described in COPY / COPY ELISION);
		- LVALUES, as already described above;
	LVALUES and XVALUES are collectively know as GLVALUES, or generalized values, the ones that can have
	dynamic types different from its static types. PRVALUES cannot. */
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//MOVE SEMANTICS and RVALUE REFERENCES
	//---------------------------------------------------------------------------------------------------
	/* Good material: http://thbecker.net/articles/rvalue_references/section_01.html
	
	When using copy constructors and copy assignment operators, the steps performed are:
			ClassX x1 = x2;						//Copy constructor
			ClassX x1(); ClassX x2(); x1 = x2;	//Copy assignment operator
	
		1) the x2's resources are copied into a temporary instance;
		2) the resources held by x1 are destroyed;
		3) the temporary instance's resources are copied into x1;
		4) the resources held by temporary instance are destroyed.
		
	Instead all of this copying, a swap can be much more efficient once it only exchanges the memory
	buffer variables:
			string S1{"oi"}, S2{"ola"}; swap(S1,S2);	//No copy performed!
	
			string temp(S1); S1 = S2; S2 = temp;		//Two copies!

	Semantically, they are different. Swap(a,b) assigns value of 'b' to 'a', as expected, but it also
	changes value of 'b'. If 'b' is expendable, OK; we can use it to copy once it is faster (considering
	that 'b' will remain in a state where it can be safely destroyed).
	
	Modern C++ adopted this idea and for that implemented special member functions 'move' and 'move assign'
	constructors, to improve performance replacing copies that are performed using temp variables; this is
	when RVALUE References come to existence: you have a LVALUE reference that allows bind to RVALUES
	references, instead of hard copies through temp variables.
	
	To overload functions which takes LVALUES references, it is necessary to add an extra &:
		LVALUE references - & (copy):
			classX (const classX & other)					//copy constructor (from 'other' to 'this')
			classX & operator = (const classX & other)		//copy assign oper (from 'other' to 'this')
		RVALUE references - && (move):
			classX (classX && other) noexcept				//move constructor (from 'other' to 'this')
			classX & operator = (classX && other) noexcept	//move assign oper (from 'other' to 'this')
	
	Notice the use of noexcept. If and exception is thrown, we can have an inconsistent state, where parts
	of instances were modified while others don't. The noexcept instruction is used to prevent that.
	
	These overloaded RVALUE referenced methods enables exchange of content between 'other' and 'this'; but
	in some cases, it is not quite good enough. Next section shows some functions to be used along with
	them to provide full 'move' capabilities.
	
	Another important point is that an RVALUE Reference can be bind not only to RVALUE, but also to LVALUE:
			void foo1(ClassX && x)
			{ ClassX someVar = x; }					// it calls ClassX (ClassX const & other)
			
			ClassX && foo2(); ClassX x = foo2();	// it calls ClassX (ClassX && other)

	In general, the rule of the language is: if it has a name, is then a LVALUE. It is a question of safety,
	once that the content of named variable would me moved, but it would still be in scope with some content
	that is expendable.
	
	This rule of names shall be remembered in class inheritance, when std::move shall be used along (move
	details in next section):
			Base(Base const & other);		// non-move semantics
			Base(Base && other);			// move semantics

			Derived(Derived const & other) : Base(other)		// it is named, LVALUE constructor of Base
			Derived(Derived && other) : Base(std::move(other))	// move it is not named, RVALUE constructor

	Summing some things up:
			func (classX && argX);
	- argX is an LVALUE bound to an RVALUE REFERENCE (XVALUE or PRVALUE);
	- argX is modifiable in the function;
	- argX is movable in the function (see next section) */
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//STD::MOVE FUNCTION
	//---------------------------------------------------------------------------------------------------
	/* Back to the rule "if it has a name, it is LVALUE" of previous section:
			void print(string && x)			//RVALUE reference (variable being passed as arg is disposable)
			{ cout << x; }					//Yet, x is an LVALUE and can be used as such
	
			string &&varStr (string{"temp"});	//"temp" is in fact RVALUE...
			print(varStr);						//ERROR! ... varStr is LVALUE even so
		
	The way to really treat the LVALUE as expendable and pass it "by move", as a simple not named RVALUE
	reference is using 'std::move':
			void print(string && x)			//RVALUE reference
			{ cout << x; }
	
			string &&varStr (string{"temp"});
			print(std::move(varStr));		//OK! It calls the move constructor of string instead of copy!
	
	The 'std::move' is not named and for that, it calls the move constructor of string in this case, managing
	to transfer the context of 'varStr' into function's argument 'x'. In fact, it does not move anything, it
	just casts LVALUE into an RVALUE Reference. Yet, it is still not safe to access 'varStr' after pass it as
	RVALUE Reference once it may be unusable; it is safe tough to assign content to it, as well as to destroy
	it.
	
	The 'std::move' should always be avoided when possible. But there are cases where it is mandatory,
	mainly with objects than cannot be copied, being only "movable", such as fstream, unique_ptr and objects
	used in multi-threading:
			void function1(fstream objF) {...}
	
			fstream objFile ("arquivo.txt");
			function1(std::move(objFile));	//Always! And remember: do not use anymore after function1 finishes!
	
	Use it always as 'std::move' to assure casting only and avoid any confusion with other move functions
	that takes a single argument.
	
	So, the move constructor already mentioned, using std::move, is:
			ClassX (ClassX&& other) noexcept : classVar1(std::move(other.classVar1));
	and the move assignment operator is:
			ClassX & operator = (const ClassX && other) noexcept {
				if (this != other) ...
				return *this;
			}
			
	Practical example: */
	
		class Teste {
			private:
				int i{0};
				X objX;
			public:
				Teste() {}
				
				//copy constructor
				Teste (const Teste & other) : i(other.i) {
					i = other.i;
					objX = other.objX;
					cout << "\t CopyConstr Teste!\n\n";
				}
				
				//move constructor
				Teste (Teste && other) noexcept : objX(std::move(other.objX)) {
					swap(i, other.i); //swaps built-in types; moves for class defined
					cout << "\t MoveConstr Teste!\n\n";
				}

				//copy assignment operator
				Teste & operator = (const Teste & other) {
					if (this != &other) {
						i = other.i;
						objX = other.objX;
						cout << "\t CopyAssig Teste!\n\n";
					}
					return *this;
				}
				//move assignment operator
				Teste & operator = (Teste && other) {
					if (this != &other) {
						swap(i, other.i);
						objX = std::move(other.objX);
						cout << "\t MoveAssig Teste!\n\n";
					}
					return *this;
				}
		};
		std::cout << "\n Outputs from std::move portion of file...\n";
		Teste varT1;
		Teste varT2 = varT1;			//copy constructor
		Teste varT3 = Teste();			//move constructor by using temporary instance
		Teste varT4(std::move(varT1));	//move constructor by casting varT1 to rvalue reference
		Teste varT5, varT6, varT7;
		varT6 = varT5;					//copy assignment (normal) operator
		varT7 = Teste();				//move assignment operator
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//REFERENCE COLLAPSING (UNIVERSAL REFERENCE)
	//---------------------------------------------------------------------------------------------------
	/* Before to proceed to Perfect Forwarding, it is necessary to understand Reference Collapsing.
	Programmers cannot create nested references:
			int & &x = y;	//Compiler ERROR
	
	The compiler can do it internally using type alias or template parameter:
			using ReferenceInt = int&;	//or typedef int& ReferenceInt;
			int i{99};
			ReferenceInt ri{i};		//'ri' is a reference to int
			ReferenceInt & rri{ri};	//'rr' is a reference to (reference to int), but has type reference to int
	
	The type of result is defined by "Reference Collapsing":
	
			Inner var (one being defined)	|	Outer var (one being bind to defined one)	|	Result
						&					|						&						|	  &
						&					|						&&						|	  &
						&&					|						&						|	  &
						&&					|						&&						|	  &&
	//-------------------------------------------------------------------------------------------------*/


	//---------------------------------------------------------------------------------------------------
	//PERFECT FORWARDING (std::forward)
	//---------------------------------------------------------------------------------------------------
	/* One function can forward some/all of its arguments to other function:
			void function1(X x) {
				function2 (x);			//function1() forwards x to g()
			}
	
	Perfect forwarding happens when the properties of the object are preserved across forwarding: if x is
	movable in F1 and in F2, if x is modifiable in F1 and in F2, etc. But considering the possibilities,
	to have that, we would need to have pairs of functions according to necessity:	
			void functF(X & objX){functG(X);}			void functG(X & objX){...};			//modifiable
			void functF(const X & objX){functG(X);}		void functG(const X & objX){...};	//unmodifiable
			void functF(X && objX){functG(X);}			void functG(X && objX){...};		//movable
	
	Not a very scalable solution. Can we use templates?
			template<typename T> void func(T && objX) {...}
		
			- the parameter is a "forwarding" reference (T &&) - OK
			- it can be bound to any type category using reference collapsing (universal reference) - OK
			- objX may be modifiable, unmodifiable or movable in the function - OK
	
	But... when deducing the argument type for a forwarding reference using templates, the compiler considers
	the value category: if the argument is LVALUE, then the type is deduced as "LVALUE reference to ObjX";
	otherwise, the original type is used. To discover that, compiler applies reference collapsing. Then:
			template<typename T> void F(T && objX){ G(objX); }
			X x1;
			const X x2;
			F(x1);					//F(int &) calls G(int &); OK
			F(x2);					//F(const int &) calls G(const int &); OK
			F(std:: move(x1));		//F(int &&) calls G(int &); NOK! Why? inside F, objX is a LVALUE!
	
	So, to keep perfect forwarding, we should cast objX when forwarding. Casting with std::move:
			template<typename T> void F(T && objX){ G(std::move(objX)); }
			
	It is going to work for the last example, but not for the other two cases! The solution must cast only
	RVALUE References. For that, we use 'std::forward':
			template<typename T> void F(T && objX){ G(std::forward<T>(objX)); }
			X x1;
			const X x2;
			F(x1);					//F(int &) calls G(int &); OK
			F(x2);					//F(const int&) calls G(const int &); OK
			F(std:: move(x1));		//F(int &&) calls G(int &&); OK
	
	This a concept nor widely used in common programming; it is more used by programmers writing libraries.
	//-------------------------------------------------------------------------------------------------*/


	//---------------------------------------------------------------------------------------------------
	//RAII (Resource Acquisition is Initialization) AND MOVE SEMANTICS
	//---------------------------------------------------------------------------------------------------
	/* For RAII languages, is much more faster use move constructor and move assign operator than copy
	constructor and standard (copy) assignment operator. It is also necessary to take care of the pointers
	to assure correct destruction of variables when necessary:

		class BufferManager {
			private:
				int size;
				char *buffer;
			public:
				// constructor
					BufferManager (int size) : size(size) { buffer = new char[size]; }
				// destructor
					~BufferManager () { delete [] buffer; }

				// copy assign operator (file "Exceptions" discuss this in terms of basic/strong guarantees;
				// not the point here, the overhead in both is pretty much the same)
					BufferManager & operator = (const BufferManager & other) {
						// Lots of overhead when compared to move assign operator!
						if (this != & other) {
							delete [] buffer;			//runs same code as destructor
							size = other.size;			//runs the same code of copy constructor
							buffer = new char[size];
							for (int i=0; i<size; ++i)
								buffer[i] = other.buffer[i];
						}
						return *this;
					}
				// move assign operator
					BufferManager & operator = (BufferManager && other) noexcept {
						swap(*this, other);
						return *this;
					}

				// copy constructor
					BufferManager (const BufferManager & other) {
						// Lots of overhead when compared to move constructor!
						size = other.size;
						buffer = new char[size];
						for (int i=0; i<size; ++i)
							buffer[i] = other.buffer[i];
					}
				// move constructor
					BufferManager (BufferManager && other) noexcept {
						// Just swapping pointers!
						swap(*this, other);	//this is a brand new inst; pointer still unassigned
											// after swap, other will have this unassigned pointer
						other.buffer = nullptr;		//assuring that destructor will be able to destroy
													// it turning the unassigned into null
					}

				// Being a binary operator, it is better to be implemented outside class, as friend
					friend void swap (BufferManager &left, BufferManager &right) noexcept;
			};

			// Being a binary operator, it is better to be implemented outside class, as friend
			inline void swap (BufferManager &left, BufferManager &right) noexcept {
				using std::swap;	//It means "if there is a overloaded method swap for the type,
									// use it; use std otherwise"
				swap(left.size, right.size);
				swap(left.buffer, right.buffer);
		}
	*/
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//DISABLING COPY OPERATORS
	//---------------------------------------------------------------------------------------------------
	/* If we do not implement copy operators, compiler will. To avoid that, we can disable copy operators
	(case where compiler falls back to the move operators). If move operators are not implemented, then
	the compiler will raise error. Disabling:

		class BufferManagerV2 {
			private:
				int size;
				char *buffer;
			public:
				//constructor
					BufferManagerV2 (int size) : size(size) { buffer = new char[size]; }
				//destructor
					~BufferManagerV2 () { delete [] buffer; }

				//copy assign operator (DISABLED)
					BufferManagerV2 & operator = (const BufferManagerV2 &) = delete;
				//move assign operator
					BufferManagerV2 & operator = (BufferManagerV2 && other) noexcept {
						swap(*this, other);
						return *this;
					}

				//copy constructor (DISABLED)
					BufferManagerV2 (const BufferManagerV2 &) = delete;
				//move constructor
					BufferManagerV2 (BufferManagerV2 && other) noexcept {
						swap(*this, other);	//this is a brand new inst; pointer still unassigned
													//after swap, other will have this unassigned pointer
						other.buffer = nullptr;		//assuring that destructor will be able to destroy it
													//turning the unassigned into null
					}

				//Being a binary operator, it is better to be implemented outside class, as friend
					friend void swap (BufferManagerV2 &left, BufferManagerV2 &right) noexcept;
			};

			//Being a binary operator, it is better to be implemented outside class, as friend
			inline void swap (BufferManagerV2 &left, BufferManagerV2 &right) noexcept {
				using std::swap;	//It means "if there is a overloaded method swap for the type, use
									//it; use generic version otherwise"
				swap(left.size, right.size);
				swap(left.buffer, right.buffer);
			}
	
	When we do that, the move operator will be called when a copy is performed. This will transfer the
	pointer member from the original instance to the target one. There can only be one instance ever
	which has this pointer as member... sounds like UNIQUE_PTR! Yeah! They are implemented this way!
	
	Remembering that unique_ptr cannot be copied (it has copies disabled!), but it can be passed as
	argument to a function and be returned by functions as well:
	
			void funct1 (unique_ptr<int> PTR) {}	//calls move constructor when entering the function
	
			unique_ptr<int> funct2()
			{ return make_unique<int> (); }			//calls move constructor when leaving the function
	
			unique_ptr<int> PTR1 = make_unique<int>();
			funct1 (PTR1);
			//do not use PTR1 any longer!
			unique_ptr<int> PTR2;
			PTR2 = funct2();						//calls move assignment operator
			unique_ptr<int> PTR3(func2());			//calls move constructor
	*/
	//---------------------------------------------------------------------------------------------------


	cout << "END OF PROGRAM" << endl;
	return 0;
}
