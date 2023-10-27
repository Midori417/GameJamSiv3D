#pragma once
#include <Siv3D.hpp>
#include "Component.hpp"

// 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = Array<GameObjectPtr>;
class GameObjectManager;

class GameObject
{
	friend GameObjectManager;
private:

	String m_Name;

	Vec3 m_Pos;

	Quaternion m_Rot;

	bool isDesotry = false;

	Array<ComponentPtr> components;

public:

	// ゲームオブジェクトを削除する
	inline void Desotory()
	{
		isDesotry = true;
	}

	// ゲームオブジェクト破壊されているか取得
	inline bool IsDestoryed() const
	{
		return isDesotry;
	}

	template<class T>
	std::shared_ptr<T> AddComponent()
	{
		auto p = std::make_shared<T>();
		p->owner = this;
		this->components.push_back(p); // コンポーネントをオブジェクトコンポーネントリストに追加
		p->Awake();
		return p;
	}

	// スタート関数
	virtual void Start();

	// 更新関数
	virtual void Update();

};
