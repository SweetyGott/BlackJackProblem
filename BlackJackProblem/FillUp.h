#pragma once

#include "SequenzCreator.h"

class FillUp {

public:
	FillUp( SequenzCreator*, int );
private:

	uint64_t globsucces, globfail;
	solution* sol;
	int* tocards[6];//Zu setzende Karten
	int points[7];	//Punktestand der einzelnen Spieler

	ofstream myfile;

	void nextnum(int = 0);
	bool checkNumPlayer( int );
};
