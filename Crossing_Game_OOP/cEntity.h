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
    vector<Hitbox> hitboxes;
public:
//	virtual short** getHitBoxX() {
//		return nullptr;
//	}
	//virtual void draw();
    
    virtual void getHitbox();
    
	//COORD pos;

	cEntity(COORD In_pos);
	~cEntity();

	COORD getPos();
	void setPos(COORD new_pos);
	bool collide(cEntity anotherEntity);
};
#endif 
