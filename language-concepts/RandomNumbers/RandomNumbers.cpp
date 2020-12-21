//============================================================================
// Name        : GenericAlgorithms.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of random functions for number generation:
//					rand, srand, random_device, random engines/distributions
//					Examples of generic algorithms shuffle and generate_n
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <chrono> //sleep_for
#include <thread> //sleep_for
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

//---------------------------------------------------------

mt19937 eng(time(0));
int FunctionRandomNumber(){
	uniform_int_distribution<int> dist(0,1000);
	return dist(eng);
}

//---------------------------------------------------------

int main() {

	int idx = 1;	//Only to organize couts!
	
	//----------------------------------------------------------------------------------------------------------
	//RAND
	//----------------------------------------------------------------------------------------------------------
	//- Inherited from C in <cstdlib>
	//- Is not actually random...
	//- If escaled between a range, it introduces bias, some numbers appear more than others
	//- Guessing next number is not so hard, shall not be used for cryptography
	
	//between 0 and RAND_MAX 32767
		int r1 = rand();
		cout << printIdx(idx++) << "rand() = " << r1 << endl;
	
	//between 0 and 1
		float r2 = 1.0 * rand()/RAND_MAX;
		cout << printIdx(idx++) << "rand() escaled between 0 and 1 = " << r2 << endl;
		
	 //between 1 and 100
		int r3 = 99 * rand()/RAND_MAX + 1;
		cout << printIdx(idx++) << "rand() escaled between 1 and 100 = " << r3 << endl;


	//----------------------------------------------------------------------------------------------------------
	//SRAND
	//----------------------------------------------------------------------------------------------------------
	//- Inherited from C in <cstdlib>
	//- If seeded with TIME <ctime>, is relatively easy to discover according to time when program started;
	
	//between 0 and RAND_MAX 32767
		srand(time(0)); int r4 = rand();
		cout << printIdx(idx++) << "srand(time) + rand() = " << r4 << endl;
		
	//between 0 and 1
		srand(time(0)); float r5 = 1.0 * rand()/RAND_MAX;
		cout << printIdx(idx++) << "srand(time) + rand() escaled between 1 and 0 = " << r5 << endl;
		
	//between 1 and 100
		srand(time(0)); int r6 = 99 * rand()/RAND_MAX + 1;
		cout << printIdx(idx++) << "srand(time) + rand() escaled between 1 and 0 = " << r6 << endl;


	//----------------------------------------------------------------------------------------------------------
	//ENGINES + DISTRIBUTIONS
	//----------------------------------------------------------------------------------------------------------
	/*- From isoccp.org (https://isocpp.org/files/papers/n3551.pdf):
	  --- An engine’s role is to return unpredictable (random) bits ensuring that the likelihood of next
	      obtaining a 0 bit is always the same as the likelihood of next obtaining a 1 bit;
	  --- A distribution’s role is to return random numbers (variates) whose likelihoods correspond to a specific
		  shape. E.g., a normal distribution produces variates according to a "bell-shaped curve."
	  --- It is necessary an object of each kind in order to obtain a random variate; the purpose of the engine
		  is to serve as a source of randomness. We always use a distribution as well to give context for the
		  request

	  - Two most used random number engines (see doc for others):
	  --- default_random_engine: uses rand(); avoid!
	  --- mt19937: "Mersenne Twister" with period 2^19937 - 1; almost impossible to guess next number; the best
		  choice for most requirements

	  - Two very used distributions:
	  --- uniform_int_distribution
	  --- uniform_real_distribution
	*/
	
	//Declaring of enginee MT19937 and UNIFORM distribution for integers (between 0 and 100):
		mt19937 engineRand;
		uniform_int_distribution<int> dist1(0,100);

	//Examples
		cout << printIdx(idx++) << "engine mt19937 with uniform_int_distribution 0-100 = " << dist1(engineRand) << endl;
		cout << printIdx(idx++) << "engine mt19937 with uniform_int_distribution 0-100 = " << dist1(engineRand) << endl;

	//Changing UNIFORM distribution for real numbers (between 0 and 1):
		uniform_real_distribution<double> dist2(0,1);
		cout << printIdx(idx++) << "engine mt19937 with uniform_real_distribution 0-1 = " << dist2(engineRand) << endl;

	//Declaring BERNOULLI distribution for bool values (equal chances for true and false):
		bernoulli_distribution dist3;
		cout << printIdx(idx++) << "engine mt19937 with bernoulli_distribution (equal chances) = " << dist3(engineRand) << endl;

	//Declaring BERNOULLI distribution for bool values (75% chances of true):
		bernoulli_distribution dist4 (0.75); //changes uniformity
		cout << printIdx(idx++) << "engine mt19937 with bernoulli_distribution (0.75 chances of true) = " << dist4(engineRand) << endl;
		
	
	//----------------------------------------------------------------------------------------------------------
	//RANDOM_DEVICE (for seeding the engine)
	//----------------------------------------------------------------------------------------------------------	
	//- Hardware-generated seed from system entropy data (mouse moves and others)
	//- Much slower than other methods, but the most secure (and most random!)
	//- Depends of support of OS and compiler; has to be checked wether supported or not
	//- Highly used as seed for ENGINE + DISTRIBUTION
	
	//Declaring
		random_device seedRD;
	
	//Testing random_device behavior (pseudo-random number engine = rand(); random number engine = really random)
		cout << printIdx(idx++) << "Testing random_device seeding: " << (seedRD.entropy() == 0.0 ? "PRNG =(" : "RNG =)") << endl;

	//Declaring engine using seed random_device (valid for systems with RNG behavior)
		mt19937 engineRand2(seedRD());
		uniform_int_distribution<int> dist5(0,100);

	//Declaring engine using other seeds (usual to use time; for PRNG behavior)
		mt19937 engineRand3(time(0));

	//Using as usual
		cout << printIdx(idx++) << "engine mt19937 seeded by random_device with uniform_int_distribution 0-100 = " << dist5(engineRand2) << endl;
		cout << printIdx(idx++) << "engine mt19937 seeded by time() with uniform_int_distribution 0-100 = " << dist5(engineRand3) << endl;


	//----------------------------------------------------------------------------------------------------------
	//Generic Algorithms Examples: SHUFFLE, GENERATE_N
	//----------------------------------------------------------------------------------------------------------
	
	//SHUFFLE
		vector<int> vecI1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		cout << printIdx(idx++) << "Vector { " << print(vecI1) << "} using SHUFFLE with engine mt19937 seeded by random_device;\n";
		shuffle(vecI1.begin(), vecI1.end(), engineRand2);
		cout << "\tResult in same vector { " << print(vecI1) << "}" << endl;

	//GENERATE_N
		vector<int> vecI2(5);
		generate_n(vecI2.begin(), 5, FunctionRandomNumber);
		cout << printIdx(idx++) << "Vector size 5, fulfilled by GENERATE_N with custom 'FunctionRandomNumber';\n\tResult { " << print(vecI2) << "}\n";
	
		vector<int> vecI3(5);
		generate_n(vecI3.begin(), 5, engineRand2);
		cout << printIdx(idx++) << "Vector size 5, fulfilled by GENERATE_N with engine mt19937 seeded by random_device;\n\tResult { " << print(vecI3) << "}\n";


	//----------------------------------------------------------------------------------------------------------
	//Application to use random (run in terminal, not in eclipse console)...
	//----------------------------------------------------------------------------------------------------------
		cout << "Printing some random dots...\n";
		
		mt19937 engRandDots(time(0));
		bernoulli_distribution distDots (0.6);	//true with 60% of chances
		
		enum direction {LEFT=-1, RIGHT=1};
		const int maxIter = 150;
		const int WIDTH = 25;
		int x = 1;
		direction sign = RIGHT;
		
		for (int i = 1; i <= maxIter; i++)
		{
			//Defining random direction of movement (true RIGHT, false LEFT)
			sign = distDots(engRandDots) ? RIGHT : LEFT;

			//Controlling boundaries
			if (x==1) sign = RIGHT;
			else if (x==WIDTH) sign = LEFT;

			//Moves one step into direction!
			x += sign;
			cout << "|" << string(x, ' ') << "." << string (WIDTH-x, ' ') << "| "<< i << " of " << maxIter << "\r" << flush; //stays in the same line

			//#include <chrono>
			//#include <thread>
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}


	cout << "END OF PROGRAM" << endl;
	return 0;
}