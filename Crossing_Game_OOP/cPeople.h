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
	HANDLE h;
    COORD topleft;
	bool mState; // true is alive, false is dead =))
	int moveCooldown;

	public:
		friend class cGameEngine;
		/*vector<Hitbox> mBoxes;*/
		vector<Hitbox> mBoxes;
		cPeople() : cPeople({ 200, 100 }) {}
		cPeople(COORD In_pos) {
			topleft = In_pos;
			mState = true;
			moveCooldown = 0;
			skin = cAsset::assetLoaders(peopleFile);
			pTexture = &skin[0];
			currentFrame = 0;
			Hitbox a({ short(topleft.X + 4), short( 2 + topleft.Y) }, {short(skin[0].getWidth() - 4 + topleft.X), short(skin[0].getHeight() - 2 + topleft.Y)});
			
			mBoxes.push_back(a);

		}
		~cPeople() {
			

		}

		COORD getPos() {
			return mBoxes[0].topleft;
		}
		void setPos(COORD pos) {
			topleft = pos;
		}
        bool getState ()
        {
            return mState;
        }
        
    
		void up();
		void down();
		void left();
		void right();
		bool move();
		void erase();

		bool isImpact(cObstacle* obsta)
		{
			for (int i = 0; i < mBoxes.size(); i++)
			{
				for (int j = 0; j < obsta->boxes.size(); j++)
				{
					if (obsta->boxes[j].isOverlap(mBoxes[i]))
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
