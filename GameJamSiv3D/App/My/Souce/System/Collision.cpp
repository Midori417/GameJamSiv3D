# include "Collision.hpp"

bool Intersect(const Sphere& a, const Sphere& b)
{
	// 中心の間の距離2乗を計算
	// aの中心からbの中心に向かうベクトル
	const Vec3 v = Vec3(
		b.x - a.x,
		b.y - a.y,
		b.z - a.z
	);
	const float d2 = static_cast<float>(v.dot(v)); // vの長さの二乗

	// d2が半径の合計より長い場合は交差していない
	const float  r = static_cast<float>(a.r + b.r);	// aとbの半径の合計
	if (d2 > r * r) { // 平方根を避けるため、二条同士で比較する
		return false;
	}

	// 交差しているので貫通ベクトルを求める
	//const float d = sqrt(d2);	// 「長さの二乗」ｗ「長さに変換」
	//const float t = (r - d) / d;	// 「半径の合計 - 長さ」の「長さに対する比率」を求める
	//penetration = v * t;	// 貫通ベクトルを計算
	return true;
}
