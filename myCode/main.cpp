// Standard (system) header files
#include <iostream>
#include <stdlib.h>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"
#include "SimpleUI.h"
#include "StudentDb.h"

// Main program
int main (void)
{
    // TODO: Add your program code here
	cout << "StudentDb started." << endl << endl;
	StudentDb db;
	SimpleUI ui(db);
	ui.run();
	return 0;
}
