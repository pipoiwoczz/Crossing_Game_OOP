#include "cAsset.h"
#include "Sound.h"


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

Texture cAsset::assetLoader(string filename, const string& prefix)
{
    ifstream inGate;
    inGate.open("Sprites//" + prefix + filename + ".txt");
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
                    CHAR_INFO t = { L'█', WORD(16*x + x) };
                    loaded.textureArray[i * loaded.width + j] = t;

                }
                else {
                    CHAR_INFO t = { L' ', WORD(0)};
                    loaded.textureArray[i * loaded.width + j] = t;
                }
            }
        }
    }
    inGate.close();
    return loaded;
}

// binary loader
Texture cAsset::loader(string filename)
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
    delete[]info;
    return loaded;
}

vector<Texture> cAsset::assetLoaders(const vector<string> &textureList, const string& prefix)
{
    vector<Texture> multiFrame;
    for (string filename: textureList)
    {
        Texture a = cAsset::assetLoader(filename, prefix);
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
        alphabet.push_back(assetLoader(filepath));
    }
}

void cAsset::numberLoader()
{
    for (int i = 0; i <= 9; i++)
    {
        number.push_back(assetLoader("Char//Number//" + to_string(i)));    
    }
}
void cAsset::specialCharLoader()
{
    for (int i = 1; i < 10   ; i++)
    {
        special.push_back(assetLoader("Char//Special//sc" + to_string(i)));
    }
}
void cAsset::settingsLoader()
{
    ifstream settingIn;
    settingIn.open("Settings.txt");
    if (settingIn.is_open())
    {
        int value;
        settingIn >> value;
        Sound::setBGVolume(value);
        settingIn >> value;
        Sound::setEffectVolume(value);
    }
    settingIn.close();
}
void cAsset::settingSave()
{
    ofstream saveIn;
    saveIn.open("Settings.txt");
    saveIn << Sound::getCurrentMusicVolume() << endl;
    saveIn << Sound::getCurrentEffectVolume() << endl;
    saveIn.close();
}

Texture* cAsset::getChar(unsigned char In_char)
{
    if (toupper(In_char) >= 'A' && toupper(In_char) <= 'Z')
        return &alphabet[toupper(In_char) - 'A'];
    if (In_char >= '0' && In_char <= '9')
        return &number[In_char - '0'];
    switch (In_char)
    {
        case '%': return &special[0];
        case ':': return &special[1];
        case '<': return &special[2];
        case '>': return &special[3];
        case '=': return &special[4];
        case '+': return &special[5];
        case '-': return &special[6];
        case '\0': return &special[7];
        case '?': return &special[8];
    default:
        break;
    }
    return nullptr;
}
