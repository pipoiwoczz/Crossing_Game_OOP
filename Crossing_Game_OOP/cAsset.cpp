#include "cAsset.h"




Texture cAsset::assetLoader(string filename)
{
    ifstream inGate;
    inGate.open(filename);
    Texture loaded;
    if (inGate.is_open()) {
        inGate >> loaded.height >> loaded.width;
        loaded.textureArray = new CHAR_INFO[loaded.height * loaded.width];
        for (int i = 0; i < loaded.height; i++)
        {
            for (int j = 0; j < loaded.width; j++)
            {
                int x;
                inGate >> x;
                if (x != 16)
                {
                    CHAR_INFO t = { L'█', x * 16 + x};
                    loaded.textureArray[i * loaded.width + j] = t;

                }
                else {
                    CHAR_INFO t = { L' ', x * 16 };
                    loaded.textureArray[i * loaded.width + j] = t;
                }
                
                
            }
        }
    }
    inGate.close();
    return loaded;
}

vector<Texture> cAsset::assetLoaders(const vector<string>& textureList)
{
    vector<Texture> multiFrame;
    for (string name : textureList)
    {
        Texture a = cAsset::assetLoader(name);
        multiFrame.push_back(a);
    }

    return multiFrame;
}

