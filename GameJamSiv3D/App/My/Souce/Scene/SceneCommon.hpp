#pragma once
#include <Siv3D.hpp>

// ゲームの状態
enum class SceneState
{
	Title,
	Play,
	GameOver,
	GameClear,
};

struct GameData
{
	int32 time = 0;
};

// プレイ状態
enum PlayState
{
	Redy,
	Go,
	End,
};

using App = SceneManager<SceneState, GameData>;
