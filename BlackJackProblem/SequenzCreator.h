#pragma once

#include "Config.h"

#include <iostream>
#include <fstream>

using namespace std;

#define SolSize 105000

class SequenzCreator {
	/*
		* n zwischen 1 und 9
		* erzeugt Sequenz von 20 Elementen, wobei immer n oder n+10 erreicht werden kann
	*/
private:
	int n, n_big;

	int tempsol[NumCards + 10];
	int* stack;
	int* seq;

	int numSolutions;
	//0-9 Flexset
	//10-29 Spezialsequenz
	//30-39 Stack der verlbeibenden Karten
	int solutions[SolSize][NumCards+10];

	ofstream myfile;


	void setValue( const int = 0, const int = 0 );
	int checkSequenz(int, int);

public:
	SequenzCreator( int );
	int* getSolution(int);
	int getAnzahlSol();


};