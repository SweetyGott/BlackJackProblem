#include <iostream>
#include <string>
#include <sstream>

#include "SequenzCreator.h"
#include "FillUp.h"

using namespace std;

int main(int argc, char** argv) {
	int n = 2;	//Sequenzen, dass immer Wert 2 bzw. evtl. 12 erreicht wird
	int e = 9;	//Sequenzen, dass immer Wert 9 bzw. evtl. 19 erreicht wird
	//Es wird durch alle Möglichkeiten in diesem Rahmen iteriert.
	for (int i = n; i <= e; i++) {
		SequenzCreator* SequenzCreate = new SequenzCreator(i);
		FillUp* SolutionCalc = new FillUp(SequenzCreate, i);
		delete SequenzCreate;
		delete SolutionCalc;
	}
	

	return 0;
}

