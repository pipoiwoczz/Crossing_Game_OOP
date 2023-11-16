//#include "Tank.h"
//
//Tank::Tank() : cObstacle{ {60,50}, 2 } {
//	h = GetStdHandle(STD_OUTPUT_HANDLE);
//	tankU = loader("tankU.txt", charHV, charWV);
//	tankD = loader("tankD.txt", charHV, charWV);
//	tankL = loader("tankL.txt", charHH, charWH);
//	tankR = loader("tankR.txt", charHH, charWH);
//	pos = center;
//
//}
//
//Tank::Tank(COORD pos, int speed) : cObstacle{ pos, speed } {
//	h = GetStdHandle(STD_OUTPUT_HANDLE);
//	tankU = loader("tankU.txt", charHV, charWV);
//	tankD = loader("tankD.txt", charHV, charWV);
//	tankL = loader("tankL.txt", charHH, charWH);
//	tankR = loader("tankR.txt", charHH, charWH);
//	pos = center;
//
//}
//
//void Tank::moveRight(Map &map) {
//	short* curW = &charWH;
//	short* curH = &charHH;
//	//while (true) {
//		float dx = 0;
//		dx++;
//		curH = &charHH;
//		curW = &charWH;
//
//		COORD topleftPlayer = { center.X - 0.5 * *(curW), center.Y - 0.5 * *(curH) };
//	//	if (topleftPlayer.X + dx >= 0 && topleftPlayer.X + dx < 478 - charWH) {
//			center.X += dx * 3;
//		//}
//		CHAR_INFO* pP = new CHAR_INFO[*(curH) * *(curW)];
//		memcpy(pP, tankR, *(curH) * *(curW) * sizeof(CHAR_INFO));
//		CHAR_INFO* bg = map.getBG();
//		short width = map.getWidth();
//		for (int i = 0; i < *(curH) * *(curW); i++)
//		{
//			if (pP[i].Char.UnicodeChar == L'b') {
//				pP[i].Char.UnicodeChar = L' ';
//				pP[i].Attributes = bg[(topleftPlayer.Y + i / *curW) * width + topleftPlayer.X + (i % *curW)].Attributes;
//			}
//		}
//
//		//map.draw();
//		SMALL_RECT playerRect = { topleftPlayer.X, topleftPlayer.Y, *curW + topleftPlayer.X - 1, *curH + topleftPlayer.Y - 1 };
//
//		WriteConsoleOutput(h, pP, { *curW, *curH }, { 0,0 }, &playerRect);
//		delete[]pP;
//
//		//Sleep(25.0 / speed / 60 * 1000.0);
//		srand(time(NULL));
//		int random = rand() % 100;
//		
//		if (center.X > 500 + random) {
//			center.X = -45;
//		}
////	}
//}
//
//void Tank::moveLeft(Map &map) {
//	short* curW = &charWH;
//	short* curH = &charHH;
//	
//	
//	//while (true) {
//		float dx = 0;
//		dx--;
//		curH = &charHH;
//		curW = &charWH;
//
//		COORD topleftPlayer = { center.X - 0.5 * *(curW), center.Y - 0.5 * *(curH) };
//		if (topleftPlayer.X + dx >= 0 && topleftPlayer.X + dx < 478 - charWH) {
//			center.X += dx * 3;
//		}
//
//		CHAR_INFO* pP = new CHAR_INFO[*(curH) * *(curW)];
//		memcpy(pP, tankL, *(curH) * *(curW) * sizeof(CHAR_INFO));
//		CHAR_INFO* bg = map.getBG();
//		short width = map.getWidth();
//		for (int i = 0; i < *(curH) * *(curW); i++)
//		{
//			if (pP[i].Char.UnicodeChar == L'b') {
//				pP[i].Char.UnicodeChar = L' ';
//				pP[i].Attributes = bg[(topleftPlayer.Y + i / *curW) * width + topleftPlayer.X + (i % *curW)].Attributes;
//			}
//		}
//
//		//map.draw();
//		SMALL_RECT playerRect = { topleftPlayer.X, topleftPlayer.Y, *curW + topleftPlayer.X - 1, *curH + topleftPlayer.Y - 1 };
//
//		WriteConsoleOutput(h, pP, { *curW, *curH }, { 0,0 }, &playerRect);
//		delete[]pP;
//
//		//Sleep(25.0 / speed / 60 * 1000.0);
//		srand(time(NULL));
//		int random = rand() % 100;
//
//		if (center.X < -45 - random) {
//			center.X = 480;
//		}
//	//}
//}
//
//void Tank::move(Map &map) {
//	if (isMovingLeft == true) {
//		moveLeft(map);
//	}
//	else {
//		moveRight(map);
//	}
//
//}