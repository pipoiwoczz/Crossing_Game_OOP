#ifndef CASSET_H
#define CASSET_H
#include "setup.h"

class cAnimal;
class cVehicle;

class cAsset {
private:

public:
	cAsset();
	friend cAnimal;
	friend cVehicle;
};
#endif