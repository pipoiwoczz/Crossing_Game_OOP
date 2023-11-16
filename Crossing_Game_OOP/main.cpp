#include "cGame.h"

bool playing = true;

void fx(COORD topleft, vector<Texture> &listFrame)
{
	
	for (auto e : listFrame)
	{
		topleft = { short(max(topleft.X, 0)), short(max(topleft.Y, 0))};
		CHAR_INFO* readyBuffer = new CHAR_INFO[e.width * e.height];
		memcpy(readyBuffer, e.textureArray, e.width * e.height * sizeof(CHAR_INFO));

		for (int i = 0; i < e.width * e.height; i++)
		{
			if (readyBuffer[i].Char.UnicodeChar == L' ') {
				readyBuffer[i].Attributes = cAsset::getCurrentMap()->mapArray[(topleft.Y + i / e.width) * cAsset::getCurrentMap()->width + topleft.X + (i % e.width)].Attributes;
			}
		}

		SMALL_RECT reg = { topleft.X , topleft.Y,  topleft.X + e.width - 1, topleft.Y + e.height - 1 };

		WriteConsoleOutput(mainHandle, readyBuffer, { e.width , e.height }, { 0,0 }, &reg);
		delete[]readyBuffer;
		//system("pause");
		Sleep(120);
	}
}

bool impactNow(cPeople& pp, cLion& li, vector<Texture> &f)
{
	for (int i = 0; i < pp.mBoxes.size(); i++)
	{
		for (int j = 0; j < li.boxes.size(); j++)
		{
			if (li.boxes[j].isOverlap(pp.mBoxes[i]))
			{
				fx(li.getPos(), f);
				return true;;
			}
		}
	}
	return false;
}



int main()
{
	system("cls");
	//Graphic gr;

	//string namelist[]{ "base.txt", "purple.txt", "blast.txt", "explosion1.txt","explosion2.txt", "explosion3.txt","fade1.txt", "fade2.txt", "fade3.txt", "dissappear.txt"};
	//string mapanimation[]{ "m1.txt", "m2.txt" ,"m3.txt" ,"m4.txt", "m5.txt", "m6.txt", "m7.txt" };
	//vector<Texture> f;
	//ifstream test;
	//for (auto name : mapanimation)
	//{
	//	test.open(name);
	//	if (test.is_open())
	//	{
	//		Texture a;
	//		test >> a.height >> a.width;
	//		a.textureArray = new CHAR_INFO[a.height * a.width];

	//		for (int i = 0; i < a.height; i++)
	//		{
	//			//  BlankSegment bla;
	//			//  bool encounter = false;

	//			for (int j = 0; j < a.width; j++)
	//			{
	//				int x;
	//				test >> x;
	//				if (x != 16 && x != 17)
	//				{
	//					/*   if (encounter) {
	//						   encounter = false;
	//						   loaded.blankTexture[i].push_back(bla);
	//					   }*/
	//					CHAR_INFO t = { L'█', x * 16 + x};
	//					a.textureArray[i * a.width + j] = t;

	//				}
	//				else {
	//					/* if (!encounter) {
	//						 encounter = true;
	//						 bla.start = j;
	//						 bla.end = bla.start - 1;
	//					 }
	//					 bla.end++;*/
	//					CHAR_INFO t = { L' ', 11 * 16 + 11};
	//					a.textureArray[i * a.width + j] = t;
	//				}
	//			}
	//		}
	//		f.push_back(a);
	//	}
	//	test.close();
	//}
	//cGame a;
	//a.drawBackGround();
	//COORD center = { 100,50 };
	//cRhino r(center, 1);
	//r.draw();
	//system("pause");
	//for (int i = 0; i < 3; i++)
	//{
	//	fx({ 0,0 }, f);
	//	//system("pause");
	//}

	//cLion b({ 20, 20 }, 1);
	//b.draw();
	//system("pause");
	// 
	
	//for (int i = 0; i < 10; i++)
	//	fx({ 0,0 }, f);
//	cPeople cr({ 20,20 });
// 
	cout << sizeof(WORD) << endl;
//cLion li({ 50, 50 }, 1);
//while (true)
//{
//	if (GetAsyncKeyState(0x51) < 0)
//		break;
//
//
//	li.move();
//	COORD p = li.getPos();
//
//	if (p.X > My_Windows.Right)
//	{
//		li.setPos({ 0, p.Y });
//	}
//
//	Sleep(20);
//	a.refreshBackGround();
//	
//}
//	system("pause");
//	
//	
//
//	while (true) {
//		//for (int i = 0; i < cr.mBoxes.size(); i++)
//		//{
//		//	cout << cr.mBoxes[i].topleft.X << " - " << cr.mBoxes[i].topleft.Y << endl;
//		//	cout << cr.mBoxes[i].botright.X << " - " << cr.mBoxes[i].botright.Y << endl;
//		//}
//
//		//cout << endl;
//
//		//for (int i = 0; i < li.boxes.size(); i++)
//		//{
//		//	cout << li.boxes[i].topleft.X << " - " << li.boxes[i].topleft.Y << endl;
//		//	cout << li.boxes[i].botright.X << " - " << li.boxes[i].botright.Y << endl;
//		//}
//
//
//
//	if (GetAsyncKeyState(0x51) < 0)
//		break;
//	li.move();
//	if (cr.move()) {
//		
//	}
//
//	if (impactNow(cr, li, f)) {
//		a.drawBackGround();
//		break;
//	}
//
//
//	Sleep(30);
//	system("cls");
//	a.drawBackGround();
//	cr.draw();
//	li.draw();
//}

	//std::thread myTh(myFunct, ref(cr), ref(li));

	//while (true) {
	//	if (GetAsyncKeyState(0x51) < 0)
	//		break;
	//	cr.move();
	//	li.move();
	//	Sleep(100);
	//	a.refreshBackGround();
	//	li.draw();
	//	cr.draw();
	//}
	//myTh.join();
	//cRhino b({ 0, 20 }, 1);
	//cRhino c({ 100, 120 }, 1);
	//system("pause");
	//b.draw();
	//	const int desiredFPS = 60;
	//const std::chrono::duration<double> frameTime(1.0 / desiredFPS);
	//auto previousTime = std::chrono::high_resolution_clock::now();
	//auto currentTime = previousTime;
	//const chrono::duration<double> wait(0.01);
	//int i = 0;
	//while (i++ < 200) {	
	//	currentTime = std::chrono::high_resolution_clock::now();
	//	std::chrono::duration<double> deltaTime = currentTime - previousTime;

	//	if (deltaTime >= frameTime) {
	//		 //Update game logic and handle input here.
	//		a.drawBackGround();
	//		 //Render the game.
	//		b.draw();
	//		c.draw();
	//		b.setPos({ short(b.getPos().X + 3*2), b.getPos().Y });
	//		c.setPos({ short(c.getPos().X + 3*2), c.getPos().Y });
	//		// Reset the previous time for the next frame.
	//		previousTime = currentTime;
	//	}

	//	// Sleep to control the frame rate.
	//	std::this_thread::sleep_for(frameTime - deltaTime);
	//	
	//}
	

}