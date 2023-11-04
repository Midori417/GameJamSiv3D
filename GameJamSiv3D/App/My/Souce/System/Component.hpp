# pragma once
# include <Siv3D.hpp>

// 先行宣言
class GameObject;
class Component;
using ComponentPtr = std::shared_ptr<Component>;

// コンポーネントの基底クラス
class Component
{
	friend GameObject;

public:

	// コンストラクタ
	Component() = default;

	// デストラクタ
	virtual ~Component() = default;


	// コンポーネントの所有者を取得
	GameObject* GetOwner() const {
		return owner;
	}

	// コンポーネントをゲームオブジェクトから削除する
	void Destroy() {
		isDesotryed = true;
	}

	// コンポーネントが破壊されているか取得
	bool IsDestroyed() const {
		return isDesotryed;
	}

	virtual void Awake(){}
	virtual void Start(){}
	virtual void Update(){}
	virtual void Draw(){}
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other) {}
	virtual void OnDestroy(){}

private:

	GameObject* owner = nullptr;
	bool isStarted = false;
	bool isDesotryed = false;

};

