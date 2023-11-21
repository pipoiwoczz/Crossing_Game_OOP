#include "cVehicle.h"

vector<Texture> cTruck::textureTruck = cAsset::assetLoaders(truckFile);
vector<Texture> cHelicopter::textureHeli = cAsset::assetLoaders(heliFile);
vector<Texture> cMotorbike::textureMotorb = cAsset::assetLoaders(motorbFile);

cTruck::cTruck() : cTruck({ 0, 40 }, 2) {};
cTruck::cTruck(COORD In_pos, /*int difficulty, int ttm*/ int speed): cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	pTexture = &cTruck::textureTruck[0];
	pLTexture = pTexture;
	currentFrame = 0;
	nFrame = textureTruck.size();
}

cHelicopter::cHelicopter() : cHelicopter({ 0, 40 }, 2) {};
cHelicopter::cHelicopter(COORD In_pos, /*int difficulty, int ttm*/ int speed): cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	pTexture = &cHelicopter::textureHeli[0];
	pLTexture = pTexture;
	currentFrame = 0;
	nFrame = textureHeli.size();
}

cMotorbike::cMotorbike() : cMotorbike({ 0, 40 }, 2) {};
cMotorbike::cMotorbike(COORD In_pos, /*int difficulty, int ttm*/ int speed): cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	pTexture = &cMotorbike::textureMotorb[0];
	pLTexture = pTexture;
	currentFrame = 0;
	nFrame = textureMotorb.size();
}

cObstacle* cTruck::bootstrapObjectcTruck = cObstacle::addObject(new cTruck());
cObstacle* cHelicopter::bootstrapObjectcHelicopter = cObstacle::addObject(new cHelicopter());
cObstacle* cMotorbike::bootstrapObjectcMotorbike = cObstacle::addObject(new cMotorbike());