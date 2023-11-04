#pragma once
#include "../System/MySystem.hpp"

class Meteo : public Component
{
public:

	Meteo() = default;
	virtual ~Meteo() = default;

	virtual void Awake() override {
		auto ownerObj = GetOwner();
		// 初期位置をランダムに
		ownerObj->position.x = Random(-StageW, StageW);
		ownerObj->position.y = Random(-StageH, StageH);
		ownerObj->position.z = Random(-StageD, StageD);

		ownerObj->rotation = Quaternion::RotateY(Random(0, 360));

	}

	virtual void Update() override {
		double deltaTime = Scene::DeltaTime();
		auto ownerObj = GetOwner();

		ownerObj->position += speed * deltaTime;
	}
private:

	// 速さ
	Vec3 speed;

	const int32 StageW = 200;
	const int32 StageH = 300;
	const int32 StageD = 200;


};
