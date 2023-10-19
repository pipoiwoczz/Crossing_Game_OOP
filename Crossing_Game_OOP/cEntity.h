#ifndef _CENTITY_H
#define _CENTITY_H
#include "setup.h"
#include "cAsset.h"
class cEntity {
protected:
	vector<wstring> model;
	vector<vector<TextureInfo>> texture;
	vector<int> padding;
	void cleaner(vector<wstring>& model, vector<int>& Charpadding);
	void printer(vector<wstring>& model, vector<vector<TextureInfo>>& texture, vector<int>& Charpadding);
public:
	virtual short** getHitBoxX() {
		return nullptr;
	}
	//virtual void draw();

public:
	COORD pos;

	cEntity(COORD In_pos);
	~cEntity();

	COORD getPos();
	void setPos(COORD new_pos);
	bool collide(cEntity anotherHitbox);

};
#endif 