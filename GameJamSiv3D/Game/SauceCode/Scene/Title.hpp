﻿#pragma once
#include "../Common.hpp"

// タイトルシーン
class Title : public App::Scene
{
public:

	// コンストラクタ
	Title(const InitData& init);

	// 更新関数
	void update() override;

	// 描画関数
	void draw() const override;
};
