#include <iostream>
#include "MapLoader.h"
using namespace std;

void part_2::start()
{
	MapLoader mp;
	cout << "Testing valid map." << endl;;
	cout << mp.generateMap("./MapFiles/canada.map");
	cout << endl;
	
	/*cout << "Testing incorrect file exception" << endl;
	mp.generateMap("./MapFiles/InvalidFiles/invalidExt.exe");
	cout << endl;
	
	
	cout << "Testing missing element exception" << endl;
	mp.generateMap("./MapFiles/InvalidFiles/canadaNoConts.map");
	cout << endl;
	

	cout << "Testing disconnected map exception" << endl;
	mp.generateMap("./MapFiles/InvalidFiles/canadaDisconnected.map");
	cout << endl;

	cout << "Testing insertion operator." << endl;;
	mp.generateMap("./MapFiles/canada.map");
	cout << "Expected output:" << endl << "Loaded map is: canada" << endl << "Output:" << endl;
	cout << mp;
	cout << endl;*/

}

