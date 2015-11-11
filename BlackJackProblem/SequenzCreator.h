#pragma once

#include "Config.h"

#include <iostream>
#include <fstream>

using namespace std;


/**Estimated anzahl Sequents
2		6000
3		100000
4		500000
5		900000
6		3500000
7		70000000
8		70000000
9		0
*/


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

	int(*solutions)[NumCards + 10];
	//int solutions[SolSize][NumCards+10];
	int SolutionSpace;
	ofstream myfile;


	void setValue( const int = 0, const int = 0 );
	int checkSequenz(int, int);

public:
	SequenzCreator( int );
	int* getSolution(int);
	int getAnzahlSol();


};