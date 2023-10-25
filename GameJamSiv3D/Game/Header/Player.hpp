#pragma once
#include <Siv3D.hpp>

class Player
{
public:

	// コンストラクタ
	Player();

	// 更新関数
	void Update();

	// 描画関数
	void Draw() const;

private:

	// 移動関数
	void Move();

private:

	// モデル
	const Model roket;

	// 位置
	Vec3 pos;

	// 移動速度
	const double speed = 2;
};
