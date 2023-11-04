# pragma once
# include"Component.hpp"

// コライダー基底クラス
class Collider : public Component
{
public:

	Collider() = default;
	virtual ~Collider() = default;

};

using ColliderPtr = std::shared_ptr<Collider>;
