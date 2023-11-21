#include "cAnimal.h"

vector<Texture> cLion::textureLion = cAsset::assetLoaders(lionFile);
vector<Texture> cRhino::textureRhino = cAsset::assetLoaders(rhinoFile);
vector<Texture> cCrocodile::textureCroco = cAsset::assetLoaders(crocoFile);



cLion::cLion() : cLion({ 0,20 }, 3) {}
cLion::cLion(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    pTexture = &cLion::textureLion[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureLion.size();
    Hitbox a({short(topleft.X + 2), short(topleft.Y)}, {short(topleft.X + pTexture->getWidth() - 2), short(topleft.Y + pTexture->getHeight())});

    boxes.push_back(a);
}

cRhino::cRhino() : cRhino({ 0,20 }, 3) {}
cRhino::cRhino(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
   // pTexture = &cRhino::textureRhino;
    pTexture = &cRhino::textureRhino[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureRhino.size();
}

cCrocodile::cCrocodile() : cCrocodile({ 0,20 }, 3) {}
cCrocodile::cCrocodile(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    pTexture = &cCrocodile::textureCroco[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureCroco.size();
}

cObstacle* cLion::bootstrapObjectcLion = cObstacle::addObject(new cLion());
cObstacle* cRhino::bootstrapObjectcRhino = cObstacle::addObject(new cRhino());
cObstacle* cCrocodile::bootstrapObjectcCrocodile = cObstacle::addObject(new cCrocodile());
