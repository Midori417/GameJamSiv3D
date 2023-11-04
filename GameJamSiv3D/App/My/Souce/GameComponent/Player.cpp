#include "Player.hpp"
#include "Bullet.hpp"
#include "../Effect/EffectJet.hpp"
#include "../Effect/EffectExposion.hpp"

void Player::Awake()
{
	auto ownerObj = GetOwner();
	ownerObj->renderQueue = RenderQueue::Effect3D;
	effectMesh = Mesh(MeshData::Billboard());
}

void Player::Start()
{
	speed = 0;
	isStrat = false;
}

void Player::Update()
{
	float deltaTime = static_cast<float>(Scene::DeltaTime());
	BasicCamera3D* camera = &MySystem::GetInstance()->GetMainCamera();
	auto ownerObj = GetOwner();

	if (isStrat)
	{
		if (damageCurrentTime <= 0)
		{

			if (KeyA.pressed())
			{
				rot.y -= rotateSpeed * deltaTime;
			}
			if (KeyD.pressed())
			{
				rot.y += rotateSpeed * deltaTime;
			}
			if (KeyS.pressed())
			{
				rot.x += rotateSpeed * deltaTime;
			}
			if (KeyW.pressed())
			{
				rot.x -= rotateSpeed * deltaTime;
			}
			if (rot.x > 360_deg || rot.x < -360_deg)
			{
				rot.x = 0;
			}
			if (rot.y > 360_deg || rot.y < -360_deg)
			{
				rot.y = 0;
			}

			if (KeySpace.pressed() && shotcurrentTime <= 0)
			{
				auto bullet = MySystem::GetInstance()->Create<GameObject>(U"Bullet", ownerObj->position, ownerObj->rotation);
				auto drawModel = bullet->AddComponent<DrawModel>();
				drawModel->model = MySystem::GetInstance()->GetModel(U"Bullet");
				auto collider = bullet->AddComponent<SphereCollider>();
				collider->sphere.setR(1);
				bullet->AddComponent<Bullet>();
				shotcurrentTime = shotInterval;
			}
			if (shotcurrentTime > 0)
			{
				shotcurrentTime -= 1 * deltaTime;
			}
			// Dash
			if (KeyLShift.pressed() && boostGage < boostGageMax && boostOk)
			{
				speed = 40.0;
				boostGage += 1 * deltaTime;
			}
			if (!KeyLShift.pressed())
			{
				if (boostGage > 0)
				{
					boostGage -= 1 * deltaTime;
					if (boostGage > 2)
					{
						boostOk = true;
					}
				}
				speed = 10.0;
			}
			if (boostGage >= boostGageMax)
			{
				speed = 10.0;
				boostOk = false;

			}

			ownerObj->position += ownerObj->rotation * Vec3(0, 0, speed) * deltaTime;
			ownerObj->rotation = Quaternion::RotateX(rot.x) * Quaternion::RotateY(rot.y);
			effect3D.add<EffectJet>(ownerObj->position + ownerObj->rotation * Vec3(1.5, 0, -3), ownerObj->rotation, effectMesh);
			effect3D.add<EffectJet>(ownerObj->position + ownerObj->rotation * Vec3(-1.5, 0, -3), ownerObj->rotation, effectMesh);
		}

		// ダメージを食らったら止まる
		if (damageCurrentTime > 0)
		{
			damageCurrentTime -= 1 * deltaTime;
		}

	}
	camera->setView(ownerObj->position + ownerObj->rotation * Vec3(0, 10, -30), ownerObj->position + ownerObj->rotation * Vec3(0,5,0), ownerObj->rotation * Vec3(0,1,0));
}

void Player::Draw()
{
	// 3D のエフェクトを描画する
	{
		// ブレンドモード有効、深度書き込み無効
		const ScopedRenderStates3D states{ BlendState::Default2D, DepthStencilState::DepthTest };
		effect3D.update();
	}
}

void Player::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
{
	const auto& name = other->GetOwner()->name;
	if (damageCurrentTime <= 0)
	{
		if (name == U"Ufo")
		{
			Print << U"UFOに衝突";
			life--;
		}
		if (name == U"Meteo")
		{
			MySystem::GetInstance()->GetAudio(U"RockBreak")->play();
			auto exprosion = MySystem::GetInstance()->Create<GameObject>(U"Exprosion", other->GetOwner()->position);
			exprosion->AddComponent<Exprosion>();
			other->GetOwner()->Destroy();
			life--;
			damageCurrentTime = damegeTime;
		}
	}
	if (name == U"PersonHelp")
	{
		Print << U"助けたよ";
		MySystem::GetInstance()->GetAudio(U"Rescue")->play();
		other->GetOwner()->Destroy();
		personNum++;
	}
}
