#include "ObjectManager.hpp"

ObjectManager* ObjectManager::instance = nullptr;

void ObjectManager::Initialize()
{
	// オブジェクト配列の容量を予約
	gameObjects.resize(1000);
}

void ObjectManager::Update()
{
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		GameObject* e = gameObjects[i].get();
		if (!e->IsDestoryed())
		{
			e->Start();
			e->Update();
		}
	}
	RemoveDestroyGameObject();
}

void ObjectManager::RemoveDestroyGameObject()
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

}

void ObjectManager::GameObjectAllClear()
{
	// ゲームオブジェクト配列をクリア
	gameObjects.clear();
}
