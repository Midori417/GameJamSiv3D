#pragma once
#include "../System/MySystem.hpp"

struct EffectExprosion : IEffect
{
	Vec3 m_pos;

	Quaternion m_rot;

	Mesh m_billboardMesh;


	BasicCamera3D* m_pCamera;

	explicit EffectExprosion(const Vec3& pos)
		: m_pos{ pos }
		, m_billboardMesh{ *MySystem::GetInstance()->GetBillMesh()}
		, m_pCamera{ &MySystem::GetInstance()->GetMainCamera()} {
	}

	bool update(double t) override
	{
		auto mySystem = MySystem::GetInstance();
		const Vec3 pos = m_pos;
		const double scale = (10.0 + t * 30.0);
		const double alpha = (1.0 - t);
		const ColorF color(1, 0, 0, alpha);

		m_billboardMesh.draw(m_pCamera->billboard(pos, scale), *mySystem->GetTexture(U"Effect"), color.removeSRGBCurve());
		const double scale2 = (7.0 + t * 20);
		const ColorF color2 = Palette::Orange;
		m_billboardMesh.draw(m_pCamera->billboard(pos, scale2), *mySystem->GetTexture(U"Effect"), color2.removeSRGBCurve());



		// 1 秒未満なら継続する
		return (t < 1);
	}
};

class Exprosion : public Component
{
public:
	Exprosion() = default;

	virtual void Awake() override
	{
		GetOwner()->renderQueue = RenderQueue::Effect3D;
	}

	virtual void Update() override
	{
		deleteTime += Scene::DeltaTime();
		effect3D.add<EffectExprosion>(GetOwner()->position);

		if (deleteTime > 1)
		{
			GetOwner()->Destroy();
		}
	}

	virtual void Draw() override
	{
		// 3D のエフェクトを描画する
		{
			// ブレンドモード有効、深度書き込み無効
			const ScopedRenderStates3D states{ BlendState::Default2D, DepthStencilState::DepthTest };
			effect3D.update();
		}
	}

private:

	double deleteTime = 0;

	// Effect
	Effect effect3D;

};
