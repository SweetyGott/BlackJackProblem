#pragma once


//Sequenzlänge die wir berechnenen
#define NumCards 30

//Punkt ab dem die Sequenzfolge zum einsteigen berechnet wird
#define SeqStart 10

//Bank im besizt eines Ass?
#define Ass 1

//NOT needed
#define N_c 3
#define n1_c 4
#define n2_c 6
#define n3_c 7

//zu setzenden Bits entsprechen
//0001 0111 0100 0101
//in BigEndian
//0xA2D0
//Die manuell zu setzende Werte
//0000 1000 0100


//0xA2D0 setzt die Bits der Bankkarte
#define STARTWERT_MASK 0xA2D0
#define MANUAL_MASK 0x210

#define PATH "C:\\Users\\Jens\\Fuffi\\Informatikstudium\\Semester7 - WS1516\\Bachelorarbeit_BlackJack\\testing\\"
//define PATH "result\\"


//struct
struct solution {
	int seq[NumCards];
	int stack[10];
};

//Messen von Effizienzwerten
#define MEASURE 1