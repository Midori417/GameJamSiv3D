#pragma once
#include "../Common.hpp"

// 先行宣言
class Player;
class PersonHelp;
class Meteo;
class UI;

// タイトルシーン
class Play : public App::Scene
{
private:

	// 背景色
	const ColorF backGroundColor = ColorF(0.1, 0.1, 0.3).removeSRGBCurve();

	// レンダーテクスチャ
	const MSRenderTexture renderTexture;
	std::shared_ptr<BasicCamera3D> camera;	//DebugCamera3D camera;
	const Vec3 offsetPos = Vec3(0, 5, -20);

	const int32 stateSize = 100;

	// 後でオブジェクトにまとめる
	std::shared_ptr<Player> player;
	std::shared_ptr<UI> ui;
	Array<std::shared_ptr<PersonHelp>> personHelps;
	const int32 personHelpMax = 5;
	Array<std::shared_ptr<Meteo>> meteos;
	const int32 meteoMax = 100;


public:

	// コンストラクタ
	Play(const InitData& init);

	// 更新関数
	void update() override;

	// 描画関数
	void draw() const override;

};
