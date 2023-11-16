#include "cAnimal.h"

vector<Texture> cLion::textureLion = cAsset::assetLoader2(lionFile);
vector<Texture> cRhino::textureRhino = cAsset::assetLoader2(rhinoFile);
vector<Texture> cCrocodile::textureCroco = cAsset::assetLoader2(crocoFile);



cLion::cLion() : cLion({ 0,20 }, 3) {}
cLion::cLion(COORD In_pos, /*int difficulty, int ttm*/ int speed) : cAnimal(In_pos, /*difficulty, ttm*/ speed) {
    pTexture = &cLion::textureLion[0];
    pLTexture = pTexture;
    currentFrame = 0;
    nFrame = textureLion.size();

    Hitbox a(topleft, { short(topleft.X + pTexture->width), short(topleft.Y + pTexture->height) });

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

