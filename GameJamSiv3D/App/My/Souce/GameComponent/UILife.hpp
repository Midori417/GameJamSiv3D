#pragma once
#include "../System/MySystem.hpp"

// UI 残機コンポーネント
class UILife : public Component
{
public:

	// コンストラクタ
	UILife() = default;

	// デストラクタ
	virtual ~UILife() = default;

	virtual void Awake() override
	{
		// システムの取得
		auto mySystem = MySystem::GetInstance();

		// コンポーネントオーナー取得
		auto ownerOBJ = GetOwner();
		fontDrawComponent = ownerOBJ->AddComponent<FontDraw>();

		fontDrawComponent->font = *mySystem->GetFont(U"Bold32");
	}

	virtual void Update() override
	{
		fontDrawComponent->txt = U" 残機 {}"_fmt(life);
	}

	inline void SetLife(int8 newLife)
	{
		life = newLife;
	}

private:

	int8 life = 3;
	std::shared_ptr<FontDraw> fontDrawComponent;
};
