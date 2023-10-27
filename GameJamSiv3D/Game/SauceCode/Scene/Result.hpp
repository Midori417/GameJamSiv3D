#pragma once
#include "../Common.hpp"

// リザルトシーン
class Result : public App::Scene
{
public:

	// コンストラクタ
	Result(const InitData& init);

	// 更新関数
	void update() override;

	// 描画関数
	void draw() const override;
};
