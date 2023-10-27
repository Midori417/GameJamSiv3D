#pragma once
#include <Siv3D.hpp>

// 助ける人
class PersonHelp
{
private:

	// モデル
	Model model;

	Sphere collider;

	// 位置
	Vec3 position;

	// 回転
	Quaternion rotation;

	// 救われたかどうか
	bool isSave;


public:

	// コンストラクタ
	PersonHelp();

	// 更新関数
	void Update();

	// 描画関数
	void Draw() const;

	inline bool IsSave()
	{
		return isSave;
	}

	inline void SaveOk()
	{
		isSave = true;
	}

	inline Sphere GetCollider()
	{
		return collider;
	}
};
