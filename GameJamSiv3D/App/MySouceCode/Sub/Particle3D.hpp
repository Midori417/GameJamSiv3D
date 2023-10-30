#pragma once
#include <Siv3D.hpp>

struct Particle3D : IEffect
{
	Vec3 m_pos;

	Quaternion m_rot;

	Mesh m_billboardMesh;

	Texture m_texture;

	std::shared_ptr<BasicCamera3D> m_pCamera;

	explicit Particle3D(const Vec3& pos, const Quaternion& rot, const Mesh& billboardMesh, const Texture& texture, const std::shared_ptr<BasicCamera3D>& pCamera)
		: m_pos{ pos }
		, m_rot(rot)
		, m_billboardMesh{ billboardMesh }
		, m_texture{ texture }
		, m_pCamera{ pCamera } {}

	bool update(double t) override
	{
		const Vec3 pos = (m_pos + m_rot * Vec3(0, 0, -2) * t);
		const double scale = (1.0 + t * 2.0);
		const double alpha = (1.0 - t);
		const ColorF color(1.0,0,0, alpha);

		m_billboardMesh.draw(m_pCamera->billboard(pos, scale), m_texture, color.removeSRGBCurve());
		if (t < 0.7)
		{
			const Vec3 pos2 = (m_pos + m_rot * Vec3(0, 0, -2) * t);
			const ColorF color2 = Palette::Orange;
			const double scale2 = (1.0 + t * 0.5);
			m_billboardMesh.draw(m_pCamera->billboard(pos2, scale2), m_texture, ColorF(color2, alpha).removeSRGBCurve());
		}
		// 1 秒未満なら継続する
		return (t < 1);
	}
};
