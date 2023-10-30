#pragma once

class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = Array<GameObjectPtr>;

// システム(My)
class MySystem
{
private:

	GameObjectList gameObjects;
public:

	// コンストラクタ
	MySystem() = default;

	// アプリの実行
	void Run();

	template<class T>
	std::shared_ptr<T> CreateObject(const String& name, const Vec3& pos, const Quaternion& rot)
	{
		auto e = std::make_shared<T>();
		e->m_Name = name;
		e->m_Pos = pos;
		e->m_Rot = rot;

		gameObjects.push_back(e);
		return e;
	}


private:

	// 初期化関数
	void Initialize();

	// 更新関数
	void Update();

	// 描画関数
	void Draw() const;
};
