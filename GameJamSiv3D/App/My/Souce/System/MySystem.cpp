# include "MySystem.hpp"
# include "Collision.hpp"
# include "../Scene/Title.hpp"
# include "../Scene/Play.hpp"
# include "../Scene/GameOver.hpp"
# include "../Scene/GameClear.hpp"
// スタティック変数の初期化
MySystem* MySystem::instance = nullptr;

void MySystem::Run()
{
	// システムを初期化
	Initialize();

	// ゲームループ
	while (System::Update())
	{
		// シーンがなければ抜ける
		if (not sceneManager.update())
		{
			break;
		}
		// システムを更新
		Update();
	}
}

void MySystem::Initialize()
{
	// ウィンドウのサイズを変更
	Window::Resize(1280, 720);

	renderTexture = MSRenderTexture(Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes);
	camera = BasicCamera3D(renderTexture.size(), 30_deg, Vec3(0, 5, -20));


	// Textrueの読み込み
	GetTexture(U"TitleBackGround", U"My/Resouce/Texture/Title.png");
	GetTexture(U"PlayBackGround", U"My/Resouce/Texture/BackGround.png");
	GetTexture(U"GameOverBackGround", U"My/Resouce/Texture/GameOver.png");
	GetTexture(U"GameClearBackGround", U"My/Resouce/Texture/GameClear.png");

	GetTexture(U"Effect", U"example/particle.png");

	// モデル読み込み
	GetModel(U"Roket", U"My/Resouce/obj/Roket.obj");
	GetModel(U"Bullet", U"My/Resouce/obj/Bullet.obj");
	GetModel(U"UFO", U"My/Resouce/obj/UFO.obj");
	GetModel(U"Meteo", U"My/Resouce/obj/Meteo.obj");
	GetModel(U"PersonHelp", U"My/Resouce/obj/PersonHelp.obj");

	// Fontの作成
	GetFont(U"Bold24", 24);
	GetFont(U"Bold32", 32);
	GetFont(U"Bold64", 64);

	// Audioの読み込み
	// BGM
	GetAudio(U"Title", U"My/Resouce/Sound/Title.mp3", true);
	GetAudio(U"Play", U"My/Resouce/Sound/Play.mp3", true);
	GetAudio(U"GameClear", U"My/Resouce/Sound/GameClear.mp3", true);
	GetAudio(U"GameOver", U"My/Resouce/Sound/GameOver.mp3", true);

	// 効果音
	GetAudio(U"Scream", U"My/Resouce/Sound/Scream.wav");
	GetAudio(U"Rescue", U"My/Resouce/Sound/Rescue.wav");
	GetAudio(U"RockBreak", U"My/Resouce/Sound/RockBreak.wav");
	GetAudio(U"Clear", U"My/Resouce/Sound/Clear.mp3");
	GetAudio(U"Start", U"My/Resouce/Sound/Start.mp3");
	GetAudio(U"UFO_Destroy", U"My/Resouce/Sound/UFO_Destroy.wav");


	// シーンの登録
	sceneManager.add<Title>(SceneState::Title);
	sceneManager.add<Play>(SceneState::Play);
	sceneManager.add<GameOver>(SceneState::GameOver);
	sceneManager.add<GameClear>(SceneState::GameClear);
	//sceneManager.init(SceneState::GameClear);

}

void MySystem::Update()
{
	// プリントを削除
	ClearPrint();

	// ゲームオブジェクトを更新
	UpdateObject();

	// 描画処理
	Render();

	// 破棄予定のゲームオブジェクトを削除
	RemoveDestroyObject();

	// 衝突処理
	HandleGameObjectCollision();
}

void MySystem::Render()
{
	// ゲームオブジェクトがなければ何もしない
	if (gameObjects.empty())
	{
		return;
	}

	// RenderQueueの小さい順にそろえる
	std::stable_sort(gameObjects.begin(), gameObjects.end(),	// 範囲
	[](const GameObjectPtr& a, const GameObjectPtr& b) {
	return a->renderQueue < b->renderQueue; });			// 条件 小さい

	// Effectの先端を検索
	const auto effectBegin = std::lower_bound(
	gameObjects.begin(), gameObjects.end(), RenderQueue::Effect3D,
	[](const GameObjectPtr& e, int value) {return e->renderQueue < value; });

	// 2Dの先端を検索
	const auto dimension2DBegin = std::lower_bound(
	effectBegin, gameObjects.end(), RenderQueue::Dimension2D,
	[](const GameObjectPtr& e, int value) {return e->renderQueue < value; });

	// 3Dシーンの描画
	if(gameObjects[0]->renderQueue == RenderQueue::Dimension3D)
	{
		ScopedRenderTarget3D target(renderTexture.clear(backGroundColor));
		Graphics3D::SetCameraTransform(camera);
		// 3Dモデルの描画
		{
			DrawObject(gameObjects.begin(), effectBegin);
		}
		// 3Dエフェクトの描画
		{
			DrawObject(effectBegin, dimension2DBegin);
		}
	}
	// [RenderTextureを2Dシーンに描画]
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}
	// 2Dシーンの描画
	{
		DrawObject(dimension2DBegin, gameObjects.end());
	}
}

void MySystem::UpdateObject()
{
	// ゲームオブジェクトがなければ何もしない
	if (gameObjects.empty())
	{
		return;
	}

	// 要素の追加に対応するための添え字を選択
	for (int i = 0; i < this->gameObjects.size(); ++i)
	{
		// オブジェクトを取得
		GameObject* e = this->gameObjects[i].get();
		// オブジェクトが破壊予定されていないかどうか
		if (!e->IsDestoryed())
		{
			e->Start(); // 最初に実行
			e->Update(); // 更新処理
		}
	}
}

void MySystem::DrawObject(GameObjectList::iterator begin, GameObjectList::iterator end)
{
	for (GameObjectList::iterator i = begin; i != end; ++i) {
		const auto& e = *i;

		e->Draw();
	}

}

void MySystem::RemoveDestroyObject()
{
	// ゲームオブジェクト配列の中身がなければ何もしない
	if (gameObjects.empty()) {
		return;
	}

	// 破棄予定の有無でゲームオブジェクトを分ける
	const auto iter = std::partition(
		gameObjects.begin(), gameObjects.end(),
		[](const GameObjectPtr& e) { return !e->IsDestoryed(); });

	// 破棄予定のオブジェクトを別の配列に移動
	GameObjectList destoryList(
		std::make_move_iterator(iter),
		std::make_move_iterator(gameObjects.end()));

	// 配列から移動済みのオブジェクトを削除
	gameObjects.erase(iter, gameObjects.end());

	// 破棄予定のオブジェクトにOnDesotryを実行
	for (auto& e : destoryList) {
		e->OnDestroy();
	}
}

void MySystem::HandleGameObjectCollision()
{
	Array<WorldColliderList> colliders;
	colliders.reserve(gameObjects.size());
	if (gameObjects.empty())
	{
		return;
	}

	for (const auto& e : gameObjects)
	{
		// コライダーを持っていなければ飛ばす
		if (e->colliders.empty())
		{
			continue;
		}
		// 衝突判定を作成
		WorldColliderList list(e->colliders.size());
		for (int i = 0; i < e->colliders.size(); ++i)
		{
			list[i].origin = e->colliders[i];
		}
		colliders.push_back(list); 
	}

	// コライダーがついているオブジェクトが二個以上ナイト衝突判定ができない
	if (colliders.size() >= 2)
	{
		for (auto a = colliders.begin(); a != colliders.end() - 1; ++a)
		{
			const GameObject* goA = a->at(0).origin->GetOwner();
			if (goA->IsDestoryed())
			{
				continue;
			}
			for (auto b = a + 1; b != colliders.end(); ++b)
			{
				const GameObject* goB = b->at(0).origin->GetOwner();	// コライダーの持ち主を取得
				// オブジェクトが破壊予定されていないか
				if (goB->IsDestoryed())
				{
					continue;	// 削除済みなので飛ばす
				}
				
				HandleWorldColliderCollision(&*a, &*b);
			}
		}
	}
}

void MySystem::HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b)
{
	// コライダー単位の衝突判定
	for (auto& colA : *a)
	{
		for (auto& colB : *b)
		{

			auto colliderA = colA.origin->GetOwner()->GetComponent<SphereCollider>();
			auto colliderB = colB.origin->GetOwner()->GetComponent<SphereCollider>();
			if (Intersect(colliderA->sphere, colliderB->sphere))
			{
				GameObject* goA = colA.origin->GetOwner();
				GameObject* goB = colB.origin->GetOwner();

				// 衝突イベント関数の呼び出し
				goA->OnCollision(colA.origin, colB.origin);
				goB->OnCollision(colB.origin, colA.origin);

				// イベントの結果、どちらかのげーむオブジェクトが破棄されたらループ終了
				if (goA->IsDestoryed() || goB->IsDestoryed())
				{
					return;	//関数を終了
				}
			}

		} // for colB
	} // for colA

}

void MySystem::AllClearGameObject()
{
	for (auto& e : gameObjects) {
		e->OnDestroy();
	}
	// ゲームオブジェクト配列をクリア
	gameObjects.clear();
}
