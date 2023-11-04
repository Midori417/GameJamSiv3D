# include "UFO.hpp"

void UFO::Update()
{
	// 上下に揺らす
	UpDown();

	// 前方に移動
	Move();
}

void UFO::UpDown()
{
	// コンポーネントの持ち主
	GameObject* ufo = GetOwner();

	auto deltaTime = Scene::DeltaTime();

	// 初期位置に合わせた上下移動
	ufo->position.y = startY + cos(radian) * radius;
	radian += deltaTime * upDownSpeed;


	// 増えすぎないように調整
	if (radian > 360_deg)
	{
		radian = 0;
	}
}

void UFO::Move()
{
	auto deltaTime = Scene::DeltaTime();

	// 一定時間経過で向きを変更する

	// コンポーネントの持ち主
	GameObject* ufo = GetOwner();

	// 経過時間を計測
	timer += deltaTime;

	// 一定時間経過で向きを変更する
	if (timer >= rotateInterval)
	{
		// 乱数で向きを決める
		speed.x = Random(-maxSpeed, maxSpeed);
		speed.z = Random(-maxSpeed, maxSpeed);

		// 経過時間をリセット
		timer = 0;
	}

	// 移動
	ufo->position.x -= speed.x * deltaTime;
	ufo->position.z -= speed.z * deltaTime;
}
