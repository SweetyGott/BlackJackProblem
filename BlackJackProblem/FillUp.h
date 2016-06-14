#pragma once

#include "SequenzCreator.h"

class FillUp {

public:
	FillUp( SequenzCreator*, uint8_t);
private:

	uint64_t globsucces, globfail;
	solution* sol;
	uint8_t* tocards[F];//Zu setzende Karten
	uint8_t points[7];	//Punktestand der einzelnen Spieler
	
	uint64_t success[7];//Wie viele Erfolglösungen für den einzelnen Spieler gefunden wurden

	ofstream myfile;

	void nextnum(uint8_t = 0);
	inline bool checkNumPlayer(uint8_t);
};
