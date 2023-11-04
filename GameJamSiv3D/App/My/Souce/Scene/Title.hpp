# pragma once
# include "SceneCommon.hpp"

// 先行宣言
class UIStartButton;

// タイトルシーンクラス
class Title : public App::Scene
{
public:

	// コンストラクタ
	Title(const InitData& init);

	// デストラクタ
	~Title();

	// シーン更新関数
	void update() override;

private:

	std::shared_ptr<UIStartButton> uiStartButtonComponent;
};
