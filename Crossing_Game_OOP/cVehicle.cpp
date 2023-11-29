#include "cVehicle.h"
#include "cAsset.h"
#include "hitbox.h"

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

unsigned char cTruck::getType()
{
	return 'T';
}

cTruck::~cTruck()
{
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

unsigned char cHelicopter::getType()
{
	return 'H';
}

cHelicopter::~cHelicopter()
{
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

unsigned char cMotorbike::getType()
{
	return 'M';
}

cMotorbike::~cMotorbike()
{
}

void cMotorbike::hitEffect(cPeople* pVictim)
{
}
void cMotorbike::hitSound()
{}

