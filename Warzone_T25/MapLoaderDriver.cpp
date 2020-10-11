#include <iostream>
#include "MapLoader.h"

int main()
{
	MapLoader mp;

	cout << "Testing valid map." << endl;;
	mp.generateMap("./MapFiles/canada.map");
	cout << endl;

	cout << "Testing incorrect file exception" << endl;
	mp.generateMap("./MapFiles/InvalidFiles/invalidExt.exe");
	cout << endl;

	cout << "Testing missing element exception" << endl;
	mp.generateMap("./MapFiles/InvalidFiles/canadaNoConts.map");
	cout << endl;

	/*
	Find working invalid file with Mohamed
	*/
	//cout << "Testing disconnected map exception" << endl;
	//mp.generateMap("./MapFiles/InvalidFiles/canadaDisconnected.map");
	//cout << endl;

	cout << "Testing insertion operator." << endl;;
	mp.generateMap("./MapFiles/canada.map");
	cout << "Expected output:" << endl << "Loaded map is: canada" << endl << "Output:" << endl;
	cout << mp;
	cout << endl;


}

