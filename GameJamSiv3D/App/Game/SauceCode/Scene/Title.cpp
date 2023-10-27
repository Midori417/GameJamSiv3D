#include "Title.hpp"

Title::Title(const InitData& init)
	:IScene(init)
	, font(64, Typeface::Bold)

{
}

void Title::update()
{
	if (MouseL.down())
	{
		// ゲームシーンに遷移
		changeScene(SceneState::Play);
	}
}

void Title::draw() const
{
	// 背景色
	Scene::SetBackground(Palette::Skyblue);

	font(U"宇宙レスキュー").drawAt(640, 360 - 20);
	font(U"左クリックで開始").drawAt(640, 360+100);
}
