#include "PersonHelp.hpp"
#include <random>

PersonHelp::PersonHelp()
	:model(U"Game/Resouce/Obj/PersonHelp.obj")
	, isSave(false)
{
	// 初期位置をランダムに
	position.x = Random(-100, 100);
	position.y = 0;
	position.z = Random(-100, 100);

	collider.setR(1);
	rotation = Quaternion::RotateY(Random(0, 360));
}

void PersonHelp::Update()
{
	collider.setPos(position);
}

void PersonHelp::Draw() const
{
	if (!isSave)
	{
		model.draw(position, rotation);
	}
}
