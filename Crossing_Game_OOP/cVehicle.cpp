#include "cVehicle.h"

cVehicle::cVehicle(COORD In_pos, int difficult, VehicleIndex Vindex) : cEntity(In_pos)
{
	level = difficult;
	model = cAsset::getModel(Vindex);
	texture = cAsset::getTexture(Vindex);
	padding = cAsset::getPadding(Vindex);
	printer(model, texture, padding);
}

cVehicle::~cVehicle()
{

}

cTruck::cTruck(COORD In_pos, int difficult) : cVehicle(In_pos, difficult, VehicleIndex::Truck)
{
}

cTruck::~cTruck()
{

}

void cTruck::move(bool ToRight)
{

}

short** cTruck::getHitBoxX()
{
	return nullptr;
}
/*
void cTruck::draw(COORD pos) {
	wstring content[5];

	
	for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
	}
}	
*/
cHelicopter::cHelicopter(COORD In_pos, int difficult) : cVehicle(In_pos, difficult, VehicleIndex::Helicopter)
{
	model = cAsset::getModel(VehicleIndex::Helicopter);
	texture = cAsset::getTexture(VehicleIndex::Helicopter);
	padding = cAsset::getPadding(VehicleIndex::Helicopter);
	printer(model, texture, padding);
}

cHelicopter::~cHelicopter()
{

}

void cHelicopter::move(bool ToRight)
{

}

short** cHelicopter::getHitBoxX()
{
	return nullptr;
}

cMotorbike::cMotorbike(COORD In_pos, int difficult) : cVehicle(In_pos, difficult, VehicleIndex::Motorbike)
{
	model = cAsset::getModel(VehicleIndex::Motorbike);
	texture = cAsset::getTexture(VehicleIndex::Motorbike);
	padding = cAsset::getPadding(VehicleIndex::Motorbike);
	printer(model, texture, padding);
}

cMotorbike::~cMotorbike()
{

}

void cMotorbike::move(bool ToRight)
{

}

short** cMotorbike::getHitBoxX()
{
	return nullptr;
}
/*
void cHelicopter::draw(COORD pos) {
	wstring content[5];
	content[0] = L"▀▀▀▀█▀▀▀▀";
	content[1] = L"─▄▀█▀▀█──────▄";
	content[2] = L"█▄▄█▄▄██████▀";
	content[3] = L"▀▀█▀▀▀█▀▀";
	content[4] = L"─▀▀▀▀▀▀▀";
	for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
	}
}

void cMotorbike::draw(COORD pos) {
	wstring content[5];
	content[0] = L"";
	content[0] = L"───────────▀▄";
	content[1] = L"──█▄▄▄▄▄███▀▄─▄▄";
	content[2] = L"▄▀──▀▄─▀▀█▀▀▄▀──▀▄";
	content[3] = L"▀▄▀▀█▀▀████─▀▄──▄▀";
	content[4] = L"──▀▀──────────▀▀";
	for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::green, Color::bright_white);
	}
}
*/