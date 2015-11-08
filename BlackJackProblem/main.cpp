#include <iostream>
#include <string>
#include <sstream>

#include "SequenzCreator.h"
#include "FillUp.h"

using namespace std;

int main(int argc, char** argv) {
	int start = 2;
	int end = 9;
	if (argc > 2) {
		start = atoi(argv[1]);
		end = atoi(argv[2]);
		if (start > end || start < 2 || start > 9 || end < 2 || end > 9) {
			cout << "Error. Wrong Input!" << endl;
			return -3;
		}
	}



	int n = 2;
	for (int n = start; n <= end; n++) {
		SequenzCreator* SequenzCreate = new SequenzCreator(n);
		FillUp* SolutionCalc = new FillUp(SequenzCreate, n);
	}
	

	return 0;
}

