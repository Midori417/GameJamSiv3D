#pragma once
#include "Common.hpp"
#include "GameObject.hpp"

// ゲームクラス
class Game
{
private:

	// ウィンドウの幅
	const int32 windowWidth = 1280;
	// ウィンドウの高さ
	const int32 windowHigth = 720;

	// シーンマネージャー
	App sceneManager;


public:

	// コンストラクタ
	Game();

	// 初期化関数
	void Initilaze();

	// 実行関数
	void Run();
};
