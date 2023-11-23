#include "cWidget.h"
#include "cAsset.h"
cWidget::cWidget(COORD In_topleft, int borderDensity)
{
	bordDensity = borderDensity;
	topleft = In_topleft;
	OTopleft = {short(In_topleft.X - 2 * bordDensity), short(In_topleft.Y - bordDensity)};
}

cButton::cButton(COORD In_topleft, int borderDensity, void (*pFunction) (void)) : cWidget(In_topleft, borderDensity)
{
	buttonFunction = pFunction;
	textures.push_back(cAsset::assetLoader("Sprites//button.txt"));
	pTexture = &textures[0];
}

void cButton::onSelect()
{

}

void cButton::onDeSelect()
{

}

void cButton::onEnter()
{
	buttonFunction();
}

void cButton::cleanButton(HANDLE curHandle)
{
	short ow = pTexture->getWidth() + 4 * bordDensity;
	short oh = pTexture->getHeight() + 2 * bordDensity;
	SMALL_RECT outerRect = { OTopleft.X, OTopleft.Y, OTopleft.X + ow - 1, OTopleft.Y + oh - 1 };
	CHAR_INFO* OuterBuffer = new CHAR_INFO[ow * oh];

	for (int i = 0; i < ow * oh; i++)
	{
		OuterBuffer[i].Char.UnicodeChar = L' ';
		OuterBuffer[i].Attributes = 16 * 15 + 15;
	}

	WriteConsoleOutput(curHandle, OuterBuffer, { ow , oh }, { 0, 0 }, &outerRect);
	SetConsoleActiveScreenBuffer(curHandle);
	delete[]OuterBuffer;
}

void cButton::drawButton(HANDLE curHandle)
{
	SMALL_RECT innerRect = { topleft.X, topleft.Y, topleft.X + pTexture->getWidth() - 1, topleft.Y + pTexture->getHeight() - 1 };
	WriteConsoleOutput(curHandle, pTexture->textureArray, { pTexture->getWidth(), pTexture->getHeight() }, { 0,0 }, &innerRect);
	SetConsoleActiveScreenBuffer(curHandle);
}

void cButton::drawBorder(HANDLE curHandle)
{
	short ow = pTexture->getWidth() + 4 * bordDensity;
	short oh = pTexture->getHeight() + 2 * bordDensity;
	CHAR_INFO* OuterBuffer = new CHAR_INFO[ow * oh];
	SMALL_RECT outerRect = { OTopleft.X, OTopleft.Y, OTopleft.X + ow - 1, OTopleft.Y + oh - 1 };

	for (int i = 0; i < ow * oh; i++)
	{
		OuterBuffer[i].Char.UnicodeChar = L' ';
		OuterBuffer[i].Attributes = 16 * 4 + 4;
	}


	WriteConsoleOutput(curHandle, OuterBuffer, { ow , oh }, { 0, 0 }, &outerRect);
	SetConsoleActiveScreenBuffer(curHandle);
	drawButton(curHandle);
	delete[]OuterBuffer;
}