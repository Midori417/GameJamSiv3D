#pragma once
#include <Siv3D.hpp>

// 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;

// コンポーネントの基底クラス
class Component
{
	friend GameObject;
private:

	GameObjectPtr owner = nullptr;
	bool isStarted = false;
	bool isDestroyed = false;

public:

	Component() = default;
	virtual ~Component() = default;

public:

	// コンポーネントの就社を取得
	GameObjectPtr GetOwner() const {
		return owner;
	}

	// コンポーネントが追加されたときに呼び出す関数
	virtual void Awake(){}

	// 最初のUpdateの直前で呼び出す関数
	virtual void Start(){}

	// 毎フレーム一回呼び出す関数
	virtual void Update(){}

	virtual void Draw() const {}

	// コンポーネントをゲームオブジェクトから削除する
	inline void Destroy()
	{
		isDestroyed = true;
	}

	// コンポーネントが破壊されているか取得
	inline bool IsDestroyed() const
	{
		return isDestroyed;
	}

};

using ComponentPtr = std::shared_ptr<Component>;
