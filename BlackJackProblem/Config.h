#pragma once


//Sequenzlänge die wir berechnenen
#define NumCards 30

//Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
#define SeqStart 10

//Bank im besizt eines Ass?
#define Ass 1

//0xA2D0 setzt die Bits der Bankkarte
#define STARTWERT_MASK 0xA2D0
#define MANUAL_MASK 0x210

#define PATH "C:\\Users\\Jens\\Fuffi\\Informatikstudium\\Semester7 - WS1516\\Bachelorarbeit_BlackJack\\testing\\"


//struct
struct solution {
	int seq[NumCards];
	int stack[10];
};
