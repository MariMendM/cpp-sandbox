//============================================================================
// Name        : main.cpp (CoinsChange)
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//		Calculates the coins contained into a given ammount of money
//		  Example: $ 356 cents = 3 dollars / 1 half / 1 nickel / 1 penny
//		  Example: R$ 356 centavos = 3 reais / 50 centavos / 5 centavos /
//									 1 not handled by currency system (not funny with R$...!)
//============================================================================
// g++ -O0 -g3 -Wall -fmessage-length=0 -o main.out src/coin.cpp main.cpp
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "src/coin.h"

int check_input() {
	int input{0};
	do {
		std::cout << "Please enter the amount of change (between 1 and 499), or -1 to exit: ";
		std::cin >> input;
	} while (input < -1 || input == 0 || input > 499);
	return input;
}

std::vector<coin> populate_coins() {
	std::vector<coin> coins;
	coin dollar{ "dollar", "dollars", 100 };
	coins.push_back(dollar);
	coin half{ "half", "halves", 50 };
	coins.push_back(half);
	coin quarter{ "quarter", "quarters", 25 };
	coins.push_back(quarter);
	coin dime{ "dime", "dimes", 10 };
	coins.push_back(dime);
    coin nickel{ "nickel", "nickels", 5 };
	coins.push_back(nickel);
	coin penny{ "penny", "pennies", 1 };
	coins.push_back(penny);
	return coins;
}

std::vector<coin> populate_coins(const char* filename){
	std::vector<coin> coins;

	std::ifstream coinFile;
	coinFile.open(filename);
	if (coinFile){
		std::string fileLine;

		while(std::getline(coinFile,fileLine)){
			std::istringstream ISStream(fileLine);
			std::string singular, plural;
			int value;
			ISStream >> singular >> plural >> value;

			//METHOD 1 (using HEAP)
			//coin *c = new coin(singular, plural, value);
			//coins.push_back(*c);
			//delete c;

			//METHOD 2 (using STACK)
			coin c(singular, plural, value);
			coins.push_back(c);
		}
	}
	else
		std::cout << "ERROR: Problem reading coins config file!\n";

	return coins;
}

int main() {
	std::vector<coin> coins;

	//HARDCODED: AMERICAN COINS:
	//coins = populate_coins();

	//FILE: coins of any currency for which files are created
	coins = populate_coins("./coins-config/AmericanCoins.txt");
	//coins = populate_coins("BrazilianCoins.txt");

	if (coins.begin() == coins.end()) {
		std::cout << "Exiting...\n";
		return 1;
	}

	int input{0};
	while (input != -1) {
		input = check_input();

		int change{input};
		for (auto c : coins) {
			change = c.do_coin(change);
		}
		if (change != 0)
			std::cout << "Plus " << change << " not handled by currency system!" << std::endl; //R$ does not have 1 cent!
	}
	std::cout << "END";
	return 0;
}
