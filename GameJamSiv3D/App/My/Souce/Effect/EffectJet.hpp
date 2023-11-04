#pragma once
#include "../System/MySystem.hpp"

struct EffectJet : IEffect
{
	Vec3 m_pos;

	Quaternion m_rot;

	Mesh m_billboardMesh;


	BasicCamera3D* m_pCamera;

	explicit EffectJet(const Vec3& pos, const Quaternion& rot, const Mesh& billboardMesh)
		: m_pos{ pos }
		, m_rot(rot)
		, m_billboardMesh{ billboardMesh }
		, m_pCamera{ &MySystem::GetInstance()->GetMainCamera() }
	{
	}

	bool update(double t) override
	{
		auto mySystem = MySystem::GetInstance();
		const Vec3 pos = (m_pos + m_rot * Vec3(0, 0, -1.0) * static_cast<float>(t));
		const double scale = (1.0 + t * 2.0);
		const double alpha = (1.0 - t);
		const ColorF color(1.0, 0, 0, alpha);

		m_billboardMesh.draw(m_pCamera->billboard(pos, scale), *mySystem->GetTexture(U"Effect"), color.removeSRGBCurve());
		if (t < 0.7)
		{
			const Vec3 pos2 = (m_pos + m_rot * Vec3(0, 0, -2.0) * static_cast<float>(t));
			const ColorF color2 = Palette::Orange;
			const double scale2 = (1.0 + t * 0.5);
			m_billboardMesh.draw(m_pCamera->billboard(pos2, scale2), *mySystem->GetTexture(U"Effect"), ColorF(color2, alpha).removeSRGBCurve());
		}
		// 1 秒未満なら継続する
		return (t < 1);
	}
};
