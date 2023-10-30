#pragma once
#include <Siv3D.hpp>

// メテオ
class Meteo
{
private:

	// モデル
	Model model;

	// コライダー
	Sphere collider;

	// 位置
	Vec3 position;

	// 回転
	Quaternion rotation;

	// 速さ
	double speed;

	// 動く方向
	int32 moveDirection;


public:

	// コンストラクタ
	Meteo();

	// 更新関数
	void Update();

	// 描画関数
	void Draw();

	inline Sphere GetCollider() const
	{
		return collider;
	}
};
