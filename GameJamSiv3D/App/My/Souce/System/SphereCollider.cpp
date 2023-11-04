# include "SphereCollider.hpp"
# include "GameObject.hpp"

void SphereCollider::Update()
{
	auto ownerObj = GetOwner();
	sphere.setPos(ownerObj->position);
}
