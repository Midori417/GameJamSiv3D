#pragma once
#include "../Common.hpp"

// 先行宣言
class Player;

// タイトルシーン
class Play : public App::Scene
{
private:

	// 背景色
	const ColorF backGroundColor = ColorF(0.1, 0.1, 0.3).removeSRGBCurve();

	// レンダーテクスチャ
	const MSRenderTexture renderTexture;
	BasicCamera3D camera;
	const Vec3 offsetPos = Vec3(0, 5, -20);

	std::shared_ptr<Player> player;

public:

	// コンストラクタ
	Play(const InitData& init);

	// 更新関数
	void update() override;

	// 描画関数
	void draw() const override;
};
