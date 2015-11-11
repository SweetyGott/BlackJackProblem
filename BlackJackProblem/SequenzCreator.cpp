#include "SequenzCreator.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

SequenzCreator::SequenzCreator( int _n ) {
	n = _n;
	n_big = n + 10;

	switch (n)
	{
	case 2: SolutionSpace = 10000; break;
	case 3:	SolutionSpace = 1000000; break;
	case 4:	SolutionSpace = 5000000; break;
	case 5:	SolutionSpace = 900000; break;
	case 6:	SolutionSpace = 3500000; break;
	case 7:	SolutionSpace = 70000000; break;
	case 8:	SolutionSpace = 70000000; break;
	case 9:	SolutionSpace = 1000; break;
	default:	SolutionSpace = 1; break;
	}
	solutions = new int[SolutionSpace][NumCards + 10];;

	numSolutions = 0;

	seq = tempsol + SeqStart;
	stack = tempsol + NumCards;
	for (int i = 0; i < 9; i++) {
		stack[i] = 4;
	}
	stack[9] = 16;
	//Die beiden Karten, die wir im Fillup verwenden, aber schon bekannt sind
	stack[0]--;
	stack[10 - n - 1]--;

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
		//Falls Einer der 3 zu setzenden
		if ( /*i == 1 ||*/ i == 3 || i == 5) {
			//Hier wird explizit ein Wert zugewiesen 
			int j = 10 - n;
			if (stack[j-1] > 0 && stack[0] > 0) {
				stack[j-1]--;
				stack[0]--;
				//1
				seq[i] = j;
				tempsol[5 + (i - 1) / 2] = 1;
				/**Check Sequnz**/
				int confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				}
				//2
				seq[i] = 1;
				tempsol[5 + (i - 1) / 2] = j;
					/**Check Sequnz**/
				confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				}

				stack[j-1]++;
				stack[0]++;
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
		if (numSolutions < SolutionSpace) {
			char s[2*(NumCards-SeqStart)+1];
			for (int j = 0; j < 20; j++) {
				s[2 * j] = '0' + seq[j];
				s[2 * j + 1] = '\t';
			}
			s[39] = '\n';
			s[40] = '\0';
			myfile << s;

			for (int j = 0; j < NumCards + 10; j++) {
				solutions[numSolutions][j] = tempsol[j];
			}

			numSolutions++;
		} else {
			string s = "Attention! More than x Solutions found. SolNum: ";
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