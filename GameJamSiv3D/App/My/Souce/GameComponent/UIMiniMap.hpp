#pragma once
#include "../System/MySystem.hpp"

class UIMiniMap : public Component
{
public:

	UIMiniMap() = default;
	virtual ~UIMiniMap() = default;

	virtual void Start() override
	{
		for (int i = 0; i < personHelps.size(); ++i)
		{
			personCicle.push_back(Circle());
			persons.push_back(false);
		}
	}

	virtual void Draw() override
	{
		miniMapRect.draw(Palette::Skyblue);
		Vec2 miniPlayerPos = (miniMapRect.pos + Vec2(100,100)) + (*playerPos / GameWorldSize * miniMapRect.size);
		playerCicle.setR(3);
		if (miniPlayerPos.x > 200)
		{
			miniPlayerPos.x = 200;
		}
		if (miniPlayerPos.x < 15)
		{
			miniPlayerPos.x = 15;
		}
		if (miniPlayerPos.y > 200)
		{
			miniPlayerPos.y = 200;
		}
		if (miniPlayerPos.y < 15)
		{
			miniPlayerPos.y = 15;
		}
		playerCicle.setPos(miniPlayerPos).draw(Palette::Red);
		for (int i = 0; i < personHelps.size(); ++i)
		{
			if (personHelps[i]->GetOwner()->IsDestoryed())
			{
				persons[i] = true;
			}
			if (persons[i])
			{
				continue;
			}
			auto personPos = -personHelps[i]->GetOwner()->position.xz();
			Vec2 miniPersonPos = (miniMapRect.pos + Vec2(100, 100)) + (personPos / GameWorldSize * miniMapRect.size);
			if (miniPersonPos.x > 200)
			{
				miniPersonPos.x = 200;
			}
			if (miniPersonPos.x < 15)
			{
				miniPersonPos.x = 15;
			}
			if (miniPersonPos.y > 200)
			{
				miniPersonPos.y = 200;
			}
			if (miniPersonPos.y < 15)
			{
				miniPersonPos.y = 15;
			}

			personCicle[i].setPos(miniPersonPos).setR(3).draw(Palette::Green);
		}
	}

	// ミニマップのサイズと位置
	const Rect miniMapRect = Rect(10, 10, 200, 200);

	const Size GameWorldSize = Size(400, 400);
	Circle playerCicle;
	Array<Circle> personCicle;
	Array<std::shared_ptr<class PersonHelp>> personHelps;
	Array<bool> persons;
	std::shared_ptr<Vec2> playerPos;
};
