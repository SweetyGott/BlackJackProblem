#pragma once

#define T_467

/*Szenario 4,5,6,7
0000 1111 0101 0101
0xAAF0
Freie Karten für die Spieler, die zu setzen sind.
ManualSet, das sind die Karten in nicht S und B
Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
*/
#ifdef T_4567

	#define F 5		//Szenario 4,5,6,7
	#define STARTWERT_MASK 0xAAF0
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
	#define F 8		//Szenario 5,6,7
	#define STARTWERT_MASK 0xA8E0
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
	#define F 6		//Szenario 4,6,7
	#define STARTWERT_MASK 0xA2D0
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
	int seq[NumCards];
	int stack[10];
};
