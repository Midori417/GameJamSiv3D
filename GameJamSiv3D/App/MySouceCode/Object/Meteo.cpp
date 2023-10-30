#include "Meteo.hpp"

Meteo::Meteo()
	:model(U"MyResouce/Obj/Meteo.obj")
{
	// 初期位置をランダムに
	position.x = Random(-100, 100);
	position.y = Random(-20, 5);
	position.z = Random(-100, 100);

	moveDirection = Random(0, 3);
	speed = Random(-2, 2);
	collider.setR(1);
	rotation = Quaternion::RotateY(Random(0, 360));
}

void Meteo::Update()
{
	double deltaTime = Scene::DeltaTime();
	switch (moveDirection)
	{
	case 1:

		position.x += speed * deltaTime;

		break;
	case 3:
		position.z += speed * deltaTime;
		break;
	default:
		break;
	}
	collider.setPos(position);
}

void Meteo::Draw()
{
	model.draw(position,rotation);
}
