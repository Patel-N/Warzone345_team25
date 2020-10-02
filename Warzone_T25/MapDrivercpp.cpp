
#include <iostream>
#include"Map.h";
using namespace std;


namespace test {
	void main() {
		Map map("created map");
		map.addTerritory(1, "Brazil");
		map.addTerritory(2, "Canada");
		map.addTerritory(3, "France");
		map.addTerritory(6, "Cuba");
		map.printMap();
		char c;
		cin >> c;
	}
}