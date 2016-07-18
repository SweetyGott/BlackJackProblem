#include "Config.h"
#include "SequenzCreator.h"

#include <string>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

SequenzCreator::SequenzCreator( uint8_t _n ) {
	//Sequenz mit 2 folgenden Werten oder nur einem 
#if Ass == 0	
		n = _n;
		n_big = _n;
#else
		n = _n;
		n_big = _n + 10;
#endif
	
		//Werte der Bank
	j2 = 1;
	j1 = 21 - n_big - j2;

	numSolutions = 0;

	//Measurement
	gesamtTest = 0;
	for (uint8_t i = 0; i < NumCards - SeqStart + 1; i++) {
		tiefe[i] = 0;
	}


	//Setzen der verblibenden karten
	//Indexshift um -1
	for (uint8_t i = 0; i < 9; i++) {
		temp_sol.stack[i] = 4;
	}
	temp_sol.stack[9] = 16;

	//Outputfile der Sequenzen vorbereiten
	numData = 0;
	s = PATH;
	s += "SolutionSequenz";
	se = ".txt";
	myfile.open( s + to_string(n) + "-" + to_string(numData) + se );

	//Setzen der Werte
	setValue( SeqStart, SeqStart );
	cout << "Sequenzen fertig mit " << to_string(n) << " -- " << numSolutions << " Sequenzen gefunden!" << endl;
	myfile << "Sequenzen fertig -- " << numSolutions << "  Sequenzen gefunden!" << endl;
	uint64_t temp = 0;
	for (uint8_t i = 0; i < NumCards - SeqStart; i++) {
		myfile << "In Tiefe " << i << ":\t" << tiefe[i] << " mal abgebrochen" << endl;
		temp += tiefe[i]*i;
	}
	myfile << "In Tiefe " << NumCards - SeqStart << ":\t" << tiefe[NumCards - SeqStart] << " Lösungen gefunden" << endl;
	temp += tiefe[NumCards - SeqStart]*(NumCards - SeqStart);
	myfile << "Durchschnittliche Tiefe: " << temp / (double)gesamtTest << endl;

	myfile.close();

	
}

//i ist die aktuelle Karte
/*confirmed is kleiner als i und die karte
bei der als nächste die Gültiigkeit der Sequenz überprüft werden muss.
Der Rest davor wurde bereits bestätigt*/
inline int SequenzCreator::checkSequenz(uint8_t i, uint8_t confirmed ) {
	for (uint8_t k = confirmed; k <= i; k++) { //Teste für alle Startpunkte ab confirmed die Fole
		uint8_t sum = 0;
		for (uint8_t l = k; l <= i; l++) { //Teste Folge für spezifischen Startpunkt k
			sum += temp_sol.seq[l];
			//Falls die bank in der Startbelegung gar kein Ass hat
#if Ass == 0
			if (n > 10 && temp_sol.seq[l] == 1) {
				n -= 10;
			}
#endif
			if (sum == n || sum == n_big) {
				//belegung passt
				if (k == confirmed) {
					confirmed++;
				}
				break;
			} else if (sum >= n_big) {
				//diese Belegung passt nicht, gehe zur nächsten Belegung
				return -1;
			}
		}
	}
	//Belegung passt für alle Fälle, gib de Fortschritt zurück
	return confirmed;
}



void SequenzCreator::setValue(const uint8_t i, const uint8_t _confirmed) {
	//Jede Karte einen Wert Zuweisen
	if (i < NumCards) {
		//Vordefinierte Werte, die gesetzt werden
		if ( i == Bank1 || i == Bank2 || i ==  Bank3 ) {
			//In der Folge wird immer der Wert n_big erreicht, als Startwert braucht somit die Bank immer 
			//21-n_big Punkte verteilt auf einmal Ass(1) und einmal (21-n_big-1) Punkte
			uint8_t p2 = i;
			uint8_t p1 = (i - 1) / 2;
			

			if (temp_sol.stack[j2-1] > 0 && temp_sol.stack[j1 - 1] > 0 ) {
				temp_sol.stack[j2 - 1]--;
				temp_sol.stack[j1 - 1]--;

				int confirmed;
#if SECOND_ASS != 1
				//Zwei Startwerte setzen
				temp_sol.seq[p1] = j2;
				temp_sol.seq[p2] = j1;
				//**CHECK/
				confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				}
#if MEASURE == 1
				else {
					tiefe[i - SeqStart]++;
					gesamtTest++;
				}
#endif
#endif
				//Umgekehrt testen
				temp_sol.seq[p1] = j1;
				temp_sol.seq[p2] = j2;
				/**CHECK**/
				confirmed = checkSequenz(i, _confirmed);
				if (confirmed != -1) {
					setValue(i + 1, confirmed);
				} 
#if MEASURE == 1
				else {
					tiefe[i - SeqStart]++;
					gesamtTest++;
				}
#endif
				temp_sol.stack[j2 - 1]++;
				temp_sol.stack[j1 - 1]++;
			}
		} else {
			//versch. Werte durchtesten
			for (int j = 1; j <= 10; j++) {
				if (temp_sol.stack[j-1] > 0) {
					//Wert setzen
					temp_sol.stack[j-1]--;
					temp_sol.seq[i] = j;

					/**Check Sequnz**/
					int confirmed = checkSequenz(i, _confirmed);

					if (confirmed != -1) {
						setValue(i + 1, confirmed);
					} 
#if MEASURE == 1
					else {
						tiefe[i - SeqStart]++;
						gesamtTest++;
					}
#endif
					temp_sol.stack[j-1]++;
				}
			}
		}
	} else {
		tiefe[NumCards - SeqStart]++;
		gesamtTest++;
		//Alle Karten in der Sequenz belegt
		//Zur Vermeidung einer großen Datei werden viele kleine Dateien angelegt
		if ((numSolutions + 1) % 500000 == 0) {
			myfile.close();
			numData++;
			myfile.open(s + to_string(n) + "-" + to_string(numData) + se);
		}

		//Generate String
		char s[2*NumCards + 1];
		for (uint8_t j = 0; j < NumCards; j++) {
			s[2 * j] = '0' + temp_sol.seq[j];
			s[2 * j + 1] = '\t';
		}
		s[2*NumCards-1] = '\n';
		s[2*NumCards] = '\0';
		myfile << s;

		//Write to SolutionVector
		if(sol.size() <= sol.max_size()) {
			sol.push_back(temp_sol);
			numSolutions++;
		}
		else {
			cout << "maximale Anzahl an Lösunge gefunden, Speicherproblem" << endl;
			myfile << "maximale Anzahl an Lösunge gefunden, Speicherproblem" << endl;
		}
	}
}

solution* SequenzCreator::getSolution( uint64_t i ) {
	return &sol[(unsigned)i];
}


uint64_t SequenzCreator::getAnzahlSol() {
	if (numSolutions != sol.size()) {
		cout << "größenFehler in Sequenzcreator getAnzahl sol" << endl;
	}
	return sol.size();
}