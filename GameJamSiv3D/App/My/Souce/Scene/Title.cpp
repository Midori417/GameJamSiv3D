# include "Title.hpp"
# include "../System/MySystem.hpp"
# include "../GameComponent/UIStartButton.hpp"

Title::Title(const InitData& init)
	:IScene(init)
{
	// システムの取得
	auto mySystem = MySystem::GetInstance();

	// 背景の生成
	{
		auto uiBackGround = mySystem->CreateUI<GameObject>(U"UIBackGroud");
		auto texDrawCom = uiBackGround->AddComponent<TextureDraw>();
		texDrawCom->texture = mySystem->GetTexture(U"TitleBackGround");
	}
	// スタートボタン
	{
		auto uiStartButon = mySystem->CreateUI<GameObject>(U"TileButton", Vec2(700, 500));
		auto fontDrawCom = uiStartButon->AddComponent<FontDraw>();
		fontDrawCom->font = *mySystem->GetFont(U"Bold64");
		fontDrawCom->txt = U"キンギョ発進";
		uiStartButtonComponent = uiStartButon->AddComponent<UIStartButton>();
	}
	mySystem->GetAudio(U"Title")->play();

}

Title::~Title()
{
	auto mySystem = MySystem::GetInstance();

	// ゲームオブジェクトをすべて削除
	mySystem->AllClearGameObject();
	mySystem->GetAudio(U"Title")->stop();

}

void Title::update()
{
	auto mySystem = MySystem::GetInstance();

	if (uiStartButtonComponent->IsLCliced())
	{
		mySystem->GetAudio(U"Title")->stop();
		mySystem->GetAudio(U"Start")->play();
		changeScene(SceneState::Play, 2.0s);
	}
}
