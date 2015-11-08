#include "SequenzCreator.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

SequenzCreator::SequenzCreator( int _n ) {
	n = _n;
	n_big = n + 10;

	numSolutions = 0;

	seq = tempsol + SeqStart;
	stack = tempsol + NumCards;
	for (int i = 0; i < 9; i++) {
		stack[i] = 4;
	}
	stack[9] = 16;

	string s = "C:\\Users\\Jens\\Fuffi\\Informatikstudium\\Semester7 - WS1516\\Bachelorarbeit_BlackJack\\SolutionSequenz";
	s += '0' + n;
	s += ".txt";
	myfile.open( s );

	
	setValue( 0, 0 );


	myfile.close();
}



int SequenzCreator::checkSequenz( int i, int confirmed ) {
	for (int k = confirmed; k <= i; k++) { //Teste für alle Startpunkte ab confirmed die Fole
		int sum = 0;
		for (int l = k; l <= i; l++) { //Teste Folge für spezifischen Startpunkt k
			sum += seq[l];
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
	//Jede Karte zuweisen
	if (i < NumCards-SeqStart) {
		//Falls 
		if (i == 3 || i == 5) {
			//Hier wird explizit ein Wert zugewiesen
			int j = 10 - n;
			if (stack[j] > 0) {
				stack[j]--;
				seq[i] = j;
				/**Check Sequnz**/
				int confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				}
				stack[j]++;
			}
		} else {
			//versch. Werte durchtesten
			for (int j = 2; j <= 10; j++) {
				if (stack[j-1] > 0) {
					//Wert setzen
					stack[j-1]--;
					seq[i] = j;

					/**Check Sequnz**/
					int confirmed = checkSequenz(i, _confirmed);

					if (confirmed != -1) {
						setValue(i + 1, confirmed);
					}
					stack[j-1]++;
				}
			}
		}
	} else {
		//Alle Karten erfolgreich belegt :-)
		if (numSolutions < SolSize) {
			char s[2*(NumCards-SeqStart)+1];
			for (int j = 0; j < 20; j++) {
				s[2 * j] = '0' + seq[j];
				s[2 * j + 1] = '\t';
				solutions[numSolutions][SeqStart+j] = seq[j];
			}
			s[39] = '\n';
			s[40] = '\0';
			myfile << s;
			for (int j = 0; j < 10; j++) {
				solutions[numSolutions][NumCards + j] = stack[1 + j];
			}

			numSolutions++;
		} else {
			string s = "Attention! More than 10000 Solutions found. SolNum: ";
			s += 0 + numSolutions;
			s += '\n';
			myfile << s;
			cout << s;
		}

	}
}

int* SequenzCreator::getSolution( int i) {
	return solutions[i];
}

int SequenzCreator::getAnzahlSol() {
	return numSolutions;
}