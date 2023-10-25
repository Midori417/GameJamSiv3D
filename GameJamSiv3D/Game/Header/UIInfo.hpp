#pragma once

#include <Siv3D.hpp>

class UIInfo
{
public:

	UIInfo()
		: font(FontMethod::SDF, 35, Typeface::Bold)

	{

	}

	void Update()
	{
		hpBarBack.setPos(20, 600 + 20);
		hpBarBack.setSize(200, 50);

		hpBar.setPos(21, 600 + 21);
		hpBar.setSize(198, 48);
	}

	// 描画
	void Draw() const
	{
		// HPBarBack
		hpBarBack.draw(Palette::Black);
		// HPBar
		hpBar.draw(Palette::Green);
		// Time
		font(txtTime).draw(TextStyle::Outline(0.5, Palette::Black), 10, 10);
		// Score
		font(txtScore).draw(TextStyle::Outline(0.5, Palette::Black), 700, 10);
	}

private:

	Rect hpBar;
	Rect hpBarBack;
	Font font;

	double time = 60;
	String txtTime = U"Time {}"_fmt(time);
	double score = 888888;
	String txtScore = U"Score {}"_fmt(score);
};
