#pragma once
#include <Siv3D.hpp>

bool Button(const Rect& rect, const Font& font, const String& text)
{
	if (rect.mouseOver())
	{
		rect.draw(ColorF(0.3, 0.5, 0.9, 0.8));
		rect.drawFrame(2, 2, ColorF(0.5, 0.7, 1.0));
	}
	else
	{
		rect.draw(ColorF(0.3, 0.5, 0.9, 0.2));
		rect.drawFrame(2, 2, ColorF(0.5, 0.7, 1.0));
	}

	font(text).draw(30, rect.x + 100, rect.y + 15, Palette::White);
	return rect.leftClicked();
}
