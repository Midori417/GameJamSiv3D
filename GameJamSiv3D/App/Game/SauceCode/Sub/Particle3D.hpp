#pragma once
#include <Siv3D.hpp>

struct Particle3D : IEffect
{
	Vec3 m_pos;


	Mesh m_billboardMesh;

	Texture m_texture;

	std::shared_ptr<BasicCamera3D> m_pCamera;

	explicit Particle3D(const Vec3& pos, const Mesh & billboardMesh, const Texture& texture, const std::shared_ptr<BasicCamera3D>& pCamera)
		: m_pos{ pos }
		, m_billboardMesh{ billboardMesh }
		, m_texture{ texture }
		, m_pCamera{ pCamera } {}

	bool update(double t) override
	{
		const Vec3 pos = (m_pos + Vec3{ 0, 0, -2 } *t);
		const double scale = (1.0 + t * 2.0);
		const double alpha = (1.0 - t);

		m_billboardMesh.draw(m_pCamera->billboard(pos, scale), m_texture, ColorF{ 0.5,0,0, alpha }.removeSRGBCurve());

		// 1 秒未満なら継続する
		return (t < 0.5);
	}
};
