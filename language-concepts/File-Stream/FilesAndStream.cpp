//============================================================================
// Name        : FilesAndStream.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Examples of stream and files
//============================================================================

#include <iostream>	//cin, cout
#include <fstream>	//istream, ostream, fstream
#include <iomanip>	//setw
#include <sstream>	//istringstream, ostringstream
#include <limits>	//cin.ignore
#include <string>

using namespace std;

int main() {

	cout << "\nReading input sample file (word by word) ......................................" << endl;
		string palavra;
		ifstream InFile;
		InFile.open("files/input.txt", ifstream::in); //read mode
		if (InFile) {
			while (InFile >> palavra)
				cout << palavra << endl;
		}
		else
			cout << "Ops! File <files/input.txt> not found!\n";
		InFile.close();
	
	cout << "\nReading input sample file (line by line) ......................................" << endl;
		string linha;
		InFile.open("files/input.txt");
		if (InFile) {
			while (getline(InFile,linha))
				cout << linha << endl;
		}
		else
			cout << "Ops! File <files/input.txt> not found!\n";
		InFile.close();

	cout << "\nWriting output file ..........................................................." << endl;	
		ofstream OutFile;
		OutFile.open("files/output.txt");
		if (OutFile) {
			OutFile << "Hellouuuu!" << endl;
			//Lembrar que escrita ostream trabalha com buffer; o flush em disco só é feito quando o buffer lota;
			//OutFile << something << flush; //força flushing, mas deve ser usado somente em caso de necessidade (performance)
			//endl = /n + flush
			cout << "Check <files/output.txt>!\n";
		}
		else
			cout << "Ops! File <files/output.txt> not writen!\n";
		OutFile.close();
	
	cout << "\nInput from keyboard (cin) ....................................................." << endl;
		int x;
		cout << "Type a number: ";
		cin >> x;
		
		if (cin.good())
			cout << "Uau! Good number!\n";
		else //cin.fail()
			cout << "I've said a NUMBER!\n";
			
		cin.clear(); cin.ignore (numeric_limits<streamsize>::max(), '\n'); //Due to ENTER that remains in buffer!
			//When used, it is always after cin.good / cin.fail
	
	cout << "\nIOManip for print ............................................................" << endl;
		cout << "Simply cout:\n";
		cout << "Mary " << 34 << " years" << endl;
		cout << "William " << 35 << " years" << endl;

		cout << "\nSome iomanip:\n";
		cout << setw(15) << "Mary " << setw(5) << 34 << "years" << endl;
		cout << setw(15) << "William " << setw(5) << 35 << "years" << endl;

		cout << "\nSome iomanip:\n";
		cout << left << setw(15) << "Mary " << setw(5) << 34 << "years" << endl;
		cout << left << setw(15) << "William " << setw(5) << 35 << "years" << endl;

		cout << "\nSome iomanip:\n";
		cout << setfill('.');
		cout << left << setw(15) << "Mary " << setw(5) << 34 << "years" << endl;
		cout << left << setw(15) << "William " << setw(5) << 35 << "years" << endl;
	
	cout << "\nOStringStream and cout ......................................................." << endl;
		ostringstream OutSStream;
		
		string var1;
		cout << "Type 1st word: ";
		cin >> var1;
		cin.clear(); cin.ignore (numeric_limits<streamsize>::max(), '\n');
		OutSStream << setw(15) << var1;

		cout << "Type 2nd word: ";
		cin >> var1;
		cin.clear(); cin.ignore (numeric_limits<streamsize>::max(), '\n');
		OutSStream << setw(20) << var1;

		cout << "You typed: " << OutSStream.str() << endl;
	
	cout << "\nIStringStream and cin ........................................................" << endl;
		string var2;
		cout << "Type text and/or numbers and press ENTER; numbers will be re-impressed (CTRL+Z / ENTER exit): " << endl;
		while (getline(cin,var2)) { //It never stops on eclipse! Take care! Run in cmd!
			istringstream InSStream(var2);
			int num;
			while (InSStream >> num)
				cout << num << endl;
		}


	cout << "END OF PROGRAM" << endl;
	return 0;
}
