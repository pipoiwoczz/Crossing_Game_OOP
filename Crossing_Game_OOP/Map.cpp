#include "Map.h"
#include "cAsset.h"

    gameMap::gameMap()
    {
        mapArray = nullptr;
        width = 0;
        height = 0;
    }
    gameMap::~gameMap()
    {
        if (mapArray)
            delete[]mapArray;
    }
    gameMap::gameMap(const gameMap& a)
    {
        height = a.height;
        width = a.width;
        this->mapArray = new CHAR_INFO[height * width];
        memcpy(mapArray, a.mapArray, a.height * a.width * sizeof(CHAR_INFO));
    }

    gameMap& gameMap::operator=(const gameMap& a)
    {
        if (&a != this)
        {
            height = a.height;
            width = a.width;
            delete[]mapArray;
            this->mapArray = new CHAR_INFO[height * width];
            memcpy(mapArray, a.mapArray, a.height * a.width * sizeof(CHAR_INFO));

        }
        return *this;
    }

    vector<gameMap> gameMap::loadMap(const vector<string> &mapFrame)
    {
        vector<gameMap> loadedMap;
        for (string filename: mapFrame)
        {
            ifstream mapIn;
            gameMap map;
            mapIn.open("Sprites//" + MapPrefix + filename);
            if (mapIn.is_open()) {
                mapIn >> map.height >> map.width;
                map.mapArray = new CHAR_INFO[map.height * map.width];
                    for (int i = 0; i < map.height * map.width; i++)
                {
                    int x;
                    mapIn >> x;
                    CHAR_INFO t = { L' ', WORD(x * 16)};
                    map.mapArray[i] = t;
                }
            }
            loadedMap.push_back(map);
            mapIn.close();
        }
        return loadedMap;
    }

    gameMap* gameMap::getCurrentMap()
    {
        return gameMap::currentMap;
    }

    void gameMap::changeMapTheme(MapTheme newTheme)
    {
        currentTheme = int(newTheme);
        numCurrentMapFrame = listMap[currentTheme].size();
        currentMap = &listMap[currentTheme][0];
        currentMapIndex = 0;
    }

    void gameMap::nextMapFrame() {
        currentMapIndex = (currentMapIndex + 1) % numCurrentMapFrame;
        currentMap = &listMap[currentTheme][currentMapIndex];
    }