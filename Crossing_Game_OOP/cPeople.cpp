#include "cPeople.h"
#include "cAsset.h"
#include "hitbox.h"

cPeople::cPeople() : cPeople({0, 145}) {}
cPeople::cPeople(COORD In_pos) {
	topleft = In_pos;
	mState = true;
	moveCooldown = 0;
	skin = cAsset::assetLoaders(peopleFile);
	pTexture = &skin[0];
	currentFrame = 0;
	Hitbox a({ short(topleft.X + 4), short(2 + topleft.Y) }, { short(skin[0].getWidth() - 4 + topleft.X), short(skin[0].getHeight() - 2 + topleft.Y) });

	mBoxes.push_back(a);

}
cPeople::~cPeople() {


}

COORD cPeople::getPos() {
	return topleft;
}
void cPeople::setPos(COORD pos) {
	topleft = pos;
}
bool cPeople::getState()
{
	return mState;
}

bool cPeople::isDead() {
	mState = false;
	return true; // why?
}
bool cPeople::isFinish() {
	return true;
}


bool cPeople::move() {
	if (moveCooldown > 0)
	{	
		moveCooldown--;
		return false;
	}
	moveCooldown = 10;
	bool ismove = false;
	bool horizon;
	float dx = 0, dy = 0;
	if (GetAsyncKeyState(VK_LEFT) < 0 && topleft.X > 0) {
		dx--;
		horizon = true;
		ismove = true;
	}

	if (GetAsyncKeyState(VK_RIGHT) < 0 && topleft.X < PlayBoxRect.Right - pTexture->getWidth()) {
		dx++;	
		horizon = true;
		ismove = true;

	}

	if (GetAsyncKeyState(VK_UP) < 0) {
		if (topleft.Y > 1) 
		{
			dy--;
			horizon = false;
			ismove = true;
		}
		else {
			passLevel = true;
			
		}

	} 

	if (GetAsyncKeyState(VK_DOWN) < 0 && topleft.Y < PlayBoxRect.Bottom - pTexture->getHeight() + 1) {
		dy++;
		horizon = false;
		ismove = true;

	}
	if (ismove )
	{
		if (horizon)
			topleft.X += dx * pTexture->getWidth();
		else
			topleft.Y += dy * pTexture->getHeight();
		for (int i = 0; i < mBoxes.size(); i++)
		{
			mBoxes[i].set({ short(topleft.X), short(topleft.Y) }, { short(pTexture->getWidth() + topleft.X - 1), short(pTexture->getHeight() + topleft.Y - 1) });
		}
		return ismove;
	}
}
