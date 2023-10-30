#include "Application.hpp"
#include "Scene/Title.hpp"
#include "Scene/Play.hpp"
#include "Scene/Result.hpp"


void Application::Initilaze()
{
	// ウィンドウのサイズを変更
	Window::Resize(windowWidth, windowHigth);

	// シーンの追加
	sceneManager.add<Title>(SceneState::Title);
	sceneManager.add<Play>(SceneState::Play);
	sceneManager.add<Result>(SceneState::Result);
	//sceneManager.init(SceneState::Play);
}


void Application::Run()
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
