#include "Map.h"

	vector<gameMap> gameMap::listMap = gameMap::loadMap();
	gameMap* gameMap::currentMap = &gameMap::listMap[0];
	MapIndex gameMap::currentMapIndex = MapIndex::Jungle;

    vector<gameMap> gameMap::loadMap()
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