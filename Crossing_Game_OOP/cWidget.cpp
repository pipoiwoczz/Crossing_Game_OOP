#include "cWidget.h"
#include "gameEngine.h"
#include "Map.h"



cWidget::cWidget(cWidget* parent, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc)
{
	if (!parent)
		return;
	offset = offsetFromParentTopleft;
	IsVisible = false;
	tag = tagName;

	this->parentWindow = parent;
	topleft = { short(parentWindow->topleft.X + offset.X), short(parentWindow->topleft.Y + offset.Y) };
	topleft = { max(topleft.X, parentWindow->topleft.X), max(topleft.Y, parentWindow->topleft.Y) };


	if (imgSrc.length() !=0)
	{
		WidgetFace = cAsset::assetLoader(UIPrefix + imgSrc);

		botright = { short(topleft.X + WidgetFace.getWidth() - 1), short(topleft.Y + WidgetFace.getHeight() - 1) };
		botright = { min(botright.X, parentWindow->botright.X), min(botright.Y, parentWindow->botright.Y) };
	}
}

bool cWidget::createMainWindow(const string& tagName)
{
	if (!hasWd) {
		hasWd = true;
		window.IsVisible = true;
		window.topleft = { My_Windows.Left, My_Windows.Top };
		window.botright = { My_Windows.Right, My_Windows.Bottom };
		window.tag = tagName;
		window.parentWindow = nullptr;
		window.WidgetFace = cAsset::assetLoader(UIPrefix + "mainWD.txt");
	}
	return true;
}

void cWidget::setPos(COORD In_topleft)
{
	offset = In_topleft;
	topleft = { short(parentWindow->topleft.X + offset.X), short(parentWindow->topleft.Y + offset.Y) };
	topleft = { max(topleft.X, parentWindow->topleft.X), max(topleft.Y, parentWindow->topleft.Y) };

	botright = { short(topleft.X + WidgetFace.getWidth() - 1), short(topleft.Y + WidgetFace.getHeight() - 1) };
	botright = { min(botright.X, parentWindow->botright.X), min(botright.Y, parentWindow->botright.Y) };
}
COORD cWidget::getPos()
{
	return offset;
}

bool cWidget::show(bool showNow)
{
	IsVisible = true;
	return cGameEngine::showWidget(this, showNow);
}

bool cWidget::unshow(bool showNow)
{
	IsVisible = false;
	return cGameEngine::unshowWidget(this, showNow);
}

cDWindow::cDWindow(cWidget* parent, COORD Topleft, const string& tagName, const string& imgSrc, bool showNow) : cWidget(parent, Topleft, tagName, imgSrc)
{
	if (showNow)
		show();
}
cDWindow::cDWindow(cDWindow* parent, COORD Topleft, const string& tagName, const string& imgSrc, bool showNow) : cWidget(static_cast<cWidget*> (parent), Topleft, tagName, imgSrc)
{
	if (showNow)
		show();
}

bool cDWindow::show(bool showNow)
{
	return cWidget::show(showNow);
}

bool cDWindow::unshow(bool showNow)
{
	return cWidget::unshow(showNow);
}


cButton::cButton(cDWindow* parent, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc, short borderDensity, void (*pFunction) ()) : cWidget(static_cast<cWidget*> (parent), offsetFromParentTopleft, tagName, imgSrc)
{
	bordDensity = borderDensity;
	
	OTopleft = { short(topleft.X - 2 * bordDensity), short(topleft.Y - bordDensity) };
	OTopleft = { max(OTopleft.X, parentWindow->topleft.X), max(OTopleft.Y, parentWindow->topleft.Y)};
	OBotright = { short(topleft.X + WidgetFace.getWidth() + 2* bordDensity - 1), short(topleft.Y + WidgetFace.getHeight() + bordDensity - 1)};
	OBotright = { min(OBotright.X, parentWindow->botright.X), min(OBotright.Y, parentWindow->botright.Y) };
	buttonFunction = pFunction;
}

cButton::cButton(cDWindow* parent, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc, short borderDensity, void(*pFunction)(cGame*)) : cWidget(static_cast<cWidget*> (parent), offsetFromParentTopleft, tagName, imgSrc)
{
	bordDensity = borderDensity;
	OTopleft = { short(topleft.X - 2 * bordDensity), short(topleft.Y - bordDensity) };
	OTopleft = { max(OTopleft.X, parentWindow->topleft.X), max(OTopleft.Y, parentWindow->topleft.Y) };
	OBotright = { short(topleft.X + WidgetFace.getWidth() + 2 * bordDensity - 1), short(topleft.Y + WidgetFace.getHeight() + bordDensity - 1) };
	OBotright = { min(OBotright.X, parentWindow->botright.X), min(OBotright.Y, parentWindow->botright.Y) };
	buttonFunction2 = pFunction;
	buttonFunction = nullptr;
}


bool cButton::show(bool showNow)
{
	return cWidget::show(showNow);
}

bool cButton::unshow(bool showNow)
{
	return cWidget::unshow(showNow);
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
	if (buttonFunction2)
		buttonFunction2(&cGameEngine::pGame);
	else if (buttonFunction)
		buttonFunction();
}

void cButton::highLight(bool showNow)
{
	cGameEngine::HighLightButton(this, showNow);
}

void cButton::unHighLight(bool showNow)
{
	cGameEngine::UnHighLightButton(this, showNow);
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
		Texture* pChar = cAsset::getChar(text[i]);
		if (text[i] == ' ')
		{
			pChar = &cAsset::blankchar;
			offset = 5 + align;
		}
		else {
			pChar = cAsset::getChar(text[i]);
			if (pChar)
			{
				offset = pChar->getWidth() + align;
			}
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
	botright = { short(topleft.X + length - 1), short(topleft.Y + textLine[0].pChar->getHeight() - 1)};
	botright = { min(botright.X, parentWindow->botright.X), min(botright.Y, parentWindow->botright.Y) };
}

cLabel::cLabel(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& text, const short& align, Color textColor)
{
	this->parentWindow = static_cast<cWidget*> (parentWindow);
	IsVisible = false;
	tag = tagName;
	this->text = text;
	color = short(textColor);
	this->align = align;
	offset = offsetFromParentTopleft;
	topleft = { short(parentWindow->topleft.X + offsetFromParentTopleft.X), short(parentWindow->topleft.Y + offsetFromParentTopleft.Y) };
	topleft = { max(topleft.X, parentWindow->topleft.X), max(topleft.Y, parentWindow->topleft.Y) };
	createTextline();
}

cLabel::cLabel(cButton* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const string& text, const short& align, Color textColor)
{
	this->parentWindow = static_cast<cWidget*> (parentWindow);
	IsVisible = false;
	tag = tagName;
	this->text = text;
	color = short(textColor);
	this->align = align;
	offset = offsetFromParentTopleft;
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

bool cLabel::show(bool showNow)
{
	if (textLine.size() == 0)
		return false;
	IsVisible = true;
	return cGameEngine::showLabel(this, showNow);
}

bool cLabel::unshow(bool showNow)
{
	if (textLine.size() == 0)
		return false;
	IsVisible = false;
	return cGameEngine::unshowLabel(this, showNow);
}

cBar::cBar(cDWindow* parentWindow, COORD offsetFromParentTopleft, const string& tagName, const short& length, const short& width, Color barColor, Color BarBGColor)
{
	this->parentWindow = static_cast<cWidget*> (parentWindow);
	IsVisible = false;
	tag = tagName;
	this->length = length;
	this->width = width;
	currentFill = 0;
	forecolor = short(barColor);
	backcolor = short(BarBGColor);

	offset = offsetFromParentTopleft;

	topleft = { short(parentWindow->topleft.X + offsetFromParentTopleft.X), short(parentWindow->topleft.Y + offsetFromParentTopleft.Y) };
	topleft = { max(topleft.X, parentWindow->topleft.X), max(topleft.Y, parentWindow->topleft.Y) };
	botright = { short(topleft.X + length * width - 1), short(topleft.Y + width - 1) };
	botright = { min(botright.X, parentWindow->botright.X), min(botright.Y, parentWindow->botright.Y) };

}


bool cBar::show(bool showNow)
{
	return cGameEngine::showBar(this, showNow);
}

bool cBar::unshow(bool showNow)
{
	return cGameEngine::unshowBar(this, showNow);
}

bool cBar::setProgress(bool autoRun, short percentage, bool showNow)
{
	if (autoRun)
	{
		for (short i = 1; i <= length; i++)
		{
			currentFill = i;
			show(showNow);
			Sleep(150);
		}
	}
	else {
		currentFill = percentage * length / 100;
		if (showNow)
		{
			unshow();
			show();
		}
	}
	return true;
}
