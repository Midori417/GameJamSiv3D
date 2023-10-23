#pragma once
#include <Siv3D.hpp>

/// @brief シーンの名前
enum class State
{
	// タイトル
	Title,

	// ゲーム
	Game,

	// ランキング
	Ranking,
};

/// @brief 共有するデータ
struct GameData
{
	// 直前のゲームのスコア
	Optional<int32> lastGameScore;

	// ハイスコア
	Array<int32> highScores = { 50, 40, 30, 20, 10 };
};

using App = SceneManager<State>;
