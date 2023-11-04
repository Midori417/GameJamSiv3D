# pragma once
# include <Siv3D.hpp>
# include <unordered_map>
# include "../Scene/SceneCommon.hpp"
# include "GameObject.hpp"
# include "SystemComponent.hpp"

// システムクラス
class MySystem
{
private:

	MySystem() = default;
	~MySystem() = default;

public:

	// MySystemのインスタンスを取得
	static MySystem* GetInstance() {
		if (instance == nullptr)
		{
			instance = new MySystem;
		}
		return instance;
	}

	// 自身のインスタンスを破壊
	static void DestoryInstance() {
		delete instance;
	}

	// MySystemを実行
	void Run();

	// ゲームオブジェクトを作成
	template<class T>
	std::shared_ptr<T> Create(const String& name, const Vec3& position = Vec3(0,0,0), const Quaternion& rotation = Quaternion(0,0,0,1))
	{
		// T型のオブジェクトの作成
		std::shared_ptr<T> p = std::make_shared<T>();
		// オブジェクトの各パラメータを設定
		p->name = name;
		p->position = position;
		p->rotation = rotation;

		gameObjects.push_back(p);
		return p;
	}

	// UIゲームオブジェクトを作成
	template<class T>
	std::shared_ptr<T> CreateUI(const String& name, const Vec2& position = Vec2(0, 0))
	{
		// T型のオブジェクトの作成
		std::shared_ptr<T> p = std::make_shared<T>();
		// オブジェクトの各パラメータを設定
		p->name = name;
		p->position.x = position.x;
		p->position.y = position.y;
		p->position.z = 0;
		p->renderQueue = Dimension2D;

		gameObjects.push_back(p);
		return p;
	}


	// カメラを取得
	BasicCamera3D& GetMainCamera() {
		return camera;
	}
	const BasicCamera3D& GetMainCamera() const {
		return camera;
	}

	// すべてのゲームオブジェクトを破棄予定にする
	void AllClearGameObject();

	// モデルを取得
	std::shared_ptr<Model> GetModel(const String& name, const String& filename = U"")
	{
		auto itr = modelCache.find(name);
		if (itr != modelCache.end())
		{
			return itr->second;
		}
		auto model = std::make_shared<Model>(filename);
		modelCache.emplace(name, model);
		return model;
	}
	
	// フォントの取得
	std::shared_ptr<Font> GetFont(const String& name, int32 size = 24)
	{
		auto itr = fontCache.find(name);
		if (itr != fontCache.end())
		{
			return itr->second;
		}
		auto font = std::make_shared<Font>(size, Typeface::Bold);
		fontCache.emplace(name, font);
		return font;
	}

	// テクスチャの取得
	std::shared_ptr<Texture> GetTexture(const String& name, const String& filename = U"")
	{
		auto itr = textureCache.find(name);
		if (itr != textureCache.end())
		{
			return itr->second;
		}
		auto texure = std::make_shared<Texture>(filename);
		textureCache.emplace(name, texure);
		return texure;
	}

	std::shared_ptr<Mesh> GetBillMesh()
	{
		meshBillbord = std::make_shared<Mesh>(MeshData::Billboard());
		return meshBillbord;
	}

	std::shared_ptr<Audio> GetAudio(const String& name, const String& filename = U"", bool loop = false)
	{
		auto itr = audioCache.find(name);
		if (itr != audioCache.end())
		{
			return itr->second;
		}
		auto audio = std::make_shared<Audio>(filename, loop ? Loop::Yes : Loop::No);
		audioCache.emplace(name, audio);
		return audio;
	}
private:

	// 初期化関数
	void Initialize();

	// 更新関数
	void Update();

	// 描画関数
	void Render();

	// オブジェクトを更新
	void UpdateObject();

	// オブジェクトを描画
	void DrawObject(GameObjectList::iterator begin, GameObjectList::iterator end);

	// 破棄予定のゲームオブジェクトを削除
	void RemoveDestroyObject();

	// ゲームオブジェクト同士の衝突判定
	void HandleGameObjectCollision();

	struct WorldCollider
	{
		ColliderPtr origin;
	};
	using WorldColliderList = Array<WorldCollider>;

	// コライダー単位の衝突判定
	void HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b);

private:

	// 自身のインスタンス
	static MySystem* instance;

	// レンダーテクスチャ
	MSRenderTexture renderTexture;

	// 背景色
	const ColorF backGroundColor = ColorF(0.1, 0.1, 0.3).removeSRGBCurve();

	// ゲームオブジェクト配列
	GameObjectList gameObjects;

	// カメラ
	BasicCamera3D camera;

	// デバッグ用カメラ
	DebugCamera3D debugCamera;

	// モデル配列
	std::unordered_map<String, std::shared_ptr<Model>> modelCache;

	// フォント配列
	std::unordered_map<String, std::shared_ptr<Font>> fontCache;

	// Texture配列
	std::unordered_map<String, std::shared_ptr<Texture>> textureCache;

	std::shared_ptr<Mesh> meshBillbord;

	// Audio配列
	std::unordered_map<String, std::shared_ptr<Audio>> audioCache;

	// シーンマネージャー
	App sceneManager;
};
