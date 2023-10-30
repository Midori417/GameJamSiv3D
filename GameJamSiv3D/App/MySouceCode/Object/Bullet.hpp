#pragma once
#include <Siv3D.hpp>

class Bullet
{
public:
	Sphere model;

	Vec3 m_Pos;
	Quaternion m_Rot;

	double speed = 10;
public:

	Bullet() {}


	void Update()
	{
		m_Pos += (m_Rot * Vec3(0, 0, speed)) * Scene::DeltaTime();
	}

	void Draw()
	{
		model.setPos(m_Pos);
		model.draw();
	}
};

using BulletPtr = std::shared_ptr<Bullet>;
using BulletList = Array<BulletPtr>;
