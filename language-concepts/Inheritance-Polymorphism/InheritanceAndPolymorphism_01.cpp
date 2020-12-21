//============================================================================
// Name        : InheritanceAndPolymorphism.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge in Inheritance and Polymorphism (static/dynamic binding, virtual class management)
//============================================================================

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main() {


	//---------------------------------------------------------------------------------------------------
	//POLYMORPHISM: STATIC TYPE AND DYNAMIC BINDING
	//---------------------------------------------------------------------------------------------------
	/*Before talking about static/dynamic types, follows an explanation of how classes (super and sub)
	behave in memory and can be binded: */

		class Drawable{
			public:
				void draw() { cout << "Drawable!" << endl; };
		};
		class Circle : public Drawable {
			public:
				void draw() { cout << "Circle!" << endl; }
		};
		class Square : public Drawable {
			public:
				void draw() { cout << "Square!" << endl; }
		};

		cout << "---" << endl;
		Drawable D1;	D1.draw();
		Circle C1;		C1.draw();
		cout << endl;

	/*In memo, what happens is that C1 has an internal instance of Draw and also the specialized part
	of Circle:
	
				 <--Drawable-->
				 +------------+---------------+
			C1 = |            |               |
				 +------------+---------------+
				 <-----------Circle----------->
	
	The address of the internal Drawable instance is also the address of the Circle instance; so, it is
	possible to bind a reference to the superclass to an instance of its derived class:
	  		Circle C2;
	  		Drawable &D2 = C2;			//Binds reference to class Drawable of Circle C2
	  		Drawable *ptrD3 = &C2;		//Pointer to Drawable instance of Circle C2...
	  		*ptrD3;						//...dereferencing then the Drawable portion of C2
	  
	  		Drawable D3;
	  		Circle &C3 = D3;	//ERROR! Every Circle is a Drawable, but not every Drawable
	  							//is a Circle; compiler cannot know the memo object that D3
	  							//is bound to!
	  
	The static type of D2 is a reference to Drawable; the dynamic type of D2 is a reference to Circle. Why?
	  
	Static type is the type used in declaration, defined in compile time:
	  		+-----VAR---------+------STATIC TYPE------+
	  		int x{5};			//int
	  		int &x{5};			//Reference to int
	  		Circle C1;			//Circle
	  		Circle &C2 = C1;	//Reference to Circle
	  		Drawable &C2 = C1;	//Reference to Drawable
	  
	Dynamic type is the type represented by variable's memory object. It is usually equal to the static
	type, but it may not be know until runtime, case of pointers:
	  		+-----VAR---------+-----DYNAMIC TYPE------+
	  		int x{5};			//int
	  		int &x{5};			//Reference to int
	  		Circle C1;			//Circle
	  		Circle &C2 = C1;	//Reference to Circle
	  		Drawable &C2 = C1;	//Reference to Circle
	  
	OK! But for what dynamic types are useful?
	 
	Let's say that we have several different shapes and we need to store all them in a vector to submit all
	of them to the method 'Draw' present in superclass Drawable but also override in subclasses. The vector
	can only have one type of objects. So: */

		cout << "***" << endl;
		vector<unique_ptr<Drawable>> shapes;	//All shapes are derived of Drawable!
		Circle Circ;	shapes.push_back(make_unique<Circle>(Circ));
		Square Squr;	shapes.push_back(make_unique<Square>(Squr));
		for (auto &shape : shapes)
			shape->draw();		//Hum! But what is the right member? 'draw' of Drawable
		cout << endl;			// defined by static binding made at the compile time!

	//How to solve?
	//Defining the Draw method of Drawable as Virtual!


	//---------------------------------------------------------------------------------------------------
	//VIRTUAL FUNCTIONS
	//---------------------------------------------------------------------------------------------------
	/*Transforming Drawable in virtual class to solve above problem. Here, the word 'override' used is not
	necessary, but it helps the compiler to perform checks that assure that we in fact have the virtual
	corresponding function in base class: */

		class DrawableV2{
			public:
				virtual ~DrawableV2() {}
				virtual void draw() = 0;	//pure virtual function; turns DrawableV2 into asbtract class
		};
		class CircleV2 : public DrawableV2 {
			public:
				void draw() override { cout << "Circle!" << endl; }
		};
		class SquareV2 : public DrawableV2 {
			public:
				void draw() override { cout << "Square!" << endl; }
		};

	//Now the loop FOR will call 'Draw' method of subclasses, resolved during runtime:

		cout << "###" << endl;
		vector<unique_ptr<DrawableV2>> shapesV2;	//All shapes are derived of Drawable!
		CircleV2 CircV2;	shapesV2.push_back(make_unique<CircleV2>(CircV2));
		SquareV2 SqurV2;	shapesV2.push_back(make_unique<SquareV2>(SqurV2));
		for (auto &shape : shapesV2)
			shape->draw();		//Hum! But what is the right member? 'draw' of subclasses
		cout << endl;			//defined by dynamic binding made at the runtime!

	/*Let's imagine now that we need to add some 'draw_shape' function that uses 'draw' method to all our
	shapes. The code is the same: */

		class DrawableV3{
			public:
				virtual ~DrawableV3() {}
				virtual void draw() = 0;
		};
		class CircleV3 : public DrawableV3 {
			public:
				void draw() override { cout << "Circle!" << endl; }
				void draw_shape(CircleV3 &c) { c.draw(); }
		};
		class SquareV3 : public DrawableV3 {
			public:
				void draw() override { cout << "Square!" << endl; }
				void draw_shape(SquareV3 &s) { s.draw(); }
		};

	/*This is inefficient cause we are replicating code unnecessarily. If we need to change, we will have
	to do it in several functions. If we create other shape class, we will have to carry the code for the
	3rd class. It is better to have one single function in the base class that does the work considering
	the possibility of dynamic binding. So we do this instead: */

		class DrawableV4{
			public:
				virtual ~DrawableV4() {}
				virtual void draw() = 0;

				static void draw_shape(DrawableV4 &d) { d.draw(); }
				//Will use dynamic binding; the instances calling 'draw_shape' will
				//be used to decide during runtime what method of which subclass to call
		};
		class CircleV4 : public DrawableV4 {
			public:
				void draw() override { cout << "Circle!" << endl; }
		};
		class SquareV4 : public DrawableV4 {
			public:
				void draw() override { cout << "Square!" << endl; }
		};

		cout << "&&&" << endl;
		CircleV4 C1v4;	DrawableV4::draw_shape(C1v4);
		SquareV4 S1v4;	DrawableV4::draw_shape(S1v4);

	cout << endl;
	//---------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------
	//VTABLE - Compiler's structure to manage virtual functions
	//---------------------------------------------------------------------------------------------------
	/*- When the compiler encounters a virtual member function, it generates extra code; for each subclass
		overriding it, it creates a version of the code for dynamic typing to find the appropriate one

	  - It also populates the VTBALE structure for each class with virtual member functions; it stores the
		addresses of all member functions that are virtual (member functions of classes are implemented by
		the compiler as global functions and when they are called, a pointer to the instance calling is
		passed as argument named "this"; so, that's why the vtable stores only addresses):

	  		vtable CircleV4 =	| ptr | -----> draw()
	  							| ptr | -----> rotate()
	  							etc

	  		vtable SquareV4 =	| ptr | -----> draw()
	  							| ptr | -----> translate()
	  							etc

	  - For all that, using virtual members has some overhead:
	  --- It takes 25-50% longer to call a virtual function compared to a non-virtual one
	  --- Extra memory allocation for VTABLE
	//-------------------------------------------------------------------------------------------------*/


	//---------------------------------------------------------------------------------------------------
	//VIRTUAL DESTRUCTORS
	//---------------------------------------------------------------------------------------------------
	/*Before, let's remember the memory allocation for a Circle:

	  			 	 <--Drawable-->
	  			 	 +------------+---------------+
	  		Circle = |            |               |
	  			 	 +------------+---------------+
	  			 	 <-----------Circle----------->

	The code:
	  		Drawable *D = new Circle;
	  		delete D;

	is expected to delete the memory of circle. It happens only if the base class has virtual destructor
	declared. Otherwise, a non-virtual destructor will consider the static type of the instance and destroy
	only the base part, leaving the derived part intact (memory leak).

	Compiler-generated destructors are always non-virtual; it shall be explicitly declared and named virtual
	on the base class. As any other virtual function, if it is virtual on the base class, will automatically
	be in the subclasses as well, no need to declare destructors virtual in each subclass
	//---------------------------------------------------------------------------------------------------*/

	cout << "END OF PROGRAM" << endl;
	return 0;
}
