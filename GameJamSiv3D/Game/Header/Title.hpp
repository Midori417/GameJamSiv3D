#pragma once

#include "Common.hpp"
#include "Button.hpp"

/// @brief タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init)
		: IScene(init)
		, font(FontMethod::MSDF, 48, Typeface::Bold)
	{
	}

	~Title()
	{
	}

	void Initialzie()
	{

	}

	void update() override
	{

		font(U"宇宙救助").draw(100, 300, 200, Palette::White);
		if (Button(Rect(350, 500, 300, 100), font, U"スタート"))
		{
			changeScene(State::Game);
		}
	}
	void draw() const override
	{
		Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
		FontAsset(U"TitileFont")(U"My Game").drawAt(400, 100);
		Circle(Cursor::Pos(), 50).draw(Palette::Orange);
	}

private:

	Font font;
};
