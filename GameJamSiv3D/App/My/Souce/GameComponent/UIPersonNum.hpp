#pragma once
#include "../System/MySystem.hpp"

// UI 助けた人数コンポーネント
class UIPersonNum : public Component
{
public:

	// コンストラクタ
	UIPersonNum() = default;

	// デストラクタ
	virtual ~UIPersonNum() = default;

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
		fontDrawComponent->txt = U"助けた人数 {} / 5"_fmt(personNum);
	}


	inline void SetPersonNum(int8 newPersonNum)
	{
		personNum = newPersonNum;
	}

private:

	int8 personNum = 0;
	std::shared_ptr<FontDraw> fontDrawComponent;
};
