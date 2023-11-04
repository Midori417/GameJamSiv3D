#include "GameClear.hpp"
#include "../System/MySystem.hpp"

GameClear::GameClear(const InitData& init)
	:IScene(init)
{
	auto mySystem = MySystem::GetInstance();

	auto backGround = mySystem->CreateUI<GameObject>(U"背景");
	auto textureDraw = backGround->AddComponent<TextureDraw>();
	textureDraw->texture = mySystem->GetTexture(U"GameClearBackGround");

	auto uiTime = mySystem->CreateUI<GameObject>(U"タイム");
	auto fontDraw = uiTime->AddComponent<FontDraw>();
	fontDraw->font = *mySystem->GetFont(U"Bold32");
	fontDraw->txt = U"救うのにかかった時間 {}"_fmt(getData().time);
	mySystem->GetAudio(U"GameClear")->play();
}

GameClear::~GameClear()
{
	auto mySystem = MySystem::GetInstance();

	// ゲームオブジェクトをすべて削除
	mySystem->AllClearGameObject();
	mySystem->GetAudio(U"GameClear")->stop();

}


void GameClear::update()
{
	if (MouseL.pressed())
	{

		changeScene(SceneState::Title);
	}
}
