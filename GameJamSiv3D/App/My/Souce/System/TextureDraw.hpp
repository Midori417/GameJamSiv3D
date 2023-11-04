# pragma once
# include "Component.hpp"

// テクスチャ描画コンポーネント
class TextureDraw : public Component
{
public:

	// コンストラクタ
	TextureDraw() = default;

	// デストラクタ
	virtual ~TextureDraw() = default;

	virtual void Awake() override;

	virtual void Draw() override;

public:

	std::shared_ptr<Texture> texture;
};
