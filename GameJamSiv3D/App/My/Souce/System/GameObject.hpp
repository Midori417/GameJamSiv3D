# pragma once
# include "Component.hpp"
# include "Collider.hpp"


// 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;

// 描画順
enum RenderQueue
{
	Dimension3D,
	Effect3D,
	Dimension2D,
};

// ゲームオブジェクトクラス
class GameObject
{
	friend class MySystem;

public:

	// コンストラクタ・デストラクタ
	GameObject() = default;
	virtual ~GameObject();

	// コピーと代入を禁止
	GameObject(GameObject&) = delete;
	GameObject& operator = (GameObject&) = delete;


	// ゲームオブジェクトを破棄予定にする
	inline void Destroy() {
		isDestroy = true;
	}

	// ゲームオブジェクトが破棄予定か取得
	inline bool IsDestoryed() const {
		return isDestroy;
	}

	//　ゲームオブジェクトにコンポーネントを追加
	template<typename T>
	std::shared_ptr<T> AddComponent() {
		auto p = std::make_shared<T>();
		p->owner = this;
		if constexpr (std::is_base_of_v<Collider, T>)
		{
			colliders.push_back(p);	// コンポーネントをオブジェクトコライダーリストに追加
		}
		this->components.push_back(p); // コンポーネントをオブジェクトコンポーネントリストに追加
		p->Awake();
		return p;
	}

	// コンポーネントを検索する
	template <typename T>
	std::shared_ptr<T> GetComponent() {
		if constexpr (std::is_base_of_v<Collider, T>)
		{
			for (auto& e : colliders) {
				auto p = std::dynamic_pointer_cast<T>(e);
				if (p) {
					return p;
				}
			}
		}

		for (auto& e : components)
		{
			auto p = std::dynamic_pointer_cast<T>(e);
			if (p) {
				return p;
			}
		}

		return nullptr;
	}

	// 親オブジェクトを取得する
	inline GameObject* GetParent() const
	{
		return parent;
	}

	// 親オブジェクトを設定する
	void SetParent(GameObject* parent);
	void SetParent(const GameObjectPtr& parent);

	// 子オブジェクトの数を取得する
	inline size_t GetChildCount() const {
		return children.size();
	}

	// 子オブジェクトを取得する
	inline GameObject* GetChild(size_t index) const {
		return children[index];
	}

private:

	/// <summary>
	/// コンポーネントをゲームオブジェクトから削除する
	/// </summary>
	void RemoveDestoryedComponent();

	// スタート関数
	virtual void Start();

	// 更新関数
	virtual void Update();

	// 描画関数
	virtual void Draw();

	// 衝突関数
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other);

	// 削除関数
	virtual void OnDestroy();

public:

	// 名前
	String name;

	// 位置
 	Vec3 position = Vec3::Zero();

	// 回転
	Quaternion rotation = Quaternion::Zero();

	// 描画順
	int32 renderQueue = Dimension3D;

private:

	// 破壊予定
	bool isDestroyTime = false;
	bool isDestroy = false;

	// コンポーネント配列
	Array<ComponentPtr> components;
	Array<ColliderPtr> colliders;

	// 親
	GameObject* parent = nullptr;
	Array<GameObject*> children;
};

using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = Array<GameObjectPtr>;
