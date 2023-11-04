# include <Siv3D.hpp>
#include "App/My/Souce/System/MySystem.hpp"

void Main()
{
	// MySystemのインスタンスを取得
	auto mySystem = MySystem::GetInstance();

	// MySystemを実行
	mySystem->Run();

	// MySystemのインスタンスを破壊
	MySystem::DestoryInstance();
}
