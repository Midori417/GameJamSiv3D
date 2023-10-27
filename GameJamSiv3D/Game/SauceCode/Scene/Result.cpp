#include "Result.hpp"

Result::Result(const InitData& init)
	:IScene(init)
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
	Scene::SetBackground(Palette::White);

}
