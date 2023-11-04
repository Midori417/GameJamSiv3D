#include "GameOver.hpp"
#include "../System/MySystem.hpp"

GameOver::GameOver(const InitData& init)
	:IScene(init)
{
	auto mySystem = MySystem::GetInstance();

	auto backGround = mySystem->CreateUI<GameObject>(U"背景");
	auto textureDraw = backGround->AddComponent<TextureDraw>();
	textureDraw->texture = mySystem->GetTexture(U"GameOverBackGround");
	mySystem->GetAudio(U"GameOver")->play();
}

GameOver::~GameOver()
{
	auto mySystem = MySystem::GetInstance();

	// ゲームオブジェクトをすべて削除
	mySystem->AllClearGameObject();
	mySystem->GetAudio(U"GameOver")->stop();


}

void GameOver::update()
{
	if (MouseL.pressed())
	{

		changeScene(SceneState::Title);
	}
}
