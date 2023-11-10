#include "setup.h"
#include "Map.h"
#include "Graphics.h"
#include "Tank.h"

int main() {
	Graphic gr;
	Map map("te.txt");
	Tank t({ 250, 50 }, 2);
	t.setSpeed(10);
	bool isMovingLeft = true;
	isMovingLeft = false;
	t.setDirection(isMovingLeft);
	t.move(map);

	return 1;
}