#pragma once
#include <Siv3D.hpp>
#include "Object.h"

/// @brief アプリケーションクラス
class Application
{
private:

	// オブジェクト配列
	ObjectList objects;

public:

	// アプリの実行関数
	int32 Run();

private:

	// アプリの初期化関数
	int32 Initialize();

	// アプリの更新関数
	void Update();

	// オブジェクトの破壊関数
	void DestoryGameObject();
};
