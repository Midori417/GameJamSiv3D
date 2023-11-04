#pragma once
#include "../System/MySystem.hpp"
#include "../Effect/EffectExposion.hpp"

class Bullet : public Component
{
public:
	Bullet() = default;
	~Bullet() = default;

	virtual void Update() override
	{
		float deltaTime = static_cast<float>(Scene::DeltaTime());
		auto ownerObj = GetOwner();
		ownerObj->position += ownerObj->rotation * Vec3(0, 0, speed) * deltaTime;


		rotY += 1_deg;
		if (rotY > 360_deg)
		{
			rotY = 0;
		}
		deleteTime += 1 * deltaTime;
		if (deleteTime > 3)
		{
			ownerObj->Destroy();
		}
	}
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other)
	{
		const auto& name = other->GetOwner()->name;
		if (name == U"Ufo")
		{
			auto exprosion = MySystem::GetInstance()->Create<GameObject>(U"Exprosion", other->GetOwner()->position);
			exprosion->AddComponent<Exprosion>();
			other->GetOwner()->Destroy();
			self->GetOwner()->Destroy();
			MySystem::GetInstance()->GetAudio(U"UFO_Destroy")->play();
			Print << U"UFoHit";
		}
		if (name == U"Meteo")
		{
			self->GetOwner()->Destroy();
		}
	}
private:

	std::shared_ptr<Model> model;
	const double speed = 100;
	float deleteTime = 0;
	double rotY = 0;

	Effect effect3D;
	Mesh effectMesh;

};
