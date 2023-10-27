#pragma once
#include "GameObject.hpp"

class ObjectManager
{
	friend class Game;

private:

	GameObjectList gameObjects;

	static ObjectManager* instance;

private:

	ObjectManager() = default;

	void Initialize();

	void Update();

	void RemoveDestroyGameObject();

public:

	static ObjectManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ObjectManager;
		}
		return instance;
	}

	static void DesotryInstance()
	{
		delete instance;
	}

	template<class T>
	std::shared_ptr<T> Create(const String& name, const Vec3& pos = Vec3::Zero(), const Quaternion& rot = Quaternion::zero)
	{
		// T型のオブジェクトの作成
		std::shared_ptr<T> p = std::make_shared<T>();
		// オブジェクトの各パラメータを設定
		p->name = name;
		p->m_Pos = pos;
		p->m_Rot = rot;

		gameObjects.push_back(p);
		return p;
	}

	void GameObjectAllClear();

};
