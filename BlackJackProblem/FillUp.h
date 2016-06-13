#pragma once

#include "SequenzCreator.h"

class FillUp {

public:
	FillUp( SequenzCreator*, int );
private:

	uint64_t globsucces, globfail;
	solution* sol;
	int* tocards[F];//Zu setzende Karten
	int points[7];	//Punktestand der einzelnen Spieler
	
	uint64_t success[7];//Wie viele Erfolglösungen für den einzelnen Spieler gefunden wurden

	ofstream myfile;

	void nextnum(int = 0);
	bool checkNumPlayer( int );
};
