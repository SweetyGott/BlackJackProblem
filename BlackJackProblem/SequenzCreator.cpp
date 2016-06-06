#include "Config.h"
#include "SequenzCreator.h"

#include <string>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

SequenzCreator::SequenzCreator( int _n ) {
	//Sequenz mit 2 folgenden Werten oder nur einem 
	n = _n;
	n_big = n + Ass*10;

	numSolutions = 0;

	//seq = tempsol + SeqStart;
	//stack = tempsol + NumCards;
	

	//Setzen der verblibenden karten
	//Indexshift um -1
	for (int i = 0; i < 9; i++) {
		temp_sol.stack[i] = 4;
	}
	temp_sol.stack[9] = 16;

	set_mask = (0);

	startwert_mask = (STARTWERT_MASK);
	manual_mask = (MANUAL_MASK);

	//Outputfile der Sequenzen vorbereiten
	string s = PATH;
	s += "SolutionSequenz";
	s += '0' + n;
	s += ".txt";
	myfile.open( s );

	//Setzen der Werte
	setValue( SeqStart, SeqStart );

	myfile.close();

	cout << "Sequenzen fertig mit " << n << " -- " << numSolutions << " Sequenzen gefunden!" << endl;
	myfile << "Sequenzen fertig -- " << numSolutions << "  Sequenzen gefunden!" << endl;
}



int SequenzCreator::checkSequenz( int i, int confirmed ) {
	for (int k = confirmed; k <= i; k++) { //Teste für alle Startpunkte ab confirmed die Fole
		int sum = 0;
		for (int l = k; l <= i; l++) { //Teste Folge für spezifischen Startpunkt k
			sum += temp_sol.seq[l];
			if (sum == n || sum == n_big) {
				//belegung passt
				if (k == confirmed) {
					confirmed++;
				}
				break;
			}
			else if (sum >= n_big) {
				//diese Belegung passt nicht, gehe zur nächsten Belegung
				return -1;
			}
		}
	}
	//Belegung passt für alle Fälle, gib de Fortschritt zurück
	return confirmed;
}



void SequenzCreator::setValue(const int i, const int _confirmed) {
	//Jede Karte einen Wert Zuweisen
	if (i < NumCards) {
		//Vordefinierte Werte, die gesetzt werden
		if (/*i == 3 || i == 5*/ startwert_mask[i]  && !set_mask[i] ) {
			//In der Folge wird immer der Wert n_big erreicht, als Startwert braucht somit die Bank immer 
			//21-n_big Punkte verteilt auf einmal Ass(1) und einmal (21-n_big-1) Punkte
			short p2 = i;
			short p1 = (i - 1) / 2;
			int j = 21 - n_big - 1;

			if (temp_sol.stack[1-1] > 0 && temp_sol.stack[j - 1] > 0 ) {
				temp_sol.stack[1 - 1]--;
				temp_sol.stack[j - 1]--;
				set_mask[p1] = true;
				set_mask[p2] = true;

				//Zwei Startwerte setzen
				temp_sol.seq[p1] = 1;
				temp_sol.seq[p2] = j;
				/**CHECK**/
				int confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				}
				//Umgekehrt testen
				temp_sol.seq[p1] = j;
				temp_sol.seq[p2] = 1;
				/**CHECK**/
				confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				}

				set_mask[p1] = false;
				set_mask[p2] = false;
				temp_sol.stack[1 - 1]++;
				temp_sol.stack[j - 1]++;
			}
		} else {
			//versch. Werte durchtesten
			for (int j = 2; j <= 10; j++) {
				if (temp_sol.stack[j-1] > 0) {
					//Wert setzen
					temp_sol.stack[j-1]--;
					temp_sol.seq[i] = j;

					/**Check Sequnz**/
					int confirmed = checkSequenz(i, _confirmed);

					if (confirmed != -1) {
						setValue(i + 1, confirmed);
					}
					temp_sol.stack[j-1]++;
				}
			}
		}
	} else {
		//Alle Karten in der Sequenz belegt
		//Write to File
		char s[2*NumCards + 1];
		for (int j = 0; j < NumCards; j++) {
			s[2 * j] = '0' + temp_sol.seq[j];
			s[2 * j + 1] = '\t';
		}
		s[2*NumCards-1] = '\n';
		s[2*NumCards] = '\0';
		myfile << s;

		//Write to SolutionVector
		sol.push_back(temp_sol);
		
		numSolutions++;
		

	}
}

solution* SequenzCreator::getSolution( int i ) {
	return &sol[i];
}


int SequenzCreator::getAnzahlSol() {
	return numSolutions;
}