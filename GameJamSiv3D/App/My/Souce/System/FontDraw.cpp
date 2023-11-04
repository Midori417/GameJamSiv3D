# include "FontDraw.hpp"
# include "GameObject.hpp"

void FontDraw::Awake()
{
	auto ownerObj = GetOwner();
	ownerObj->renderQueue = RenderQueue::Dimension2D;
}

void FontDraw::Draw()
{
	auto ownerObj = GetOwner();
	font(txt).draw(ownerObj->position.xy());
}
