#include "FillUp.h"
#include "SequenzCreator.h"

#include <iostream> 
#include <string>
using namespace std;
FillUp::FillUp( SequenzCreator* sC, int n ) {
	globsucces = 0;
	globfail = 0;

	for (int i = 0; i < 7; i++) {
		points[i] = 0;
		success[i] = 0;
	}

	string s = PATH;
	s += "SolutionFinal";
	s += '0' + n;
	s += ".txt";
	myfile.open( s + to_string(n) + ".txt" );
	
	int z = 1;
	//Alle Lösungen testen
	for (int i = 0; i < sC->getAnzahlSol(); i++) {
		//Progress-Output
		if (i / (double)sC->getAnzahlSol() > z / (double)10) {
			cout << z << "0%, done!" << endl;
			z++;
		}

		//PointerStruktur
		sol = sC->getSolution(i);
		
		//Zu setzende Bankstartkarten
		if (sol->stack[0] > 0 && sol->stack[11 - n - 2] > 0) {
			sol->stack[0]--;
			sol->stack[11 - n - 2]--;

			sol->seq[9] = 1;
			sol->seq[4] = 10 - n;
			nextnum();

			sol->seq[4] = 1;
			sol->seq[9] = 10 - n;
			nextnum();
		}

		//Zu setzende Spielerkarten
		tocards[0] = &sol->seq[0];
		tocards[1] = &sol->seq[1];
		tocards[2] = &sol->seq[2];
		tocards[3] = &sol->seq[3];
		tocards[4] = &sol->seq[5];
		tocards[5] = &sol->seq[8];
		

	}
	
	cout << "Finished mit "<< n << " -- " << globsucces << " Loesungen gefunden -- " << globfail << " gescheitert!" << endl;
	myfile << "Finished -- " << globsucces << " Loesungen gefunden -- " << globfail << " gescheitert!" << endl;
	myfile << "Erfolgsquote bei " << globsucces / (double)(globsucces + globfail) << endl;
	for (int i = 0; i < 7; i++) {
		myfile << "Für " << i+1 << " Spieler: " << success[i] << "Lösungen gefunden" << endl;
	}
	myfile.close();
}

void FillUp::nextnum(int num ) {
	//Setzen der 6 freien Variablen
	if (num < 6) {
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

		if (checkNumPlayer(4) && checkNumPlayer(6) && checkNumPlayer(7)) {
			globsucces++;
			
			char s[61];
			for (int j = 0; j < 30; j++) {
				s[2 * j] = '0' + sol->seq[j];
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
	/**Es reicht aus auf nur ein Ass zu testen
	Bei mehreren kann nur ein Ass als Zehner wirken
	**/
	bool ass = false;

	int start = anzspieler * 2 + 2;
	int latestplay = start;

	for (int i = 0; i < anzspieler; i++) {//Jeden Spieler testen
		//Hat der Spieler ein Ass auf der Starthand?
		if (sol->seq[i] == 1 || sol->seq[(anzspieler + 1) + i] == 1) {
			ass = true;
		}
		points[i] = sol->seq[i] + sol->seq[(anzspieler + 1) + i];

		int l;
		for (int j = start; j <= latestplay; j++) {	//Jeden Einstiegspunkt durchlaufen
			//Test auf 21			
			int k = points[i];
			l = 0;
			while ( k < 21 && j+l < NumCards ) {
				if (ass && k == 11) {
					return false; //Falls Ass im Deck und 11 erreicht werden kann
				}
				if (sol->seq[j + l] == 1) {
					ass = true;
				}
				k += sol->seq[j + l];
				l++;
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