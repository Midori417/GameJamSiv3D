#pragma once
#include "../System/MySystem.hpp"

// UFOコンポーネント
class UFO : public Component
{
public: 

	// コンストラクタ
	UFO() = default;

	// デストラクタ
	virtual ~UFO() = default;

	virtual void Awake() override
	{
		GetOwner()->position.x = Random(-StageW, StageW);
		GetOwner()->position.y = Random(-StageH, StageH);
		GetOwner()->position.z = Random(-StageD, StageD);

		startY = GetOwner()->position.y;
	}

	// コンポーネント更新関数
	virtual void Update() override;

private:

	/// 上下に揺らす
	void UpDown();

	/// 前方移動
	void Move();

public:

	// 上下運動の半径(移動幅)
	float radius = 0;

	// 上下運動の速度
	float upDownSpeed = 0;

	// 移動方向を変更するまでの間隔
	float rotateInterval = 1.0;

	// 移動速度の最大値
	float maxSpeed = 15;

private: 

	// UFOの初期位置(高さ)
	float startY;

	// 上下運動に使う角度
	float radian = 0;

	// 経過時間
	float timer = 0;

	// 方向別の移動速度
	Vec3 speed = { 0,0,0 };

	const int32 StageW = 200;
	const int32 StageH = 300;
	const int32 StageD = 200;

};

