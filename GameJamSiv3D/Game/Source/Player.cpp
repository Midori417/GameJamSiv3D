#include "../Header/Player.hpp"

// コンストラクタ
Player::Player()
	:roket(U"../Game/Resouce/Obj/Roket.obj")
	, pos(Vec3::Zero())
{

}

// 更新関数
void Player::Update()
{
	// 移動処理
	Move();
}

// 描画関数
void Player::Draw() const
{
	// モデルの描画
	roket.draw(pos);
}

// 移動関数
void Player::Move()
{
	double deltaTime = Scene::DeltaTime();

	if (KeyW.pressed())
	{
		pos.z += speed * deltaTime;
	}
	if (KeyS.pressed())
	{
		pos.z -= speed * deltaTime;
	}
	if (KeyA.pressed())
	{
		pos.x -= speed * deltaTime;
	}
	if (KeyD.pressed())
	{
		pos.x += speed * deltaTime;
	}

}
