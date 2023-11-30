#include "cAsset.h"

vector<Texture> cAsset::alphabet;
vector<Texture> cAsset::number;
Texture cAsset::blankchar = cAsset::assetLoader("Char//Alphabet//blank.txt");

Texture::Texture() {
    height = 0;
    width = 0;
}

Texture::Texture(const Texture& a)
{
    if (a.height != 0 && a.width != 0)
        height = a.height;
    width = a.width;
    this->textureArray = new CHAR_INFO[height * width];
    memcpy(textureArray, a.textureArray, a.height * a.width * sizeof(CHAR_INFO));
}

Texture& Texture::operator=(const Texture& a)
{
    if (&a != this)
    {
        height = a.height;
        width = a.width;
        delete[]textureArray;
        this->textureArray = new CHAR_INFO[height * width];
        memcpy(textureArray, a.textureArray, a.height * a.width * sizeof(CHAR_INFO));
    }
    return *this;
}

Texture::~Texture()
{
    if (textureArray)
        delete[]textureArray;
}

void Texture::setHeight(const short& height)
{
    this->height = height;
}

void Texture::setWidth(const short& width)
{
    this->width = width;
}

short Texture::getHeight() {
    return height;
}

short Texture::getWidth() {
    return width;
}   

Texture cAsset::assetLoader(string filename)
{
    ifstream inGate;
    inGate.open("Sprites//" + filename, ios::binary);

    if (!inGate.is_open())
        return Texture();
    Texture loaded;
    
    inGate.read((char *) &loaded.height, 2);
    inGate.read((char *) &loaded.width, 2);
    int size = loaded.height * loaded.width;
    if (size == 0)
        return loaded;
    
    loaded.textureArray = new CHAR_INFO [size];
    short * info = new short [size];
    inGate.read((char *) info, 2 * size);
    inGate.close();
    
    for (int i = 0; i < size; i++)
    {
        if (info[i] >= 16)
            loaded.textureArray[i] = { L' ', WORD(0)};
        else
            loaded.textureArray[i] = { L'█', WORD(info[i] * 16 + info[i])};
    }

    return loaded;
}

vector<Texture> cAsset::assetLoaders(const vector<string> &textureList, const string& prefix)
{
    vector<Texture> multiFrame;
    for (string filename: textureList)
    {
        Texture a = cAsset::assetLoader(prefix + filename);
        multiFrame.push_back(a);
    }

    return multiFrame;
}

void cAsset::alphabetLoader()
{
    for (int i = 0; i < 26; i++)
    {
        char c = 'A' + i;
        string filepath = "Char//Alphabet//";
        filepath += c;
        filepath += ".txt";
        alphabet.push_back(assetLoader(filepath));
    }
}

void cAsset::numberLoader()
{
    for (int i = 0; i <= 9; i++)
    {
        number.push_back(assetLoader("Char//Number//" + to_string(i) + ".txt"));    
    }
}
