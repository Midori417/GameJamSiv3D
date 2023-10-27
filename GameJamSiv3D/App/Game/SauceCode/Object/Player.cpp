#include "Player.hpp"
#include "../Sub/Particle3D.hpp"
Player::Player()
	: model(U"Game/Resouce/Obj/Roket.obj")
	, position(Vec3::Zero())
	, rotationY(0)
	, personHelp(0)
	,hp(3)
	,isMuteki(true)
	,effectMesh(MeshData::Billboard())
	,effectTexture(U"example/particle.png", TextureDesc::MippedSRGB)
{
	
	sphereCollider.setR(1);
}

void Player::Update()
{
	double deltaTime = Scene::DeltaTime();

	if (isMuteki)
	{
		mutekiTime -= 1 * deltaTime;
		if (mutekiTime < 0)
		{
			isMuteki = false;
		}
	}

	double sinY = Sin(rotationY);
	double cosY = Cos(rotationY);

	speed = !KeyLShift.pressed() ? defaltSpeed : dashSpeed;

	if (KeyW.pressed() || KeyA.pressed() || KeyD.pressed())
	{
		position.x += sinY * speed * deltaTime;
		position.z += cosY * speed * deltaTime;
		effect3D.add<Particle3D>(position + rotation * Vec3(0,0,-3), effectMesh, effectTexture, camera);
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
	sphereCollider.setPos(position);
}

void Player::Draw() const
{
	model.draw(position, rotation);
	sphereCollider.draw();
	// 3D のエフェクトを描画する
	{
		// ブレンドモード有効、深度書き込み無効
		const ScopedRenderStates3D states{ BlendState::Default2D, DepthStencilState::DepthTest };
		effect3D.update();
	}
}

void Player::EffectDraw() const
{
}
