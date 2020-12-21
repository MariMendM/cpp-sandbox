//============================================================================
// Name        : Pointers.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of Traditional Pointers / Smart Pointers / Pointers in built in arrays, classes, and pre/postfix operators
//============================================================================

#include <iostream>
#include <memory>

using namespace std;

//Function returning pointers (unique)
unique_ptr<int> create_ptr(){
	int x{10};		//Creates some variable
	//...			//Manipulates it
	unique_ptr<int> ptr = make_unique<int>(x);
	return ptr;		//Transfers pointer member of instance ptr to the instance of class that is going to receive the return
}


int main() {

	//Some things being using in pointers demos
	struct point2D { int x, y; };


	//----------------------------------------------------------------------------------------------
	//TRADITIONAL POINTERS (C standard)
	//----------------------------------------------------------------------------------------------
	/*- Store addresses to memory areas
	  - Highly used to pass variables by reference into functions
	  - Working in heap, MUST be manually allocated/deallocated or program will face memory leaks (memory
		will be indefinitely allocated, not being possible to reuse)
	  - It can be reassigned, which diminishes control over access (what address is currently pointing to?)
	  - Offer lots of opportunities to undefined behavior:
	  --- access a pointer that is null or not yet defined;
	  --- access a pointer after being deleted;
	  --- delete a pointer twice;
	  --- ...
	  - ALWAYS BE CARFEUL! VERY VERY CAREFUL! VERY! VEEEERY!
	----------------------------------------------------------------------------------------------*/

	//Working in STACK
	int var1 {10};
	int *ptr1;		//It is a pointer...
	ptr1 = &var1;	//...and points to the same space in memory allocated to var1
	cout << "&ptr1 = " << &ptr1 << endl;	//So, its address is...
	cout << "ptr1  = " << ptr1 << endl;		//...which points to address...
	cout << "&var1 = " << &var1 << endl;	//...that is the same address of var1...
	cout << "*ptr1 = " << *ptr1 << endl;	//Dereferencing it, the value stored in address pointed by ptr is...
	cout << "var1  = " << var1 << endl;		//the same value of var1

	cout << "Logical (ptr1)  = " << ptr1 << endl;
	cout << "Logical (!ptr1) = " << !ptr1 << endl;

	//Working in HEAP
	int *ptr2 = new int;
	int *ptr3 = new int{36};   //Creates a pointer which points to an int that stores value 36
	//int *ptr3 = new int(36); //The same for C++ versions below 11

	delete ptr2; //if you allocate memory with new, YOU shall EXPLICITLY free the memory!
	delete ptr3; //NEVER forget it! No memory leaks, PLEASE!
	//From now until the end of the program, ptr2 and ptr3 are DANGLING POINTERS
	//They exist, but do not point to valid memory; access them it's DANGEROUS!

	//Operations
	point2D *ptr4 = new point2D{20, 30};
	cout <<"point2D ptr4->x = " << ptr4->x << endl; //Dereferencing when using structures
	cout <<"point2D ptr4->y = " << ptr4->y << endl;
	delete ptr4;

	//More details of arrays in the end section of this file...
	int sizeArray = 10;
	int *ptrArray = new int[sizeArray]; //contiguous block of size equal to (10 x sizeof(int)) allocated, non-initialized
	int *ptrI = new int;
	int num;
	
	for (ptrI = ptrArray,num=0; ptrI < ptrArray+sizeArray; ptrI++,num+=2) *ptrI = num;
	cout << "Array (method 1) = "; for (int i=0;i<sizeArray;i++) { cout << ptrArray[i] << " "; } cout << endl;

	for (num=0;num<sizeArray;num++) ptrArray[num] = num;
	cout << "Array (method 2) = "; for (int i=0;i<sizeArray;i++) { cout << ptrArray[i] << " "; } cout << endl;

	delete [] ptrArray;
	delete ptrI;

	cout << endl;
	//----------------------------------------------------------------------------------------------




	//----------------------------------------------------------------------------------------------
	//SMART POINTERS
	//----------------------------------------------------------------------------------------------
	/*- Shall always be preferred instead of traditional C pointers;
	  --- auto_ptr: first version, should not be used with C++11 or higher (it has its problems!)
	  --- unique_ptr: the most used, does not share memory between variables
	  --- shared_ptr: with higher overhead comparing to unique, allows two variables to share the same memory
	----------------------------------------------------------------------------------------------*/




	//----------------------------------------------------------------------------------------------
	//SMART POINTERS - UNIQUE_PTR
	//----------------------------------------------------------------------------------------------
	/*- Class where the pointer is a private member, with some public methods to operate it
	  - Lightweight, with no more overhead than a traditional pointer; it is actually a simple wrapper
		to traditional pointers
	  - Only one instance of the class can access allocated memory
	  - Follows principles of RAII (Resource allocation is initialization)
	  --- memory allocated is class constructor, released in class destructor
	  --- programmer doesn't need to manage memory
	----------------------------------------------------------------------------------------------*/
	unique_ptr<int> uptr1;
	auto uptr2 {make_unique<int>(15)}; //initialized with a int space storing 15
	//unique_ptr<int> uptr3 {new int(36)}; //initialized with a int space storing 36 (C++11 or lower)

	cout << "&uptr2 = " << &uptr2 << endl;		//So, its address is...
	cout << "uptr2  = " << uptr2.get() << endl;	//...which points to address...
	cout << "*uptr2 = " << *uptr2 << endl;		//Dereferencing it, the value stored in address pointed by ptr is...

	cout << "Logical (uptr2)  = " << uptr2.operator bool() << endl;
	cout << "Logical (!uptr2) = " << !uptr2 << endl;

	//Not supported: operations ++uptr2; copy uptrX(uptr2); assignment uptrX = uptr2;

	auto uptr4 { make_unique<point2D>( point2D{10,15} ) };
	//unique_ptr<point2D> uptr4 {new point2D{10,15} }; //C++11 or lower
	cout << "point2D uptr4->x = " << uptr4->x << endl; //Dereferencing when using structures
	cout << "point2D uptr4->y = " << uptr4->y << endl;

	auto uptr5 { make_unique<point2D>( point2D{40,55} ) };
	uptr4.swap(uptr5);
	cout << "point2D uptr4->x after swap = " << uptr4->x << endl;
	cout << "point2D uptr4->y after swap = " << uptr4->y << endl;
	cout << "point2D uptr5->x after swap = " << uptr5->x << endl;
	cout << "point2D uptr5->y after swap = " << uptr5->y << endl;
	swap(uptr4,uptr5); //swapping again with non-member function

	unique_ptr<int> uptr6 {create_ptr()};
	cout <<"uptr6 created by function = " << *uptr6 << endl;

	unique_ptr<int[]> uptrArray(new int[sizeArray]); //SizeArray declared in traditional pointers block; calls delete when destroyed

	//NOT applicable to unique_ptr!
	// int *ptrI = new int;
	// for (ptrI = uptrArray, num=0; ptrI < uptrArray+sizeArray; ptrI++,num+=2) *ptrI = num;
	// cout << "Array (method 1) = "; for (int i=0;i<sizeArray;i++) { cout << uptrArray[i] << " "; } cout << endl;

	for (num=0;num<sizeArray;num++) uptrArray[num] = num;
	cout << "Array = "; for (int i=0;i<sizeArray;i++) { cout << uptrArray[i] << " "; } cout << endl;
	cout << "Array = "; for (int i=0;i<sizeArray;i++) { cout << uptrArray.get()[i] << " "; } cout << endl;

	uptrArray.reset(); //uptrArray.get() == Nullptr //Do not use tough; release it is automatic

	cout << endl;
	//----------------------------------------------------------------------------------------------


	//----------------------------------------------------------------------------------------------
	//SMART POINTERS - SHARED_PTR
	//----------------------------------------------------------------------------------------------
	/*- Class where the pointer is a private member, with some public methods to operate it
	  - Uses more memo than traditional/unique pointers once it has an internal counter to keep track
		of the copies accessing the allocated memo
	  - Extra overhead than traditional/unique pointers managing internal counter
	  - Multiple instances of the class can access shared heap allocated memory
	  - Memory allocated is released when the last of pointers using it cease to exist (internal
		counter reaches zero)
	  - Follows principles of RAII (Resource allocation is initialization)
	  --- memory allocated is class constructor, released in class destructor
	  --- programmer doesn't need to manage memory
	//----------------------------------------------------------------------------------------------
	//SMART POINTERS - SHARED_PTR WEAK (not demonstrated into code)
	//----------------------------------------------------------------------------------------------
	  - It is a shared_ptr but for readonly purposes; it does not affect internal counter
	  - It also does not know if the shared_ptr is still valid, must check before access
	----------------------------------------------------------------------------------------------*/
	shared_ptr<int> sptr1;
	auto sptr2 {make_shared<int>(15)};  //memory and counter are allocated in one allocation
										//into a single block of memo; are deallocated together also
	shared_ptr<int> sptr3 {new int(36)}; //explicit NEW is less efficient once memory and counter are
										 //allocated separately, in different blocks of memo); deallocation
										 //is separately too

	cout << "&sptr2 = " << &sptr2 << endl;		//So, its address is...
	cout << "sptr2  = " << sptr2.get() << endl;	//...which points to address...
	cout << "*sptr2 = " << *sptr2 << endl;		//Dereferencing it, the value stored in address pointed by ptr is...

	cout << "Logical (sptr2)  = " << sptr2.operator bool() << endl;
	cout << "Logical (!sptr2) = " << !sptr2 << endl;

	//Not supported: operations ++sptr2;
	//Supported: copy sptrX(sptr2); assignment sptrX = sptr2;

	auto sptr4 { make_shared<point2D>( point2D{10,15} ) };
	//unique_ptr<point2D> sptr4 {new point2D{10,15} }; //C++11 or lower
	cout << "point2D sptr4->x = " << sptr4->x << endl; //Dereferencing when using structures
	cout << "point2D sptr4->y = " << sptr4->y << endl;

	auto sptr5 { make_shared<point2D>( point2D{40,55} ) };
	sptr4.swap(sptr5);
	cout << "point2D sptr4->x after swap = " << sptr4->x << endl;
	cout << "point2D sptr4->y after swap = " << sptr4->y << endl;
	cout << "point2D sptr5->x after swap = " << sptr5->x << endl;
	cout << "point2D sptr5->y after swap = " << sptr5->y << endl;
	swap(sptr4,sptr5); //swapping again with non-member function

	shared_ptr<int> sptr6 {create_ptr()};
	cout <<"sptr6 created by function = " << *sptr6 << endl;

	//NOT applicable to shared_ptr!
	//shared_ptr<int[]> sptrArray(new int[sizeArray]); //SizeArray declared in traditional pointers block

	// int *ptrI = new int;
	// for (ptrI = sptrArray, num=0; ptrI < sptrArray+sizeArray; ptrI++,num+=2) *ptrI = num;
	// cout << "Array (method 1) = "; for (int i=0;i<sizeArray;i++) { cout << sptrArray[i] << " "; } cout << endl;

	//for (num=0;num<sizeArray;num++) sptrArray[num] = num;
	//cout << "Array = "; for (int i=0;i<sizeArray;i++) { cout << sptrArray[i] << " "; } cout << endl;

	//sptrArray.reset();

	cout << endl;
	//----------------------------------------------------------------------------------------------





	//----------------------------------------------------------------------------------------------
	//BUILT-IN ARRAYS AND POINTERS
	//----------------------------------------------------------------------------------------------
	int varArray[] = {4, 3, 2, 1};
	cout << "varArray contains: "; for (int i=0;i<4;i++) { cout << varArray[i] << " "; } cout << endl;
	cout << "varArray     = " << varArray << endl;
	cout << "&varArray[0] = " << &varArray[0] << endl;
	int *ptrVarArray = varArray;
	cout << "ptrVarArray  = " << ptrVarArray << endl;
	cout << "*ptrVarArray = " << *ptrVarArray << endl;

	//Sum numbers (offset) in the pointer gives the next addresses for the next items:
	cout << "varArray[0]: ptrVarArray     = " << ptrVarArray   << "; *(ptrVarArray)   = " << *ptrVarArray << endl;
	cout << "varArray[1]: ptrVarArray + 1 = " << ptrVarArray+1 << "; *(ptrVarArray+1) = " << *(ptrVarArray+1) << endl;
	cout << "varArray[2]: ptrVarArray + 2 = " << ptrVarArray+2 << "; *(ptrVarArray+2) = " << *(ptrVarArray+2) << endl;

	//Operate over pointers also possible:
	cout << "ptrVarArray   = " << ptrVarArray << "; *ptrArray = " << *ptrVarArray << endl;
	++ptrVarArray;
	cout << "++ptrVarArray = " << ptrVarArray << "; *ptrArray = " << *ptrVarArray << endl;
	++ptrVarArray;
	cout << "++ptrVarArray = " << ptrVarArray << "; *ptrArray = " << *ptrVarArray << endl;
	--ptrVarArray;
	cout << "--ptrVarArray = " << ptrVarArray << "; *ptrArray = " << *ptrVarArray << endl;

	//See FOR with pointers for array in 'traditional pointers' section of this file

	//Always consider iterations calculating the number of offsets (items):
	auto sizeVarArray = sizeof(varArray)/sizeof(int);
	cout << "varArray contains: "; for (size_t i=0;i<sizeVarArray;i++) { cout << varArray[i] << " "; } cout << endl;

	//In case of char vectors, can leave iteration when reach '\0':
	char varArrayChr[] = "Testing";
	cout << "varArrayChr contains: "; for (char *ptrChr=varArrayChr; *ptrChr!='\0'; ptrChr++) cout << *ptrChr << " "; cout << endl;

	//Arrays are never passed by value to functions once that cannot be copied.
	//
	//Passing by address and decaying into a pointer (no matter size); for that, is necessary to
	//pass the size of the vector along!
	//	int varArray1[] = {1, 3, 5, 7};					//Array of 4 integers
	//	int varArray2[] = {1, 3, 5, 7, 9};				//Array of 5 integers
	//	function1(varArray1, 4);						//&varArray[0] is passed
	//	function1(varArray2, 5);						//&varArray[0] is passed
	//	void function1 (int *array1, int len) {...}		//Is working with a pointer!
	//	void function1 (int array1[]), int len {...}	//Same thing, different notation only
	//
	//Passing by reference (size must be known by compiler):
	//	int varArray1[] = {1, 3, 5, 7};			//Array of 4 integers
	//	int varArray2[] = {1, 3, 5, 7, 9};		//Array of 5 integers
	//	void function1 (int &array1[4]) {...}	//Array of 4 references to int - ERROR!
	//	void function1 (int (&array1)[4]) {...}	//Reference to array of 4 ints - OK!
	//	function1(varArray1);					//OK
	//	function1(varArray2);					//Expects size 4! - ERROR!
	//
	//Suming up:
	//- Cannot be copied, so cannot be passed by value;
	//- Can be passed by reference only when the size is know at compile time;
	//- Are usually passed by address decaying into a pointer;
	cout << endl;
	//----------------------------------------------------------------------------------------------



	//----------------------------------------------------------------------------------------------
	//CLASS WITH POINTERS
	//----------------------------------------------------------------------------------------------
	class WithPtr {
		private:
			char *p;
			int n;
		public:
			//RAII: allocates when create, releases when destroy
			WithPtr(int n) : n(n) { p = new char[n]; }
			~WithPtr() { delete [] p; }

			void PrintWithPtr() const {
				cout << "Array of class WithPtr = ";
				for (int i=0; i<n; i++) cout << p[i] << " ";
				cout << endl;
			}

			//If we do not specify copy constructor, the compiler will create it; but using
			//traditional pointers inside the class, this can imply in disastrous behavior!
			//Compiler-generated version will perform 'shallow copy' copying pointer address only;
			//both instances will point to the same area of memory, which is not the desired:
			//- if first object changes the value stored in the address, both instances will be
			//  affected
			//- once one of the objects is destroyed, the memo is released and the other will be
			//  pointing to null
			//- when the second object is released, the pointer will be deleted twice
			//
			//Compiler-generated copy constructor (shallow copy):
			//		WithPtr(const WithPtr &other) : n(other.n), p(other.p) {}
			//Implementation of copy constructor (deep copy):
					WithPtr(const WithPtr &other) : n(other.n) {
						p = new char[n];
						for (int i=0; i<n; i++) p[i]=other.p[i];
					}

			//If we do not specify assignment operator, the compiler will create it; but
			//using traditional pointers inside the class, this can imply in disastrous
			//behavior! Compiler-generated version will assign memory addresses only; along
			//with all bullets pointed out in the copy constructor above, it will also
			//imply in memory leak, once that memory allocated to one object will not be
			//released previously to the assignment and it will no longer be accessible to
			//the program
			//
			//Compiler-generated assignment operator (shallow assignment):
			//		WithPtr & operator = (const WithPtr &other) {
			//			n=other.n; p=other.p; return *this;
			//		}
			//
			//Implementation of assignment operator (deep assignment):
			WithPtr & operator = (const WithPtr &other) {
				if (this != &other) //preventing self-assignment, obj1 = obj1
				{
					n = other.n;
					delete [] p;
					p = new char[n];
					for (int i=0; i<n; i++) p[i]=other.p[i];
				}
				return *this;
			}
	};

	WithPtr obj1(5);	//Constructor
	WithPtr obj2(obj1);	//Copy constructor
	obj2 = obj1;		//Assignment operator
	//----------------------------------------------------------------------------------------------




	//----------------------------------------------------------------------------------------------
	//PREFIX AND POSTFIX OPERATORS
	//----------------------------------------------------------------------------------------------
	int *ptr = varArray;
	cout << "\n*ptr     = " << *ptr;  

	cout << "\n*++ptr   = " << *++ptr;			//ptr = ptr + 1; *ptr;
	cout << "\n*(++ptr) = " << *(++ptr);		//idem

	cout << "\n++(*ptr) = " << ++(*ptr);		//*ptr = *ptr + 1;

	cout << "\n*ptr++   = " << *ptr++;			//auto temp = ptr; ptr = ptr + 1; *temp;
	cout << "\n*(ptr++) = " << *(ptr++);		//idem

	//Observe the overhead of var++ when compared to ++var; when doesn't matter the order, use second;

	int x{2};
	cout << "\nx(" << x << ")";
	int y = x++;	//y = x; x = x+1;
	cout << "\nx(" << x << "); y(" << y << ")";
	int z = ++x;	//x = x+1; z = x;
	cout << "\nx(" << x << "); z(" << z << ")";
	
	//To overload prefix operator in classes:
	//		ClassName & operator ++() { member = member + 1; return *this; }
	//
	//To overload postfix operator in classes:
	//		ClassName & operator ++(int t) {	//Dummy argument to differentiate of prefix
	//			ClassName tempVar(*this);		//Copies the current value
	//			member = member + 1;			//Increases
	//			return tempVar;					//Returns original value
	//		}
	cout << endl;
	//----------------------------------------------------------------------------------------------


	cout << "END OF PROGRAM" << endl;
	return 0;
}
