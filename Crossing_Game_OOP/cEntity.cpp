#include "cEntity.h"

cEntity::cEntity(COORD In_pos) {
    pos = In_pos;
}
cEntity::~cEntity() {

}
bool cEntity::collide(cEntity anotherHitbox) {
    return true;
}

COORD cEntity::getPos()
{
    return pos;
}

void cEntity::setPos(COORD new_pos)
{
    pos = new_pos;
}


void cEntity::cleaner(vector<wstring>& model, vector<int>& Charpadding)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD Written;

    for (int i = 0; i < model.size(); i++)
    {
        FillConsoleOutputCharacterW(hOut, L'\0', model[i].length() + Charpadding[i], { short(pos.X + i), pos.Y }, &Written);
    }
}
void cEntity::printer(vector<wstring>& model, vector<vector<TextureInfo>>& texture, vector<int>& Charpadding)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD Written;

    for (int i = 0; i < model.size(); i++)
    {
        short cX = pos.X + Charpadding[i];
        for (int j = 0; j < model[i].length(); j++)
        {
            int color = int(texture[i][j].ForeG) + int(texture[i][j].BackG) * 16;
            FillConsoleOutputAttribute(hOut, color, 1, { short(cX + j), short(pos.Y + i) }, &Written);
            FillConsoleOutputCharacterW(hOut, model[i][j], 1, { short(cX + j), short(pos.Y + i) }, &Written);
        }
    }
}

