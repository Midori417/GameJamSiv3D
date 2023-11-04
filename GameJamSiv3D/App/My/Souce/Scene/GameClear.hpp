#pragma once
#include "SceneCommon.hpp"

// ゲームクリアシーン
class GameClear : public App::Scene
{
public:

	// Constructor
	GameClear(const InitData& init);
	// destructor
	~GameClear();

	// Scene Update関数
	void update() override;

private:

};
