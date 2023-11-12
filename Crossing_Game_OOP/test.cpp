#include "setup.h"
#include "Map.h"
#include "Graphics.h"
#include "Tank.h"
#include "cPeople.h"

int main() {
	Graphic gr;
	Map map("te.txt");
	Tank t({ 0, 50 }, 2);
	Tank t2({ 300, 50 }, 10);
	/*t.setSpeed(10);
	bool isMovingLeft = true;
	isMovingLeft = false;
	t.setDirection(isMovingLeft);
	t2.setDirection(isMovingLeft);
	while (true) {
		map.draw();
		auto future1 = async(launch::async, &Tank::move, &t, ref(map));
		auto future2 = async(launch::async, &Tank::move, &t2, ref(map));
		
		Sleep(25.0 / t.getSpeed() / 60 * 1000.0);
	}*/
	cPeople p;
	while (true) {
		p.move(map);
	}

	return 1;
}