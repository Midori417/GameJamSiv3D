#pragma once
#include "../System/MySystem.hpp"

// UI 時間コンポーネント
class UITime : public Component
{
public:

	// コンストラクタ
	UITime() = default;

	// デストラクタ
	virtual ~UITime() = default;

	virtual void Awake() override
	{
		font = *MySystem::GetInstance()->GetFont(U"Bold32");
		font2 = *MySystem::GetInstance()->GetFont(U"Bold64");
	}

	virtual void Update() override
	{

		auto deltaTime = Scene::DeltaTime();

		if (isStart)
		{
			time += 1 * deltaTime;
		}
		else
		{
			startTimer -= 1 * deltaTime;
		}
		txt = U"Time {}"_fmt(static_cast<int>(time));
	}

	virtual void Draw() override
	{
		font(txt).draw(GetOwner()->position.xy());

		// カウントダウン
		if (!isStart)
		{
			if (startTimer > 1)
			{
				font2(U"{}"_fmt(static_cast<int>(startTimer))).drawAt(1280.0 / 2, 720.0 / 2);
			}
			else
			{
				font2(U"発進").drawAt(1280.0 / 2, 720.0 / 2);

			}
		}
	}

	void StartOk()
	{
		isStart = true;
	}

	inline int32 GetTime()
	{
		return static_cast<int32>(time);
	}

private:

	double time = 0;
	double startTimer = 5;
	bool isStart = false;
	Font font;
	Font font2;
	String txt;
};
