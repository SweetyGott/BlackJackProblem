#pragma once

#include "Config.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

#define SolSize 105000

class SequenzCreator {
	/*
		* n zwischen 1 und 9
		* erzeugt Sequenz von 20 Elementen, wobei immer n oder n+10 erreicht werden kann
	*/
private:
	int n, n_big;

	solution temp_sol;

	uint64_t numSolutions;

	std::vector<solution> sol;
	std::bitset<NumCards> set_mask;

	ofstream myfile;


	void setValue( const int = 0, const int = 0 );
	int checkSequenz(int, int);

	std::bitset<NumCards> startwert_mask;
	std::bitset<NumCards> manual_mask;

public:
	SequenzCreator( int );
	solution* getSolution(int);
	int getAnzahlSol();


};