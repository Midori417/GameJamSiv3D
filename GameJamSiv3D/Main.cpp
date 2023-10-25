#include <Siv3D.hpp>
#include "Game/SpaceRescue.hpp"

void Main()
{
	Window::Resize(1000, 700);
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);


	// シーンマネージャーの作成
	App manager;

	// タイトルシーンを登録
	manager.add<Title>(State::Title);
	
	// ゲームシーンを登録
	manager.add<Game>(State::Game);

	manager.init(State::Game);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
