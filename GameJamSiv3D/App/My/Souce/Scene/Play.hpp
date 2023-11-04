#pragma once
#include "SceneCommon.hpp"

// 先行宣言
class Player;
class PersonHelp;
class UILife;
class UIPersonNum;
class UITime;
class UIBoostGage;
class UIMiniMap;

// プレイシーン
class Play : public App::Scene
{
public:

	// コンストラクタ
	Play(const InitData& init);
	// デストラクタ
	~Play();

	// 更新関数
	void update() override;

private:

	// プレイ状態
	PlayState playState;

	// プレイヤーコンポーネント
	std::shared_ptr<Player> playerComponent;

	// 助ける人コンポーネント配列
	Array<std::shared_ptr<PersonHelp>> personHelpComponents;

	// UI 残機コンポーネント
	std::shared_ptr<UILife> uiLifeComponent;

	// UI 助けた人数コンポーネント
	std::shared_ptr<UIPersonNum> uiPersonNumComponent;

	// UI タイムコンポーネント
	std::shared_ptr<UITime> uiTimeComponent;

	// UI ダッシュゲージコンポーネント
	std::shared_ptr<UIBoostGage> uiBoostGageComponent;

	// UI ミニマップコンポーネント
	std::shared_ptr<UIMiniMap> uiMiniMapComponent;

	// 開始タイム
	double startTime = 5;
};
