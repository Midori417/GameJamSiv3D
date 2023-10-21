#include "Application.hpp"

/// @brief アプリの実行関数
/// @return 0 正常に終了 1 エラー発生
int32 Application::Run()
{
	// 初期化
	auto result = Initialize();
	if (result != 0) {
		return 1;
	}

	// アプリループ
	while (System::Update()){
		// 更新
		Update();
	}

	return 0;
}

/// @brief アプリの初期化関数
/// @return 0 初期化成功 1 初期化失敗
int32 Application::Initialize()
{
	// ウィンドウサイズを設定
	Window::Resize(1000, 800);

	// 背景の色を設定
	Scene::SetBackground(ColorF(0.22, 0.34, 0.8));

	// オブジェクトの追加

	// オブジェクト配列の初期化処理
	for (auto i : objects)
	{
		i->Initialize();
	}
	return 0;
}

/// @brief アプリの更新関数
void Application::Update()
{
	// オブジェクト配列の更新
	for (auto i : objects)
	{
		i->Update();
	}

	// オブジェクトを破壊
	DestoryGameObject();
}

/// @brief オブジェクトの破壊関数
void Application::DestoryGameObject()
{
	// オブジェクト配列に何もなければ何もしない
	if (objects.empty()) {
		return;
	}

	// 破棄予定の有無でオブジェクトを分ける
	const auto iter = std::partition(
		objects.begin(), objects.end(),
		[](const ObjectPtr& e) {return !e->IsDesotryed(); });

	// 破棄予定のオブジェクトを別の配列に移動
	ObjectList desotryList(
		std::make_move_iterator(iter),
		std::make_move_iterator(objects.end()));

	// 配列から移動済みのオブジェクトを削除
	objects.erase(iter, objects.end());
}
