#pragma once
#include "../System/MySystem.hpp"

// UI スタートボタンコンポーネント
class UIStartButton : public Component
{
public:

	// コンストラクタ
	UIStartButton() = default;

	// デストラクタ
	virtual ~UIStartButton() = default;

	// 更新関数
	virtual void Update() override
	{
		// マウスカーソルがRectの上にあったらカーソルを手に変える
		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}

	inline bool IsLCliced()
	{
		return rect.leftClicked();
	}
private:

	const Rect rect = Rect(700, 500, 450, 100);

};
