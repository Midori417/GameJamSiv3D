#pragma once
#include "../System/MySystem.hpp"

class PersonHelp : public Component
{
public:
	PersonHelp() = default;
	virtual ~PersonHelp() = default;

	virtual void Update() override
	{
		auto ownerObj = GetOwner();
		if (ownerObj->GetParent())
		{
			ownerObj->position = Vec3(ownerObj->GetParent()->position.x, ownerObj->GetParent()->position.y - 5, ownerObj->GetParent()->position.z);
			ownerObj->rotation = ownerObj->GetParent()->rotation;
		}
	}
};
