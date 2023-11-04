# pragma once
# include "Component.hpp"

using ModelPtr = std::shared_ptr<Model>;

class DrawModel : public Component
{
public:

	// コンストラク
	DrawModel() = default;

	// デストラクタ
	virtual ~DrawModel() = default;

	// 描画関数
	virtual void Draw() override;

public:

	// モデル
	ModelPtr model;
};
