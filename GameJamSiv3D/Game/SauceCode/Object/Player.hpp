#pragma once
#include <Siv3D.hpp>

// プレイヤー
class Player
{
private:

	// メッシュ
	const Model model;

	// 位置
	Vec3 position;

	// 回転
	Quaternion rotation;
	double rotationY;

	// 移動速度
	int16 speed;
	const int16 defaltSpeed = 4;
	const int16 dashSpeed = 6;

	// HP
	int16 hp;
	const int16 hpMax = 3;


public:

	// コンストラクタ
	Player();

	// 更新関数
	void Update();

	// 描画関数
	void Draw();

	inline Vec3 GetPos()
	{
		return position;
	}
	inline Quaternion GetQuaternion()
	{
		return rotation;
	}
};
