#include "Game.hpp"
#include "Scene/Title.hpp"
#include "Scene/Play.hpp"
#include "Scene/Result.hpp"

Game::Game()
{
}

void Game::Initilaze()
{
	// ウィンドウのサイズを変更
	Window::Resize(windowWidth, windowHigth);

	// シーンの追加
	sceneManager.add<Title>(SceneState::Title);
	sceneManager.add<Play>(SceneState::Play);
	sceneManager.add<Result>(SceneState::Result);	sceneManager.init(SceneState::Play);
}


void Game::Run()
{
	// ゲームを初期化
	Initilaze();

	// ループ処理
	while (System::Update())
	{
		if (not sceneManager.update())
		{
			break;
		}
	}
}
