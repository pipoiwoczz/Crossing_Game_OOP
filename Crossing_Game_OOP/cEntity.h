#ifndef _CENTITY_H
#define _CENTITY_H
#include "setup.h"
#include "cAsset.h"
#include "hitbox.hpp"

class cEntity
{
protected:
	vector<wstring> model;
	vector<vector<TextureInfo>> texture;
	vector<int> padding;
	void cleaner(vector<wstring>& model, vector<int>& Charpadding);
	void printer(vector<wstring>& model, vector<vector<TextureInfo>>& texture, vector<int>& Charpadding);
    
    COORD pos;
    vector<Hitbox> hitboxes; //list of (rectangular) hitboxes
    int speed; // determines time between moves. lower = faster
    int timeToMove; // time left until next move. reset to [speed] when it reaches 0.
public:
//	virtual short** getHitBoxX() {
//		return nullptr;
//	}
	//virtual void draw();
    
    virtual void getHitbox();
    void move(COORD displace) // displace contains movement in both axes. direction determined by sign (+/-)
    {
        pos.X += displace.X;
        pos.Y += displace.Y;
        for (Hitbox h : hitboxes)
            h.move(displace);
    }
    
	//COORD pos;

	cEntity(COORD In_pos);
	~cEntity();

	COORD getPos();
	void setPos(COORD new_pos);
	bool collide(cEntity anotherEntity);
};
#endif 
