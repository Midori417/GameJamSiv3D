#pragma once
#include "../System/MySystem.hpp"

// スカイスフィアコンポーネント
class SkySphere : public Component
{
public:

	// コンストラクタ
	SkySphere() = default;

	// デストラクタ
	virtual ~SkySphere() = default;

	virtual void Awake()override
	{
		texture = *MySystem::GetInstance()->GetTexture(U"PlayBackGround");
	}

	virtual void Draw() override
	{
		const ScopedRenderStates3D states{ RasterizerState::SolidCullFront };
		skySphere.draw(texture);
	}

private:

	Sphere skySphere = Sphere(0,0,0,1000);
	Texture texture;
};
