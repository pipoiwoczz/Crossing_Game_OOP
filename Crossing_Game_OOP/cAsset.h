#ifndef _CASSET_H
#define _CASSET_H
#include "setup.h"

class cAsset {
public:
    //ARTIST ZONE-----
    vector<wstring> sketch_Lion {
        L"▄▀▀▀▀▀───▄█▀▀▀█▄",
        L"▐▄▄▄▄▄▄▄▄██▌▀▄▀▐██",
        L"▐▒▒▒▒▒▒▒▒███▌▀▐███",
        L"▌▒▓▒▒▒▒▓▒██▌▀▐██",
        L"▌▓▐▀▀▀▀▌▓─▀▀▀▀▀"
    };
    vector<int> paddValue_Lion {1, 0, 0, 1, 1};
    TextureInfo color_Lion = { Color::yellow, Color::bright_white };
    //ARTIST ZONE-----

    
    

    vector<wstring> sketch_Rhino {
        L"▄  ▄ ▀█▄",
        L"▄████████▄██▄██▄██",
        L"█████████████▄████▌",
        L"▌████████████▀▀▀▀▀",
        L"▀ ▐█▄▐█▄▐█▄▐█▄"
    };
    vector<int> paddValue_Rhino { 12, 2, 2, 2, 1 };
    TextureInfo color_Rhino = { Color::green, Color::bright_white };


    

    vector<wstring> sketch_Crocodile {
        L"▄▄▄▄▄░▄░▄░▄░▄",
        L"▄▄▄▄██▄████▀█▀█▀█▀██▄",
        L"▀▄▀▄▀▄████▄█▄█▄█▄█████",
        L"▒▀▀▀▀▀▀▀▀██▀▀▀▀██▀▒▄██",
        L"▀▀▒▒▒▒▀▀▄▄██▀▒"
    };

    vector<int> paddValue_Crocodile { 5, 0, 0, 1, 8 };
    TextureInfo color_Crocodile = { Color::green, Color::bright_white };




    vector<wstring> sketch_Truck {
        L"──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▌",
        L"───▄▄██▌█░░░░░░░░░░░░▐",
        L"▄▄▄▌▐██▌█░░░░░░░░░░░░▐",
        L"███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▌",
        L"▀❍▀▀▀▀▀▀▀❍❍▀▀▀▀▀▀❍❍▀"
    };
    vector<int> paddValue_Truck { 0, 0, 0, 0, 0 };
    TextureInfo color_Truck = { Color::green , Color::bright_white };



    vector<wstring> sketch_Helicopter {
        L"▀▀▀▀█▀▀▀▀",
        L"─▄▀█▀▀█──────▄",
        L"█▄▄█▄▄██████▀",
        L"▀▀█▀▀▀█▀▀",
        L"─▀▀▀▀▀▀▀"
    };

    vector<int> paddValue_Helicopter { 0, 0, 0, 0, 0 };
    TextureInfo color_Helicopter = { Color::green, Color::bright_white };



    vector<wstring> sketch_Motorbike {
        L"───────────▀▄",
        L"──█▄▄▄▄▄███▀▄─▄▄",
        L"▄▀──▀▄─▀▀█▀▀▄▀──▀▄",
        L"▀▄▀▀█▀▀████─▀▄──▄▀",
        L"──▀▀──────────▀▀"
    };
    vector<int> paddValue_Motorbike { 0, 0, 0, 0, 0 };
    TextureInfo color_Motorbike = { Color::green, Color::bright_white };



    cAsset(int x);

    vector<vector<TextureInfo>> buildTexture(vector<wstring>& model, TextureInfo& colorCode);

    static vector<wstring> model_Lion;
    static vector<vector<TextureInfo>> texture_Lion;
    static vector<int> padding_Lion;

    static vector<wstring> model_Rhino;
    static vector<vector<TextureInfo>> texture_Rhino;
    static vector<int> padding_Rhino;

    static vector<wstring> model_Crocodile;
    static vector<vector<TextureInfo>> texture_Crocodile;
    static vector<int> padding_Crocodile;

    static vector<wstring> model_Truck;
    static vector<vector<TextureInfo>> texture_Truck;
    static vector<int> padding_Truck;

    static vector<wstring> model_Helicopter;
    static vector<vector<TextureInfo>> texture_Helicopter;
    static vector<int> padding_Helicopter;

    static vector<wstring> model_Motorbike;
    static vector<vector<TextureInfo>> texture_Motorbike;
    static vector<int> padding_Motorbike;

    static vector<wstring> getModel(AnimalIndex Aindex);
    static vector<wstring> getModel(VehicleIndex Vindex);
    static vector<int> getPadding(AnimalIndex Aindex);
    static vector<int> getPadding(VehicleIndex Vindex);
    static vector<vector<TextureInfo>> getTexture(AnimalIndex Aindex);
    static vector<vector<TextureInfo>> getTexture(VehicleIndex Vindex);
};
#endif
