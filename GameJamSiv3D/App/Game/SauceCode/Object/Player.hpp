#pragma once
#include <Siv3D.hpp>

// プレイヤー
class Player
{
private:

	// メッシュ
	const Model model;

	// 当たり判定
	Sphere sphereCollider;

	// 位置
	Vec3 position;

	// 回転
	Quaternion rotation;
	double rotationY;

	// 移動速度
	int16 speed;
	const int16 defaltSpeed = 6;
	const int16 dashSpeed = 8;

	// HP
	int16 hp;
	const int16 hpMax = 3;

	bool isMuteki;
	double mutekiTime;

	// 助けた人の数
	int32 personHelp;

	// カメラ
	std::shared_ptr<BasicCamera3D> camera;

	// エフェクト
	const Mesh effectMesh;
	const Texture effectTexture;
	Effect effect3D;

public:

	// コンストラクタ
	Player();

	// 更新関数
	void Update();

	// 描画関数
	void Draw() const;
	void EffectDraw() const;

	inline Vec3 GetPos()
	{
		return position;
	}
	inline Quaternion GetQuaternion()
	{
		return rotation;
	}

	inline int16 GetHP()
	{
		return hp;
	}
	inline void HPDown()
	{
		if (!isMuteki)
		{
			hp--;
			mutekiTime = 3;
			isMuteki = true;
		}
	}

	inline void SetCamera(std::shared_ptr<BasicCamera3D> _camera)
	{
		camera = _camera;
	}

	inline Sphere GetCollider()
	{
		return sphereCollider;
	}
};
