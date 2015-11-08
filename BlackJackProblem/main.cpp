#include <iostream>
#include <string>
#include <sstream>

#include "SequenzCreator.h"
#include "FillUp.h"

using namespace std;

int main(int argv, char** argc) {
	

	int n = 2;
	for (int n = 2; n <= 9; n++) {
		SequenzCreator* SequenzCreate = new SequenzCreator(n);
		FillUp* SolutionCalc = new FillUp(SequenzCreate, n);
	}
	

	return 0;
}

