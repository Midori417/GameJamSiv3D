# include "GameObject.hpp"

GameObject::~GameObject()
{
	// 死ぬ前に親子関係を解除する
	SetParent(nullptr);
	for (auto child : children) {
		child->parent = nullptr;
	}
}

void GameObject::SetParent(GameObject* parent)
{
	// 同じ親を指定された場合は何もしない
	if (parent == this->parent)
	{
		return;
	}

	// 別の親がある場合、その親との関係を解除
	if (this->parent)
	{
		// 自分の位置を検索
		auto& c = this->parent->children;
		auto itr = std::find(c.begin(), c.end(), this);
		if (itr != c.end()) {
			c.erase(itr);	// 配列から自分を削除
		}
	}

	// あらたな親子関係を設定
	if (parent) {
		parent->children.push_back(this);
	}
	this->parent = parent;
}

void GameObject::SetParent(const GameObjectPtr& parent)
{
	SetParent(parent.get());
}

void GameObject::RemoveDestoryedComponent()
{
	if (this->components.empty() == true)
	{
		return;	//　コンポーネントを持っていなければ何もしない
	}

	// 破棄予定の有無でコンポーネントを分ける
	// stable_partition 戻り値条件を満たさない要素範囲の先頭位置
	const auto iter = std::stable_partition(this->components.begin(), this->components.end(),
		[](const auto& p) {return !p->IsDestroyed(); });

	// 破棄予定のコンポーネントを別の配列に移動
	std::vector<ComponentPtr> destroyList(
		std::move_iterator(iter), // 先ほど分けられた条件を満たさない要素の先頭位置
		std::move_iterator(this->components.end()));

	// 配列から破棄予定の配列に移動したコンポーネントを削除
	this->components.erase(iter, this->components.end());

	// 破棄予定のコンポーネントのOnDestoryを実行
	for (auto& e : destroyList)
	{
		e->OnDestroy();
	}

	// ここで実際にコンポーネントが削除される(desotryListの寿命が終わるため)
}

void GameObject::Start()
{
	for (auto& e : this->components)
	{
		if (!e->isStarted)
		{
			e->Start();

			e->isStarted = true;
		}
	}
}

void GameObject::Update()
{
	for (auto& e : this->components)
	{
		e->Update();
	}
	// 削除予定のコンポーネントを削除する
	RemoveDestoryedComponent();
}

void GameObject::Draw()
{
	for (auto& e : components)
	{
		e->Draw();
	}
}

void GameObject::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
{
	for (auto& e : this->components)
	{
		e->OnCollision(self, other);
	}
}

void GameObject::OnDestroy()
{
	for (auto& e : this->components)
	{
		e->OnDestroy();
	}
}
