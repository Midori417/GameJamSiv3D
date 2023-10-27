#include "Player.hpp"

Player::Player()
	: mesh(U"../Game/Resouce/Obj/Roket.obj")
	, position(Vec3::Zero())
	, rotationY(0)
{
}

void Player::Update()
{
	double deltaTime = Scene::DeltaTime();

	double sinY = Sin(rotationY);
	double cosY = Cos(rotationY);

	speed = !KeyLShift.pressed() ? defaltSpeed : dashSpeed;

	if (KeyW.pressed() || KeyA.pressed() || KeyD.pressed())
	{
		position.x += sinY * speed * deltaTime;
		position.z += cosY * speed * deltaTime;
	}
	if (KeyA.pressed())
	{
		rotationY -= 1 * deltaTime;
	}
	if (KeyD.pressed())
	{
		rotationY += 1 * deltaTime;
	}
	rotation = Quaternion::RotateY(rotationY);
}

void Player::Draw()
{
	model.draw(position, rotation);
}
