#pragma once

#include "Config.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;


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
	//std::bitset<NumCards> set_mask;

	ofstream myfile;


	void setValue( const int, const int );
	int checkSequenz(int, int);

	std::bitset<NumCards> startwert_mask;

	//Measuring
	uint64_t gesamtTest;
	uint64_t tiefe[NumCards - SeqStart + 1];

	//Dateiausgabe
	int numData;
	string s, se;

public:
	SequenzCreator( int );
	solution* getSolution(uint64_t);
	uint64_t getAnzahlSol();


};