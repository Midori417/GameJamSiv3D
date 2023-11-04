# include "TextureDraw.hpp"
# include "GameObject.hpp"

void TextureDraw::Awake()
{
	auto ownerObj = GetOwner();
	ownerObj->renderQueue = RenderQueue::Dimension2D;
}

void TextureDraw::Draw()
{
	auto ownerObj = GetOwner();
	texture->draw(ownerObj->position.xy());
}
