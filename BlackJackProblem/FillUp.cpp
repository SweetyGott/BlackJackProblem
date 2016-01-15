#include "FillUp.h"
#include "SequenzCreator.h"

#include <iostream> 
#include <string>
using namespace std;
FillUp::FillUp( SequenzCreator* sC, int n ) {
	globsucces = 0;
	globfail = 0;

	string s = "C:\\Users\\Jens\\Fuffi\\Informatikstudium\\Semester7 - WS1516\\Bachelorarbeit_BlackJack\\SolutionFinal";
	s += '0' + n;
	s += ".txt";
	myfile.open( s );
	
	int z = 1;
	cout << "0%, done! Startinth with: " << n << " ....." << endl;
	//Alle Lösungen testen
	for (int i = 0; i < sC->getAnzahlSol(); i++) {
		//Progress-Output
		if (i / (double)sC->getAnzahlSol() > z / (double)10) {
			cout << z << "0%, done!" << endl;
			z++;
		}

		//PointerStruktur
		cards = sC->getSolution(i);
		stack = cards + NumCards;
		//Verweise auf die 6 zu setzende Karten
		tocards[0] = &cards[0];
		tocards[1] = &cards[1];
		tocards[2] = &cards[2];
		tocards[3] = &cards[3];
		tocards[4] = &cards[5];
		tocards[5] = &cards[8];

		//Die beiden Orangen setzen
		//stack[0]--;//Zu beginn ein Ass weniger ;-)
		//stack[10 - n - 1]--;
		//1
		cards[4] = 1;
		cards[9] = 10 - n;
		nextnum();
		//2
		cards[9] = 1;
		cards[4] = 10 - n;
		nextnum();
	}
	
	cout << "Finished mit "<< n << " -- " << globsucces << " Loesungen gefunden -- " << globfail << " gescheitert!" << endl;
	myfile << "Finished -- " << globsucces << " Loesungen gefunden -- " << globfail << " gescheitert!" << endl;
	myfile.close();
}

void FillUp::nextnum(int num ) {
	//Setzen der 6 freien Variablen
	if (num < NumFillUpCards) {
		for (int i = 2; i <= 10; i++) {
			if (stack[i - 1] > 0) {
				*tocards[num] = i;
				stack[i - 1]--;
				nextnum(num + 1);
				stack[i - 1]++;
			}
		}
	}
	//Teste die Möglichkeit
	else {

		if (checkNumPlayer(4) /*&& checkNumPlayer(5)*/ && checkNumPlayer(6) && checkNumPlayer(7)) {
			globsucces++;
			
			char s[61];
			for (int j = 0; j < 30; j++) {
				s[2 * j] = '0' + cards[j];
				s[2 * j + 1] = '\t';
			}
			s[59] = '\n';
			s[60] = '\0';
			myfile << s;
		}
		else {
			globfail++;
		}
	}
}

// arg Anzahl Spieler: Anzahl der SPieler gegen die Bank
bool FillUp::checkNumPlayer(int anzspieler) {

	int start = anzspieler * 2 + 2;
	int latestplay = start;

	for (int i = 0; i < anzspieler; i++) {//Jeden Spieler testen
		/**Es reicht aus auf nur ein Ass zu testen
		Bei mehreren kann nur ein Ass als Zehner wirken
		**/
		bool ass = false;
		if (cards[i] == 1 || cards[(anzspieler + 1) + i] == 1) {
			ass = true;
		}
		points[i] = cards[i] + cards[(anzspieler + 1) + i];

		int l;
		for (int j = start; j <= latestplay; j++) {	//Jeden Einstiegspunkt durchlaufen
			//Test auf 21			-- Strenger Möglich mit dem Test auf 11 beim Ass, erstmal vernachlaessigt
			int k = points[i];
			l = 0;
			while ( k < 21 && j+l < NumCards ) {
				if (ass && k == 11) {
					return false; //Falls Ass im Deck und 11 erreicht werden kann
				}
				if (cards[j + l] == 1) {
					ass = true;
				}
				k += cards[j + l];
				l++;
			} 
			if (k == 21) {
				return false;
			}
		}
		latestplay += l;
	}

	return true;
}