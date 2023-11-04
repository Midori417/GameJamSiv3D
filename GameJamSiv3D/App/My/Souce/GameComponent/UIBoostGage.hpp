#pragma once
#include "../System/MySystem.hpp"

// UI ブースとゲージコンポーネント
class UIBoostGage : public Component
{
public:

	UIBoostGage() = default;
	virtual ~UIBoostGage() = default;

	virtual void Awake() override
	{
		auto ownerobj = GetOwner();
		fillGage.setPos(ownerobj->position.x, ownerobj->position.y);
		fillGage.setSize(200, 40);
	}

	virtual void Update() override
	{
		fillGage.setSize(200 * energiW, 40);
	}

	virtual void Draw() override
	{
		auto ownerobj = GetOwner();
		fillGage.draw(Palette::Skyblue);
		Rect(ownerobj->position.x, ownerobj->position.y, 200, 40).drawFrame(2, Palette::Black);
	}

	inline void SetEnrgi(double newenerugi)
	{
		energiW = newenerugi;
	}

private:

	double energiW = 0;
	Rect fillGage ;
};
