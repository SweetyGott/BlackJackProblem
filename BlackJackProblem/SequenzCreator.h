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
	int j1, j2;

	solution temp_sol;

	uint64_t numSolutions;

	std::vector<solution> sol;
	//std::bitset<NumCards> set_mask;

	ofstream myfile;

	//Bitmaske für die Karten, welche durch die Bank definiert werden (Menge B)
	std::bitset<NumCards> startwert_mask;

	//Measuring
	uint64_t gesamtTest;
	uint64_t tiefe[NumCards - SeqStart + 1];

	//Dateiausgabe
	int numData;
	string s, se;

	//Nächste Karte für die Sequenz setzen
	void setValue(const int, const int);
	//Überprüfe gültigkeit der Sequenz
	inline int checkSequenz(int, int);

public:
	SequenzCreator( int );
	solution* getSolution(uint64_t);
	uint64_t getAnzahlSol();


};