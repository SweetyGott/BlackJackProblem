#pragma once

#include <stdint.h>

//SZENARIO AUSWAHL
#define T_4567
//#define T_567
//#define T_467



/*Szenario 4,5,6,7
0000 1111 0101 0101
0xAAF0
Freie Karten für die Spieler, die zu setzen sind.
ManualSet, das sind die Karten in nicht S und B
Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
*/
#ifdef T_4567
	#define F 5	
	#define Bank1 11
	#define Bank2 13
	#define Bank3 15
	#define Manual1 4
	#define Manual2 9
	#define SeqStart 10
#endif



/*Szenario 5,6,7
0000 0111 0001 0101
0xA8E0
Freie Karten für die Spieler, die zu setzen sind.
ManualSet, das sind die Karten in nicht S und B
Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
*/
#ifdef T_567
	#define F 8
	#define Bank1 13
	#define Bank2 15
	#define Bank3 13
	#define Manual1 5
	#define Manual2 11
#define SeqStart 12
#endif



/*0xA2D0 setzt die Bits der Bankkarte
zu setzenden Bits entsprechen; 4,6,7
0000 1011 0100 0101
in BigEndian
0xA2D0
Freie Karten für die Spieler, die zu setzen sind.
ManualSet, das sind die Karten in nicht S und B
Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
*/
#ifdef T_467
	#define F 6	
	#define Bank1 13
	#define Bank2 15
	#define Bank3 13
	#define Manual1 4
	#define Manual2 9
	#define SeqStart 10
#endif



//Sequenzlänge die wir berechnenen
#define NumCards 30

//Bank im besizt eines Ass?
#define Ass 1

//Messen von Effizienzwerten - 1 = true
#define MEASURE 1

//#define PATH "C:\\Users\\Jens\\Fuffi\\Informatikstudium\\Semester7 - WS1516\\Bachelorarbeit_BlackJack\\testing\\"
#define PATH ""

//struct
struct solution {
	uint8_t seq[NumCards];
	uint8_t stack[10];
};
