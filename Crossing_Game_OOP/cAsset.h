#ifndef CASSET_H
#define CASSET_H
#include "setup.h"
class cAnimal;
class cVehicle;

class cAsset {
private:
	vector<vector<unsigned char>> textureLion;
	vector<vector<unsigned char>> textureRhino;
	vector<vector<unsigned char>> textureCrocodile;
public:
	cAsset();
	friend cAnimal;
	friend cVehicle;
};
#endif