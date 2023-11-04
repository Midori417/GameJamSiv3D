#include "Play.hpp"
#include "../GameComponent/Player.hpp"
#include "../GameComponent/Meteo.hpp"
#include "../GameComponent/UFO.hpp"
#include "../GameComponent/PersonHelp.hpp"
#include "../GameComponent/SkySphere.hpp"
#include "../GameComponent/UIMiniMap.hpp"
#include "../GameComponent/UITime.hpp"
#include "../GameComponent/UIPersonNum.hpp"
#include "../GameComponent/UILife.hpp"
#include "../GameComponent/UIBoostGage.hpp"


Play::Play(const InitData& init)
	:IScene(init)
	, playState(Redy)
{
	// システムの取得
	auto mySystem = MySystem::GetInstance();


	// プレイヤーの生成
	auto player = mySystem->Create<GameObject>(U"Player");
	{
		auto drawModel = player->AddComponent<DrawModel>();
		drawModel->model = mySystem->GetModel(U"Roket");
		auto collider = player->AddComponent<SphereCollider>();
		collider->sphere.setR(3);
		playerComponent = player->AddComponent<Player>();
	}
	// UFOと助ける人を生成
	for (int i = 0; i < 5; ++i)
	{
		// UFO
		auto ufo = mySystem->Create<GameObject>(U"Ufo");
		{
			auto drawModel = ufo->AddComponent<DrawModel>();
			drawModel->model = mySystem->GetModel(U"UFO");
			auto collider = ufo->AddComponent<SphereCollider>();
			collider->sphere.setR(3);
			ufo->AddComponent<UFO>();
		}
		// 助ける人
		auto personHelp = mySystem->Create<GameObject>(U"PersonHelp");
		{
			auto drawModel = personHelp->AddComponent<DrawModel>();
			drawModel->model = mySystem->GetModel(U"PersonHelp");
			auto personHelpComponent = personHelp->AddComponent<PersonHelp>();
			personHelpComponents.push_back(personHelpComponent);
			auto collider = personHelp->AddComponent<SphereCollider>();
			collider->sphere.setR(3);
			personHelp->SetParent(ufo);
		}
	}

	// 隕石を生成
	for (int i = 0; i < 200; ++i)
	{
		auto meteo = mySystem->Create<GameObject>(U"Meteo");
		auto drawModel = meteo->AddComponent<DrawModel>();
		drawModel->model = mySystem->GetModel(U"Meteo");
		auto collider = meteo->AddComponent<SphereCollider>();
		collider->sphere.setR(4);
		
		meteo->AddComponent<Meteo>();
	}

	// スカイスフィアを生成
	auto sky = mySystem->Create<GameObject>(U"SkySpehere");
	sky->AddComponent<SkySphere>();

	// UI
	{
		// ミニマップの生成
		auto miniMap = mySystem->CreateUI<GameObject>(U"UIMiniMap", Vec2(10, 10));
		uiMiniMapComponent = miniMap->AddComponent<UIMiniMap>();
		uiMiniMapComponent->playerPos = std::make_shared<Vec2>(player->position.xy());
		for (auto x : personHelpComponents)
		{
			uiMiniMapComponent->personHelps.push_back(x);
		}

		// 時間
		auto uiTime = mySystem->CreateUI<GameObject>(U"UITime", Vec2(1100, 0));
		uiTimeComponent = uiTime->AddComponent<UITime>();

		// 助けた人数
		auto uiPersonNum = mySystem->CreateUI<GameObject>(U"UIPersonNum", Vec2(550, 10));
		uiPersonNumComponent = uiPersonNum->AddComponent<UIPersonNum>();

		// ライフ
		auto uiLife = mySystem->CreateUI<GameObject>(U"UILife", Vec2(10, 720 - 50));
		uiLifeComponent = uiLife->AddComponent<UILife>();

		// ブースとゲージ
		auto uiBoost = mySystem->CreateUI<GameObject>(U"UIGage", Vec2(1000, 720 - 50));
		uiBoostGageComponent = uiBoost->AddComponent<UIBoostGage>();

	}

	mySystem->GetAudio(U"Play")->play();
}

Play::~Play()
{
	// システムの取得
	auto mySystem = MySystem::GetInstance();

	// ゲームオブジェクトをすべて削除
	mySystem->AllClearGameObject();
	mySystem->GetAudio(U"Play")->stop();
}

void Play::update()
{
	// プレイ状態
	switch (playState)
	{
	case Redy:
		startTime -= 1 * Scene::DeltaTime();
		if (startTime <= 0)
		{
			// プレイヤーをスタート状態にする
			playerComponent->StartOk();
			uiTimeComponent->StartOk();
			playState = Go;
		}
		break;
	case Go:
		uiLifeComponent->SetLife(playerComponent->GetLife());
		uiPersonNumComponent->SetPersonNum(playerComponent->GetPersonNum());
		uiBoostGageComponent->SetEnrgi(playerComponent->GetEnrgi());
		uiMiniMapComponent->playerPos = std::make_shared<Vec2>(-playerComponent->GetOwner()->position.xz());
		if (playerComponent->GetPersonNum() == 5)
		{
			MySystem::GetInstance()->GetAudio(U"Play")->stop();
			MySystem::GetInstance()->GetAudio(U"Clear")->play();
			getData().time = uiTimeComponent->GetTime();
			changeScene(SceneState::GameClear, 2.0s);
		}
		if (playerComponent->GetLife() == 0)
		{
			MySystem::GetInstance()->GetAudio(U"Play")->stop();
			MySystem::GetInstance()->GetAudio(U"Scream")->play();
			changeScene(SceneState::GameOver, 2.0s);
		}
		break;
	}
	
}
