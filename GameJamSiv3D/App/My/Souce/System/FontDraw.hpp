#pragma once
#include "Component.hpp"

// フォント描画コンポーネント
class FontDraw : public Component
{
public:

	// コンストラクタ
	FontDraw() = default;
	virtual ~FontDraw() = default;

	virtual void Awake() override;

	virtual void Draw() override;

public:

	// フォント
	Font font;

	// テキスト
	String txt = U"";
};
