#include "FillUp.h"
#include "SequenzCreator.h"

#include <iostream> 
#include <string>
using namespace std;
FillUp::FillUp( SequenzCreator* sC, uint8_t n ) {
	//Erfolg-Niederlage
	globsucces = 0;
	globfail = 0;

	//Startpunkte der Spieler
	for (uint8_t i = 0; i < 7; i++) {
		points[i] = 0;
		success[i] = 0;
	}

	string s = PATH;
	s += "SolutionFinal";
	myfile.open( s + to_string(n) + ".txt" );
	
	uint8_t z = 1;
	//Alle Lösungen testen
	for (uint64_t i = 0; i < sC->getAnzahlSol(); i++) {
		//Progress-Output
		if (i / (double)sC->getAnzahlSol() > z / (double)10) {
			cout << (int)z << "0%, done!" << endl;
			z++;
		}

		//Zu setzende Spielerkarten bei 4,5,6,7
#ifdef T_4567
		tocards[0] = &sol->seq[0];
		tocards[1] = &sol->seq[1];
		tocards[2] = &sol->seq[2];
		tocards[3] = &sol->seq[3];
		tocards[4] = &sol->seq[8];
#endif
		//Zu setzende Spielerkarten bei 5,6,7
#ifdef T_567
		tocards[0] = &sol->seq[0];
		tocards[1] = &sol->seq[1];
		tocards[2] = &sol->seq[2];
		tocards[3] = &sol->seq[3];
		tocards[4] = &sol->seq[4];
		tocards[5] = &sol->seq[8];
		tocards[6] = &sol->seq[9];
		tocards[7] = &sol->seq[10];
#endif
		//Zu setzende Spielerkarten bei 4,6,7
#ifdef T_467
		tocards[0] = &sol->seq[0];
		tocards[1] = &sol->seq[1];
		tocards[2] = &sol->seq[2];
		tocards[3] = &sol->seq[3];
		tocards[4] = &sol->seq[5];
		tocards[5] = &sol->seq[8];
#endif

		//PointerStruktur
		sol = sC->getSolution(i);
		
		//Zu setzende Bankstartkarten
		if (sol->stack[0] > 0 && sol->stack[11 - n - 2] > 0) {
			sol->stack[0]--;
			sol->stack[11 - n - 2]--;

			sol->seq[Manual1] = 1;
			sol->seq[Manual2] = 10 - n;
			nextnum();

			sol->seq[Manual2] = 1;
			sol->seq[Manual1] = 10 - n;
			nextnum();
		}

		
		

	}
	
	cout << "Finished mit "<< n << " -- " << globsucces << " Loesungen gefunden -- " << globfail << " gescheitert!" << endl;
	myfile << "Finished -- " << globsucces << " Loesungen gefunden -- " << globfail << " gescheitert!" << endl;
	myfile << "Erfolgsquote bei " << globsucces / (double)(globsucces + globfail) << endl;
	for (int i = 0; i < 7; i++) {
		myfile << "Für " << (int)(i+1) << " Spieler: " << success[i] << "Lösungen gefunden" << endl;
	}
	myfile.close();
}

void FillUp::nextnum(uint8_t num ) {
	//Setzen der F freien Variablen
	if (num < F) {
		for (int i = 1; i <= 10; i++) {
			if (sol->stack[i - 1] > 0) {
				*tocards[num] = i;
				sol->stack[i - 1]--;
				nextnum(num + 1);
				sol->stack[i - 1]++;
			}
		}
	}
	//Teste die Möglichkeit
	else {
		if ( 
			#ifdef T_4567
						checkNumPlayer(4) && checkNumPlayer(5) && checkNumPlayer(6) && checkNumPlayer(7)
			#endif
			#ifdef T_567
						checkNumPlayer(5) && checkNumPlayer(6) && checkNumPlayer(7)
			#endif
			#ifdef T_467
						checkNumPlayer(4) && checkNumPlayer(6) && checkNumPlayer(7)
			#endif	
		) {
			globsucces++;
			
			char s[2*NumCards-1];
			for (int j = 0; j < 30; j++) {
				s[2 * j] = '0' + sol->seq[j];
				s[2 * j + 1] = '\t';
			}
			s[NumCards*2-1] = '\n';
			s[NumCards*2] = '\0';
			myfile << s;
		}
		else {
			globfail++;
		}
	}
}

// arg Anzahl Spieler: Anzahl der SPieler gegen die Bank
inline bool FillUp::checkNumPlayer(uint8_t anzspieler) {
	bool ass;
	int start = anzspieler * 2 + 2;
	int latestplay = start;

	for (int i = 0; i < anzspieler; i++) {//Jeden Spieler testen
		//Hat der Spieler ein Ass auf der Starthand?
		if (sol->seq[i] == 1 || sol->seq[(anzspieler + 1) + i] == 1) {
			ass = true;
		}
		else {
			ass = false;
		}
		points[i] = sol->seq[i] + sol->seq[(anzspieler + 1) + i];

		int l;
		for (uint8_t j = start; j <= latestplay; j++) {	//Jeden Einstiegspunkt durchlaufen
			//Test auf 21			
			uint8_t k = points[i];
			l = 0;
			while ( k < 21 && j+l < NumCards ) {
				//Neue Karte ein Ass?
				if (sol->seq[j + l] == 1) {
					ass = true;
				}
				//Karte zuweisen
				k += sol->seq[j + l];
				l++;
				//Test
				if (ass && k == 11) {
					return false; //Falls Ass im Deck und 11 erreicht werden kann
				}
			} 
			if (k == 21) {
				return false;
			}
		}
		latestplay += l;
	}

	success[anzspieler - 1]++;
	return true;
}