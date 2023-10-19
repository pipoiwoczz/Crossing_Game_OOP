#include "cPeople.h"

cPeople::cPeople() : cEntity({50, 50}) {
	mState = true;
}
cPeople::cPeople(COORD In_pos) : cEntity(In_pos)
{
	mState = true;
}
cPeople::~cPeople()
{
	
}

void cPeople::draw(COORD pos) {
	wstring content[3];
	printCharacter(L"     ", {short (pos.X), short(pos.Y - 1)}, Color::bright_white, Color::bright_white);
	printCharacter(L"     ", { short(pos.X), short(pos.Y + 3) }, Color::bright_white, Color::bright_white);
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			printCharacter(L"     ", pos, Color::green, Color::green);
		}
		if (i == 1) {
			printCharacter(L"     ", { pos.X, short(pos.Y + 1) }, Color::black, Color::green);
			printCharacter(L" ", { short(pos.X + 1), short(pos.Y + 1) }, Color::black, Color::black);
			printCharacter(L" ", { short(pos.X + 3), short(pos.Y + 1) }, Color::black, Color::black);
		}
		else if (i == 2) {
			printCharacter(L"     ", { pos.X, short(pos.Y + 2) }, Color::green, Color::green);
		}
	}
}

void cPeople::up(){
	COORD pos = getPos();
	pos.Y--;
	setPos(pos);
	draw(pos);
}

void cPeople::down() {
	COORD pos = getPos();
	pos.Y++;
	setPos(pos);
	draw(pos);
}

void delPeople(COORD pos) {
	int y = pos.Y;
	for (int i = y; i < y + 3; i++) {
		printCharacter(L" ", { pos.X, short(i) }, Color::bright_white, Color::bright_white);
	}
}

void cPeople::left() {
	COORD pos = getPos();
	delPeople({ short(pos.X + 4), pos.Y });
	delPeople({ short(pos.X + 3), pos.Y });
	pos.X -= 2;
	setPos(pos);
	draw(pos);
}


void cPeople::right() {
	COORD pos = getPos();
	delPeople(pos);
	delPeople({short(pos.X + 1), pos.Y});
	pos.X += 2;
	setPos(pos);
	draw(pos);
}

void cPeople::move(char &MOVING) {
	if (MOVING == 'S') {
		down();
	}
	else if (MOVING == 'W') {
		up();
	}
	else if (MOVING == 'A') {
		left();
	}
	else if (MOVING == 'D') {
		right();
	}
}
/*
bool cPeople::isImpactOneLion(cLion *lion) {
	COORD pos = (*lion).getPos();
	short** lionShapeTemp = (*lion).getHitBoxX();
	short lionShape[5][2];
	for (int i = 0; i < 5; i++) {
		lionShape[i][0] = lionShapeTemp[i][0];
		lionShape[i][1] = lionShapeTemp[i][1];
	}
	for (int i = 0; i < 5; i++) {
		delete[] lionShapeTemp[i];
	}
	delete[] lionShapeTemp;
	for (int i = 0; i < 5; i++) {
		if (mX >= lionShape[i][0] && mX < lionShape[i][1] && mY >= pos.Y && mY < pos.Y + 6)

			return true;
	}
	for (int i = 0; i < 5; i++) {
		if (mX + 4 >= lionShape[i][0] && mX < lionShape[i][1] && mY >= pos.Y && mY < pos.Y + 6)
			return true;
	}
	for (int i = 0; i < 5; i++) {
		if (mX >= lionShape[i][0] && mX < lionShape[i][1] && mY + 2 >= pos.Y && mY < pos.Y + 6)
			return true;
	}
	for (int i = 0; i < 5; i++) {
		if (mX + 4 >= lionShape[i][0] && mX < lionShape[i][1] && mY + 2 >= pos.Y && mY < pos.Y + 6)
			return true;
	}
	return false;
}

bool cPeople::isImpactLion(cLion* lion) {
	for (int i = 0; i < 7; i++) {
		if (isImpactOneLion(&lion[i])) {
			isDead();
			drawLosingTitle();
			return true;
		}
	}
	return false;
}

*/