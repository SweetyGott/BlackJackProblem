#pragma once


//Sequenzlänge die wir berechnenen
#define NumCards 30

//Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
#define SeqStart 12

//Bank im besizt eines Ass?
#define Ass 1



/*Szenario 4,5,6,7
0000 1111 0101 0101
0xAAF0
Manuell zu setzende Werte
0000 1000 0100
0x210*/
//#define STARTWERT_MASK 0xAAF0
//#define MANUAL_MASK 0x210

//Freie Karten für die Spieler, die zu setzen sind.
//#define F 5		//Szenario 4,5,6,7



/*Szenario 5,6,7
0000 0111 0001 0101
0xA710
Manuell zu setzende Werte
0000 0100 0001
0x140*/
#define STARTWERT_MASK 0xA710
#define MANUAL_MASK 0x140

//Freie Karten für die Spieler, die zu setzen sind.
#define F 8		//Szenario 5,6,7



/*0xA2D0 setzt die Bits der Bankkarte
zu setzenden Bits entsprechen; 4,6,7
0000 1011 0100 0101
in BigEndian
0xA2D0
Die manuell zu setzende Werte
0000 1000 0100*/
//#define STARTWERT_MASK 0xA2D0
//#define MANUAL_MASK 0x210

//Freie Karten für die Spieler, die zu setzen sind.
//#define F 6		//Szenario 4,6,7


//Messen von Effizienzwerten - 1 = true
#define MEASURE 1


//#define PATH "C:\\Users\\Jens\\Fuffi\\Informatikstudium\\Semester7 - WS1516\\Bachelorarbeit_BlackJack\\testing\\"
#define PATH ""


//struct
struct solution {
	int seq[NumCards];
	int stack[10];
};
