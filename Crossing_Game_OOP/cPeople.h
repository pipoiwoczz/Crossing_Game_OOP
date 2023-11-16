#ifndef _CPEOPLE_H
#define _CPEOPLE_H
#include "setup.h"
#include "cAsset.h"
#include "cAnimal.h"
#include "cVehicle.h"
//#include "Map.h"
class cPeople {
	//int mX, mY;


	vector<Texture> skin;
	Texture* pTexture;
	int currentFrame;
	short height, width;
	HANDLE h;
    COORD topleft;
	bool mState; // true is alive, false is dead =))


	public:
		/*vector<Hitbox> mBoxes;*/
		vector<Hitbox> mBoxes;
		cPeople() : cPeople({ 200, 100 }) {}
		cPeople(COORD In_pos) {
			topleft = In_pos;
			mState = true;
			skin = cAsset::assetLoader2(peopleFile);
			pTexture = &skin[0];
			currentFrame = 0;
			Hitbox a(In_pos, {short(skin[0].width + topleft.X), short(skin[0].height + topleft.Y)});
			
			mBoxes.push_back(a);

		}
		~cPeople() {
			

		}

		COORD getPos() {
			return topleft;
		}
		void setPos(COORD pos) {
			topleft = pos;
		}
        bool getState ()
        {
            return mState;
        }
        

		void draw();
    
		void up();
		void down();
		void left();
		void right();
		bool move();
		void erase();
//		bool isImpactOneLion(cLion *lion);
//		bool isImpactLion(cLion *lion);
//		bool isImpact(cVehicle *vehicle);
		bool isImpact(cObstacle obsta)
		{
			for (int i = 0; i < mBoxes.size(); i++)
			{
				for (int j = 0; j < obsta.boxes.size(); j++)
				{
					if (obsta.boxes[j].isOverlap(mBoxes[i]))
					{
						return true;
					}
				}
			}
			return false;
		}
		bool isDead() {
			mState = false;
			return true; // why?
		}
		bool isFinish() {
			//if (mY == 10) {
			//	return true;
			//}
			//return false;
		}
};

#endif
