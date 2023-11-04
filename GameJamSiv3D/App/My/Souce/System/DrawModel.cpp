# include "DrawModel.hpp"
# include "GameObject.hpp"

void DrawModel::Draw()
{
	auto ownerObj = GetOwner();
	model->draw(ownerObj->position, ownerObj->rotation);
}
