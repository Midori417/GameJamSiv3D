#pragma once
#include <Siv3D.hpp>

/// @brief オブジェクトの基本クラス
class Object
{
private:

	String name;
	bool isDestory = false;

public:

	Object() = default;
	~Object() = default;

	/// @brief オブジェクトの初期化関数
	virtual void Initialize();

	/// @brief オブジェクトの更新関数
	virtual void Update();

	// オブジェクトを破棄予定にする
	inline void Desotry() {
		isDestory = true;
	}

	// オブジェクトが破棄予定か取得
	inline bool IsDesotryed() const {
		return isDestory;
	}
};

using ObjectPtr = std::shared_ptr<Object>;
using ObjectList = std::vector<ObjectPtr>;
