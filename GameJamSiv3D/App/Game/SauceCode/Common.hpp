#pragma once

#include <Siv3D.hpp>

enum class SceneState
{
	Title,
	Play,
	Result,
};

using App = SceneManager<SceneState>;
