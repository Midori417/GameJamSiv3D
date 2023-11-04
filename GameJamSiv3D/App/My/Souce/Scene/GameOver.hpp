#pragma once
#include "SceneCommon.hpp"

// ゲームオーバーシーン
class GameOver : public App::Scene
{
public:

	// Constructor
	GameOver(const InitData& init);
	// destructor
	~GameOver();

	// Scene Update関数
	void update() override;

private:

};
