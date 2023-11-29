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
		WidgetFace = cAsset::assetLoader(ButtonPrefix + imgSrc);

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
		window.WidgetFace.textureArray = nullptr;
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

void cWidget::show(bool showNow)
{
	IsVisible = true;
	cGameEngine::showWidget(this, showNow);
}

void cWidget::unshow(bool showNow)
{
	IsVisible = false;
	cGameEngine::unshowWidget(this, showNow);
}
void cWidget::reset(bool showNow)
{
	show(showNow);
}

cDWindow::cDWindow(cWidget* parent, COORD Topleft, const string& tagName, const string& imgSrc) : cWidget(parent, Topleft, tagName, imgSrc) {}
cDWindow::cDWindow(cDWindow* parent, COORD Topleft, const string& tagName, const string& imgSrc) : cWidget(static_cast<cWidget*> (parent), Topleft, tagName, imgSrc) {}

void cDWindow::show(bool showNow)
{
	cWidget::show(showNow);
}

void cDWindow::unshow(bool showNow)
{
	cWidget::unshow(showNow);
}


cButton::cButton(cDWindow* parent, COORD offsetFromParentTopleft, const string& tagName, const string& imgSrc, short borderDensity, void (*pFunction) (void)) : cWidget(static_cast<cWidget*> (parent), offsetFromParentTopleft, tagName, imgSrc)
{
	bordDensity = borderDensity;
	
	OTopleft = { short(topleft.X - 2 * bordDensity), short(topleft.Y - bordDensity) };
	OTopleft = { max(OTopleft.X, parentWindow->topleft.X), max(OTopleft.Y, parentWindow->topleft.Y)};
	OBotright = { short(topleft.X + WidgetFace.getWidth() + 2* bordDensity - 1), short(topleft.Y + WidgetFace.getHeight() + bordDensity - 1)};
	OBotright = { min(OBotright.X, parentWindow->botright.X), min(OBotright.Y, parentWindow->botright.Y) };
	buttonFunction = pFunction;
}

void cButton::show(bool showNow)
{
	cWidget::show(showNow);
}

void cButton::unshow(bool showNow)
{
	cWidget::unshow(showNow);
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

void cLabel::show(bool showNow)
{
	if (textLine.size() == 0)
		return;
	IsVisible = true;
	cGameEngine::showLabel(this, showNow);
}

void cLabel::unshow(bool showNow)
{
	if (textLine.size() == 0)
		return;
	IsVisible = false;
	cGameEngine::unshowLabel(this, showNow);
}


