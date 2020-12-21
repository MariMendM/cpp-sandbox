
//Intention: demonstrate some effects of multiple inheritance, disable some warnings
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-value"

#include <iostream>

using namespace std;


int main()
{
	//http://citeseer.ist.psu.edu/viewdoc/download?doi=10.1.1.23.4735&rep=rep1&type=pdf
	//Bjarne Stroustrup - Multiple Inheritance for C++
	
	//Examples withut definite purpose, only to demonstrate concepts!
	
	
	//---------------------------------------------------------------------------------------
	//Independent multiple inheritance ------------------------------------------------------
	//---------------------------------------------------------------------------------------
	{
		class A {
			public:
				int var1 = 0;
				void fPrint(void) { cout << "\tfPrint A\n"; }
		};
		
		class B {
			public:
				char *var1;
				void fPrint(void) { cout << "\tfPrint B\n"; }
		};
		
		class C : public A, public B { };
		
		C objC;
	
		//Ambiguities:
			//objC.var1;			//error: request for member 'var1' is ambiguous
			//objC.fPrint();		//error: request for member 'fPrint' is ambiguous
		
		//Option 1: explicit qualification of scope...
			cout << "Multiple base classes: Solving ambiguities through explicit qualification of scope:\n";
			objC.A::var1;
			objC.B::var1;
			objC.A::fPrint();
			objC.B::fPrint();
			
		//Option 2: typecast...
			cout << "Multiple base classes: Solving ambiguities through typecast:\n";
			((A)objC).fPrint();
			B objB = objC;
			objB.fPrint();
			
	}
	
	//---------------------------------------------------------------------------------------
	//Virtual functions ---------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	{
		class A {
			public:
				virtual void fPrint(void) { cout << "\tfPrint A\n"; }
		};
		
		class B {
			public:
				virtual void fPrint(void) { cout << "\tfPrint B\n"; }
		};
		
		class C : public A, public B {
			public:
				void fPrint(void) { A::fPrint(); B::fPrint(); /*or anything else!*/}
		};
		
		C objC;
		
		cout << "Virtual functions: ambiguities solved by concept:\n";
			objC.fPrint();
		
		cout << "Virtual functions: explicit qualification of scope still works:\n";
			objC.A::fPrint();
			objC.B::fPrint();
			
		cout << "Virtual functions: typecast still works:\n";
			((A)objC).fPrint();
			B objB = objC;
			objB.fPrint();
			
	}
	
	
	//---------------------------------------------------------------------------------------
	//Diamond inheritance problem -----------------------------------------------------------
	//---------------------------------------------------------------------------------------
	
	//Attempt 1
	{
		class A {
			private:
				int num = 0;
			public:
				void setNum(int n) { num = n; };
				void fPrint(void)  { cout << "\tfPrint A with <" << num << ">\n"; }
		};
		
		class B : public A{
			public:
				B() { setNum(5); }
				void fPrint(void) { cout << "\tfPrint B\n"; }
		};
		
		class C : public A{
			public:
				C() { setNum(9); }
				void fPrint(void) { cout << "\tfPrint C\n"; }
		};
		
		class D : public B, public C { };
		
		D objD;
		
		//D object has two A parts, one for B and other for C
			//((A)objD).fPrint();		//error: 'main()::A' is an ambiguous base of 'main()::D'
		
		cout << "Diamond inheritance problem: explicit qualification of scope does not reach A:\n";
			//objD.C::A::fPrint();		//error: 'main()::A' is an ambiguous base of 'main()::D'
			//objD.B::A::fPrint();		//error: 'main()::A' is an ambiguous base of 'main()::D'
			objD.B::fPrint();
			objD.C::fPrint();
			
		cout << "Diamond inheritance problem: typecast works:\n";
			//Accessing A through C
				((A)(C)objD).fPrint();
			//Accessing A through B
				B objB = objD;
				A objA = objB;
				objA.fPrint();			
	}
	
	//Attempt 2 (now were talking!)
	{
		class A {
			private:
				int num = 0;
			public:
				void setNum(int n) { num = n; };
				void fPrint(void)  { cout << "\tfPrint A with <" << num << ">\n"; }
		};
		
		//The "virtualness" of A is a property of the derivation specified by B, not a property of A itself
		class B : virtual public A {
			public:
				B() { setNum(5); }
				void fPrint(void) { cout << "\tfPrint B\n"; }
		};
		
		//The "virtualness" of A is a property of the derivation specified by C, not a property of A itself
		class C : virtual public A {
			public:
				C() { setNum(9); }
				void fPrint(void) { cout << "\tfPrint C\n"; }
		};
		
		class D : public B, public C { 	};
		
		D objD;
		
		//D object has only one A part
		cout << "Diamond inheritance problem: solving with virtual inheritance:\n";
			((A)objD).fPrint();			//D::C::A - C last inherited
		
		cout << "Diamond inheritance problem: explicit qualification of scope now reaches A:\n";
			objD.A::fPrint();			//D::C::A - C last inherited
			objD.B::fPrint();
			
		cout << "Diamond inheritance problem: typecast works:\n";
			//Accessing A through C
				((A)(C)objD).fPrint();
				((A)(B)objD).fPrint();	//it only has C's part of A
	}
	
	cout << "END OF PROGRAM";
	return 0;
}