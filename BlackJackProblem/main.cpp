#include <iostream>
#include <string>
#include <sstream>

#include "SequenzCreator.h"
#include "FillUp.h"

using namespace std;

int main(int argc, char** argv) {
	int n = 4;
	int e = 9;
	for (int i = n; i <= e; i++) {
		SequenzCreator* SequenzCreate = new SequenzCreator(i);
		FillUp* SolutionCalc = new FillUp(SequenzCreate, i);
		delete SequenzCreate;
		delete SolutionCalc;
	}
	

	return 0;
}

