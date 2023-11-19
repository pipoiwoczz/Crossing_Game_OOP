#include "cAsset.h"


vector<gameMap> cAsset::listMap = cAsset::loadMap();
gameMap* cAsset::currentMap = &cAsset::listMap[0];
MapIndex cAsset::currentMapIndex = MapIndex::Jungle;

Texture cAsset::assetLoader(string filename)
{
    ifstream inGate;
    inGate.open(filename);
    Texture loaded;
    if (inGate.is_open()) {
        inGate >> loaded.height >> loaded.width;
       // loaded.blankTexture.resize(loaded.height);
        loaded.textureArray = new CHAR_INFO[loaded.height * loaded.width];
        for (int i = 0; i < loaded.height; i++)
        {
          //  BlankSegment bla;
          //  bool encounter = false;

            for (int j = 0; j < loaded.width; j++)
            {
                int x;
                inGate >> x;
                if (x != 16)
                {
                 /*   if (encounter) {
                        encounter = false;
                        loaded.blankTexture[i].push_back(bla);
                    }*/
                    CHAR_INFO t = { L'█', x * 16 + x};
                    loaded.textureArray[i * loaded.width + j] = t;

                }
                else {
                   /* if (!encounter) {
                        encounter = true;
                        bla.start = j;
                        bla.end = bla.start - 1;
                    }
                    bla.end++;*/
                    CHAR_INFO t = { L' ', x * 16 };
                    loaded.textureArray[i * loaded.width + j] = t;
                }
                
                
            }
         /*   if (encounter) {
                loaded.blankTexture[i].push_back(bla);
            }*/
        }
    }
    inGate.close();
    return loaded;
}

vector<Texture> cAsset::assetLoader2(const vector<string>& textureList)
{
    //  string namelist[] {"unk1.txt", "unk2.txt"};
    vector<Texture> multiFrame;
    for (string name : textureList)
    {
        Texture a = cAsset::assetLoader(name);
        multiFrame.push_back(a);
    }

    return multiFrame;
}

vector<gameMap> cAsset::loadMap()
{
    vector<gameMap> loadedMap;
    for (string mapName : maplist)
    {
        ifstream mapIn;
        gameMap map;
        mapIn.open(mapName);
        if (mapIn.is_open()) {
            mapIn >> map.height >> map.width;
            map.mapArray = new CHAR_INFO[map.height * map.width];
            for (int i = 0; i < map.height * map.width; i++)
            {
                int x;
                mapIn >> x;
                CHAR_INFO t = { L' ', x * 16 };
                map.mapArray[i] = t;
            }
        }
        loadedMap.push_back(map);
        mapIn.close();
    }
    return loadedMap;
}

gameMap* cAsset::getCurrentMap()
{
    return cAsset::currentMap;
}

void cAsset::changeMap(MapIndex newMapIndex)
{
    currentMap = &listMap[int(newMapIndex) % maplist.size()];
}

void cAsset::nextMap() {
    currentMapIndex = MapIndex((int(currentMapIndex) + 1) % maplist.size());
    currentMap = &listMap[int(currentMapIndex) % maplist.size()];
}