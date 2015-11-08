#pragma once

#include "SequenzCreator.h"

class FillUp {

public:
	FillUp( SequenzCreator*, int );
private:

	int globsucces, globfail;
	int* stack;
	int* cards;
	int* tocards[6];//Zu setzende Karten
	int points[7];	//Punktestand

	ofstream myfile;

	void nextnum(int = 0);
	bool checkNumPlayer( int );
};
