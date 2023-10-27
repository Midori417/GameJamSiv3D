#pragma once
#include <Siv3D.hpp>

// 助ける人
class PersonHelp
{
private:

	// モデル
	Model model;

	// 位置
	Vec3 position;

	// 救われたかどうか
	bool isSave;

public:

	// コンストラクタ
	PersonHelp();

	// 更新関数
	void Update();

	// 描画関数
	void Draw();

};
