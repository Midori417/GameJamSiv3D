#pragma once

// 描画する順番
enum DrawState
{
	D3,			// 3D
	D2,			// 3D
	Effect		// Effect
};

// ゲームオブジェクトクラス
class GameObject
{
private:


	bool isDesotory = false;
	bool isStarted = false;

public:

	String name;

	Model m_Model;

	Vec3 m_Pos;

	Quaternion m_Rot;

	DrawState m_DrawState = DrawState::D2;
	
public:

	GameObject() = default;

	[[nodiscard]]
	bool IsDestroyed() const
	{
		return isDesotory;
	}

	void Desotry()
	{
		isDesotory = true;
	}

	// 最初のUpdateの前に呼び出す関数
	virtual void Start() {}

	// 毎フレーム一回呼び出す関数
	virtual void Update(){}

	// 描画関数
	virtual void Draw() const {}

};

using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = Array<GameObjectPtr>;
