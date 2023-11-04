# pragma once
# include "Collider.hpp"

// 球体コライダーコンポーネント
class SphereCollider : public Collider
{
public:

	// コンストラクタ
	SphereCollider() = default;

	// デストラクタ
	virtual ~SphereCollider() = default;

	// 更新関数
	virtual void Update() override;

public:

	Sphere sphere = Sphere( Vec3(0,0,0), 1);
};
