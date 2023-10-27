#include "Title.hpp"

Title::Title(const InitData& init)
	:IScene(init)
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
}
