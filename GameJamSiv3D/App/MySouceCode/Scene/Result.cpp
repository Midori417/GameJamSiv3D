#include "Result.hpp"

Result::Result(const InitData& init)
	:IScene(init)
	, font(64, Typeface::Bold)

{
}

void Result::update()
{
	if (MouseL.down())
	{
		// ゲームシーンに遷移
		changeScene(SceneState::Title);
	}

}

void Result::draw() const
{
	// 背景色
	Scene::SetBackground(Palette::Green);
	font(U"リザルト").drawAt(640, 360 - 20);
	font(U"左クリックでタイトル").drawAt(640, 360 + 100);

}
