#include "Map.h"
#include "cAsset.h"
	vector<gameMap> gameMap::listMap = gameMap::loadMap();
	gameMap* gameMap::currentMap = &gameMap::listMap[0];
	MapIndex gameMap::currentMapIndex = MapIndex::Jungle;

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

    vector<gameMap> gameMap::loadMap()
    {
        vector<gameMap> loadedMap;
        for (string filename: maplist)
        {
            ifstream mapIn;
            gameMap map;
            mapIn.open(filename);
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

    gameMap* gameMap::getCurrentMap()
    {
        return gameMap::currentMap;
    }

    void gameMap::changeMap(MapIndex newMapIndex)
    {
        currentMap = &listMap[int(newMapIndex) % maplist.size()];
    }

    void gameMap::nextMap() {
        currentMapIndex = MapIndex((int(currentMapIndex) + 1) % maplist.size());
        currentMap = &listMap[int(currentMapIndex) % maplist.size()];
    }