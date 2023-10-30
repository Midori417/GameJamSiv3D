#pragma once
#include "Scene/Common.hpp"

// ゲームクラス
class Application
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
	Application() = default;

	// 初期化関数
	void Initilaze();

	// 実行関数
	void Run();
};
