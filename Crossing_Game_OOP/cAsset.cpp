#include "cAsset.h"

vector<wstring> cAsset::getModel(AnimalIndex Aindex) {
	switch (Aindex)
	{
	case AnimalIndex::Lion: return model_Lion;
		case AnimalIndex::Rhino: return model_Rhino;
		case AnimalIndex::Crocodile: return model_Crocodile;
	}
}
vector<wstring> cAsset::getModel(VehicleIndex Vindex) {
	switch (Vindex)
	{
		case VehicleIndex::Truck: return model_Truck;
		case VehicleIndex::Helicopter: return model_Helicopter;
		case VehicleIndex::Motorbike: return model_Motorbike;
	}
}
vector<int> cAsset::getPadding(AnimalIndex Aindex) {
	vector<int> paddValue;
	switch (Aindex)
	{
	case AnimalIndex::Lion: return padding_Lion;
	case AnimalIndex::Rhino: return padding_Rhino;
	case AnimalIndex::Crocodile: return padding_Crocodile;

	}
}
vector<int> cAsset::getPadding(VehicleIndex Vindex) {
	vector<int> paddValue;
	switch (Vindex)
	{
	case VehicleIndex::Truck: return padding_Truck;
	case VehicleIndex::Helicopter: return padding_Helicopter;
	case VehicleIndex::Motorbike: return padding_Motorbike;
	}
}
vector<vector<TextureInfo>> cAsset::getTexture(AnimalIndex Aindex)
{
	switch (Aindex)
	{
	case AnimalIndex::Lion: return texture_Lion;
	case AnimalIndex::Rhino: return texture_Rhino;
	case AnimalIndex::Crocodile: return texture_Crocodile;
	}
}
vector<vector<TextureInfo>> cAsset::getTexture(VehicleIndex Vindex)
{
	switch (Vindex)
	{
	case VehicleIndex::Truck: return texture_Truck;
	case VehicleIndex::Helicopter: return texture_Helicopter;
	case VehicleIndex::Motorbike: return texture_Motorbike;
	}
}

vector<vector<TextureInfo>> cAsset::buildTexture(vector<wstring> &model, TextureInfo &colorCode)
{
	vector<vector<TextureInfo>> texture(model.size());
	for (int i = 0; i < texture.size(); i++)
	{
		vector<TextureInfo> temp(model[i].length(), colorCode);
		texture[i] = temp;
	}
	return texture;
}

cAsset::cAsset(int x)
{
	model_Lion = sketch_Lion;
	model_Rhino = sketch_Rhino;
	model_Crocodile = sketch_Crocodile;
	model_Truck = sketch_Truck;
	model_Helicopter = sketch_Helicopter;
	model_Motorbike = sketch_Motorbike;

	texture_Lion = buildTexture(model_Lion, color_Lion);
	texture_Rhino = buildTexture(model_Rhino, color_Rhino);
	texture_Crocodile = buildTexture(model_Crocodile, color_Crocodile);
	texture_Truck = buildTexture(model_Truck, color_Truck);
	texture_Helicopter = buildTexture(model_Helicopter, color_Helicopter);
	texture_Motorbike = buildTexture(model_Motorbike, color_Motorbike);

	padding_Lion = paddValue_Lion;
	padding_Rhino = paddValue_Rhino;
	padding_Crocodile = paddValue_Crocodile;
	padding_Truck = paddValue_Truck;
	padding_Helicopter = paddValue_Helicopter;
	padding_Motorbike = paddValue_Motorbike;
}