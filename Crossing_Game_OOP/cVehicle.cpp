#include "cVehicle.h"
#include "cAsset.h"
vector<Texture> cTruck::textureTruck = cAsset::assetLoaders(truckFile);
vector<Texture> cHelicopter::textureHeli = cAsset::assetLoaders(heliFile);
vector<Texture> cMotorbike::textureMotorb = cAsset::assetLoaders(motorbFile);



cVehicle::cVehicle(COORD In_pos, int speed) : cObstacle(In_pos, speed)
{
}

cTruck::cTruck() : cTruck({ 0, 40 }, 2) {};
cTruck::cTruck(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	pTexture = &cTruck::textureTruck[0];
	pLTexture = pTexture;
	currentFrame = 0;
	nFrame = textureTruck.size();
}

cTruck::~cTruck()
{
	delete bootstrapObjectcTruck;
}

char cTruck::getType()
{
	return 'T';
}

cObstacle* cTruck::copy(COORD pos)
{
	cTruck* obj = new cTruck(*this);
	obj->topleft = pos;
	return obj;
}
cObstacle* cTruck::construct(COORD pos, int spd)
{
	cTruck* obj = new cTruck(*this);
	obj->topleft = pos;
	obj->speed = spd;
	return obj;
}

void cTruck::hitEffect(cPeople* pVictim) {}
void cTruck::hitSound() {}

cHelicopter::cHelicopter() : cHelicopter({ 0, 40 }, 2) {};
cHelicopter::cHelicopter(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	pTexture = &cHelicopter::textureHeli[0];
	pLTexture = pTexture;
	currentFrame = 0;
	nFrame = textureHeli.size();
}

cHelicopter::~cHelicopter()
{
	delete bootstrapObjectcHelicopter;
}

char cHelicopter::getType()
{
	return 'H';
}

cObstacle* cHelicopter::copy(COORD pos)
{
	cHelicopter* obj = new cHelicopter(*this);
	obj->topleft = pos;
	return obj;
}
cObstacle* cHelicopter::construct(COORD pos, int spd)
{
	cHelicopter* obj = new cHelicopter(*this);
	obj->topleft = pos;
	obj->speed = spd;
	return obj;
}

void cHelicopter::hitEffect(cPeople* pVictim)
{
}
void cHelicopter::hitSound()
{
}
cMotorbike::cMotorbike() : cMotorbike({ 0, 40 }, 2) {};
cMotorbike::cMotorbike(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cVehicle(In_pos, /*difficulty, ttm*/ speed) {
	pTexture = &cMotorbike::textureMotorb[0];
	pLTexture = pTexture;
	currentFrame = 0;
	nFrame = textureMotorb.size();
}

cMotorbike::~cMotorbike()
{
	delete bootstrapObjectcMotorbike;
}

char cMotorbike::getType()
{
	return 'M';
}

cObstacle* cMotorbike::copy(COORD pos)
{
	cMotorbike* obj = new cMotorbike(*this);
	obj->topleft = pos;
	return obj;
}
cObstacle* cMotorbike::construct(COORD pos, int spd)
{
	cMotorbike* obj = new cMotorbike(*this);
	obj->topleft = pos;
	return obj;
}

void cMotorbike::hitEffect(cPeople* pVictim)
{
}
void cMotorbike::hitSound()
{}

