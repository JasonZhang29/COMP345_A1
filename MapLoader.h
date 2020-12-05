#ifndef MapLoader_H
#define MapLoader_H
#include "Map.h"
#include <iostream>
using namespace std;

class MapLoader {
public:
	MapLoader();
	~MapLoader();
	Map* readMap(string mapFile);
};

class conquestFile {
private:
	vector<Continent*> continents;
	vector<Territory*> territories;
public:
	conquestFile();
	conquestFile(conquestFile* conFile);
	~conquestFile();
	vector<Continent*> getContinents();
	vector<Territory*> getTerritories();
	void addContinent(Continent* continent);
	void addTerritory(Territory* territory);
	void print();
	bool isConnectedGraph();
	bool validate();
};

class ConquestFileReader {
public:
	ConquestFileReader();
	~ConquestFileReader();
	Map* readConquestFile(string conquestFile);
};

class ConquestFileReaderAdapter : public MapLoader {
private:
	ConquestFileReader con;
public:
	ConquestFileReaderAdapter(ConquestFileReader cfreader);
};

#endif //MapLoader_H
