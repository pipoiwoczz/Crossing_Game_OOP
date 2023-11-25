#include "cWidget.h"
#include "gameEngine.h"
#include "Map.h"



cWidget::cWidget(cWidget* parent, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc)
{
	if (!parent)
		return;
	IsVisible = false;
	pHandle = &cGameEngine::curHandle;
	tag = tagName;

	this->parentWindow = parent;
	topleft = { short(parentWindow->topleft.X + offsetFromParentTopleft.X), short(parentWindow->topleft.Y + offsetFromParentTopleft.Y) };
	topleft = { max(topleft.X, parentWindow->topleft.X), max(topleft.Y, parentWindow->topleft.Y) };


	if (imgSrc.length() !=0)
	{
		WidgetFace = cAsset::assetLoader(imgSrc);
		short W = WidgetFace.getWidth();
		short H = WidgetFace.getHeight();

		botright = { short(topleft.X + W - 1), short(topleft.Y + H - 1) };
		botright = { min(botright.X, parentWindow->botright.X), min(botright.Y, parentWindow->botright.Y) };
	}
}

bool cWidget::createMainWindow(const string& tagName)
{
	if (!hasWd) {
		hasWd = true;
		window.IsVisible = true;
		window.pHandle = &cGameEngine::curHandle;
		window.topleft = { My_Windows.Left, My_Windows.Top };
		window.botright = { My_Windows.Right, My_Windows.Bottom };
		window.tag = tagName;
		window.parentWindow = nullptr;
	}
	return true;
}

void cWidget::show()
{
	IsVisible = true;
	SMALL_RECT region = { topleft.X, topleft.Y, botright.X, botright.Y };
	WriteConsoleOutput(*pHandle, WidgetFace.textureArray, { WidgetFace.getWidth(), WidgetFace.getHeight() }, { 0,0 }, &region);
	SetConsoleActiveScreenBuffer(*pHandle);	
}

void cWidget::unshow()
{
	IsVisible = false;
	COORD erasepos = { topleft.X - parentWindow->topleft.X, topleft.Y - parentWindow->topleft.Y };
	SMALL_RECT region = { topleft.X, topleft.Y, botright.X, botright.Y };
	short W = WidgetFace.getWidth();
	short H = WidgetFace.getHeight();

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = parentWindow->WidgetFace.textureArray[(erasepos.Y + i / W) * parentWindow->WidgetFace.getWidth() + erasepos.X - parentWindow->topleft.X + i % W].Attributes;
	}
	WriteConsoleOutput(cGameEngine::curHandle, cGameEngine::reservedBuffer, { W, H }, { 0, 0 }, &region);
	SetConsoleActiveScreenBuffer(*pHandle);
}


cDWindow::cDWindow(cWidget* parent, COORD Topleft, const string& tagName, const string& imgSrc) : cWidget(parent, Topleft, tagName, imgSrc) {}
cDWindow::cDWindow(cDWindow* parent, COORD Topleft, const string& tagName, const string& imgSrc) : cWidget(static_cast<cWidget*> (parent), Topleft, tagName, imgSrc) {}


void cDWindow::show()
{
	cWidget::show();
}

void cDWindow::unshow()
{
	cWidget::unshow();
}


cButton::cButton(cDWindow* parent, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc, int borderDensity, void (*pFunction) (void)) : cWidget(static_cast<cWidget*> (parent), offsetFromParentTopleft, tagName, imgSrc)
{
	bordDensity = borderDensity;
	
	OTopleft = { short(topleft.X - 2 * bordDensity), short(topleft.Y - bordDensity) };
	OTopleft = { max(OTopleft.X, parentWindow->topleft.X), max(OTopleft.Y, parentWindow->topleft.Y)};
	OBotright = { short(topleft.X + WidgetFace.getWidth() + 2* bordDensity - 1), short(topleft.Y + WidgetFace.getHeight() + bordDensity - 1)};
	OBotright = { min(OBotright.X, parentWindow->botright.X), min(OBotright.Y, parentWindow->botright.Y) };
	buttonFunction = pFunction;
}

void cButton::show()
{
	cWidget::show();
}

void cButton::unshow()
{
	cWidget::unshow();
}

void cButton::onSelect()
{
	highLight();
}

void cButton::onDeSelect()
{
	unHighLight();
}

void cButton::onEnter()
{
	Sleep(200);
	buttonFunction();
}

void cButton::highLight()
{
	short ow = OBotright.X - OTopleft.X + 1;
	short oh = OBotright.Y - OTopleft.Y + 1;
	SMALL_RECT outerRect = { OTopleft.X, OTopleft.Y, OBotright.X, OBotright.Y };

	for (int i = 0; i < ow * oh; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = 16 * 4 + 4;
	}

	WriteConsoleOutput(*pHandle, cGameEngine::reservedBuffer, { ow , oh }, { 0, 0 }, &outerRect);
	cWidget::show();
}

void cButton::unHighLight()
{
	COORD erasepos = { OTopleft.X - parentWindow->topleft.X, OTopleft.Y - parentWindow->topleft.Y };

	short ow = OBotright.X - OTopleft.X + 1;
	short oh = OBotright.Y - OTopleft.Y + 1;
	SMALL_RECT outerRect = { OTopleft.X, OTopleft.Y, OBotright.X, OBotright.Y };

	for (int i = 0; i < ow * oh; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = parentWindow->WidgetFace.textureArray[(erasepos.Y + i / ow) * parentWindow->WidgetFace.getWidth() + erasepos.X + i % ow].Attributes;
	}

	WriteConsoleOutput(*pHandle, cGameEngine::reservedBuffer, { ow , oh }, { 0, 0 }, &outerRect);
	show();
}


void cLabel::createTextline()
{
	if (text.length() == 0)
		return;
	textLine.clear();
	int offset = 0;
	int length = 0;
	COORD pos = { topleft.X - parentWindow->topleft.X, topleft.Y - parentWindow->topleft.Y};
	for (int i = 0; i < text.length(); i++)
	{
		Texture* pChar = nullptr;
		if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
		{
			pChar = &cAsset::alphabet[toupper(text[i]) - 'A'];
			offset = pChar->getWidth() + align;

		}
		else if (text[i] >= '0' && text[i] <= '9')
		{
			pChar = &cAsset::number[text[i] - '0'];
			offset = pChar->getWidth() + align;
		}
		else if (text[i] == ' ')
		{
			pChar = &cAsset::blankchar;
			
			offset = 5 + align;

		}
		if (pChar)
		{
			textLine.push_back({ pChar, pos });
			pos.X += offset;
			length += offset;
		}
	}
	if (offset == 0)
		return;
	botright = { short(min(topleft.X + length - 1, parentWindow->botright.X)), short(min(topleft.Y + textLine[0].pChar->getHeight() - 1, parentWindow->botright.Y))};
}

cLabel::cLabel(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& text, const short& align, Color textColor)
{
	this->parentWindow = static_cast<cWidget*> (parentWindow);
	IsVisible = false;
	pHandle = &cGameEngine::curHandle;
	tag = tagName;
	this->text = text;
	color = short(textColor);
	this->align = align;
	topleft = { short(parentWindow->topleft.X + offsetFromParentTopleft.X), short(parentWindow->topleft.Y + offsetFromParentTopleft.Y) };
	topleft = { max(topleft.X, parentWindow->topleft.X), max(topleft.Y, parentWindow->topleft.Y) };
	createTextline();
}

void cLabel::updateText(const string& newText)
{
	unshow();
	text = newText;
	createTextline();
	show();
}

void cLabel::show()
{
	if (textLine.size() == 0)
		return;
	IsVisible = true;
	for (int i = 0; i < textLine.size(); i++)
	{
		if (textLine[i].pos.X > botright.X - textLine[i].pChar->getWidth())
			break;
		short iw = textLine[i].pChar->getWidth();
		short ih = textLine[i].pChar->getHeight();
		SMALL_RECT charBox = {parentWindow->topleft.X + textLine[i].pos.X, parentWindow->topleft.Y + textLine[i].pos.Y, parentWindow->topleft.X + textLine[i].pos.X + iw - 1, parentWindow->topleft.X + textLine[i].pos.Y + ih - 1};
		memcpy(cGameEngine::reservedBuffer, textLine[i].pChar->textureArray, iw * ih * sizeof(CHAR_INFO));
		for (int j = 0; j < iw * ih; j++)
		{
			if (textLine[i].pChar->textureArray[j].Char.UnicodeChar != L' ')
			{
				cGameEngine::reservedBuffer[j].Attributes = 16 * color + color;
			}
			else {
				cGameEngine::reservedBuffer[j].Attributes = parentWindow->WidgetFace.textureArray[(textLine[i].pos.Y + j / iw) * parentWindow->WidgetFace.getWidth() + textLine[i].pos.X + j % iw].Attributes;
			}
		}

		WriteConsoleOutput(cGameEngine::curHandle, cGameEngine::reservedBuffer, {iw, ih}, {0,0}, &charBox);
		SetConsoleActiveScreenBuffer(cGameEngine::curHandle);
	}
}

void cLabel::unshow()
{
	if (textLine.size() == 0)
		return;
	IsVisible = false;
	COORD erasepos = { topleft.X - parentWindow->topleft.X, topleft.Y - parentWindow->topleft.Y };
	SMALL_RECT region = { topleft.X, topleft.Y, botright.X, botright.Y };
	short W = botright.X - topleft.X + 1;
	short H = botright.Y - topleft.Y + 1;

	for (int i = 0; i < W * H; i++)
	{
		cGameEngine::reservedBuffer[i].Attributes = parentWindow->WidgetFace.textureArray[(erasepos.Y + i / W) * parentWindow->WidgetFace.getWidth() + erasepos.X + i % W].Attributes;
	}
	WriteConsoleOutput(cGameEngine::curHandle, cGameEngine::reservedBuffer, { W, H }, { 0, 0 }, &region);
	SetConsoleActiveScreenBuffer(*pHandle);
}

