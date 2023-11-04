#pragma once
#include "../System/MySystem.hpp"

enum PlayerState
{
	defalt,
	muteki,
	death,
};

class Player : public Component
{
public:
	Player() = default;
	~Player() = default;

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other) override;
	void StartOk()
	{
		isStrat = true;
	}

	inline int8 GetLife() const
	{
		return life;
	}

	inline int8 GetPersonNum() const
	{
		return personNum;
	}

	inline double GetEnrgi() const
	{
		return  (boostGageMax - boostGage) / boostGageMax;
	}

private:

	// 移動速度
	float speed = 0;
	double rotateSpeed = 30_deg;
	const float speedMax = 20;
	Vec3 rot = Vec3::Zero();

	// 開始かどうか
	bool isStrat;

	// 残機
	int8 life = 3;

	// 助けた数
	int8 personNum = 0;

	// ブーストゲージ
	double boostGageMax = 10;
	double boostGage = 0;
	bool boostOk = true;


	// Shot
	double shotInterval = 0.5;
	double shotcurrentTime = 0;

	// Dmage
	const double damegeTime = 2;
	double damageCurrentTime = 0;

	// プレイヤーの状態
	PlayerState playerState = PlayerState::defalt;

	// Effect
	Effect effect3D;
	Mesh effectMesh;
};
