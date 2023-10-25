#pragma once

#include "Common.hpp"
#include "Player.hpp"
#include "UIInfo.hpp"

/// @brief ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init)
		: IScene(init)
		,renderTexture(Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes)
		, camera(renderTexture.size(), 30_deg, Vec3(0, 16, -20))
	{
	}

	~Game()
	{
	}

	void update() override
	{
		ClearPrint();
		// カメラを更新
		camera.update(2.0);
		// 3Dシーンにカメラを設定
		Graphics3D::SetCameraTransform(camera);

		// プレイヤーの更新処理
		player.Update();

		uiInfo.Update();
	}
	void draw() const override
	{

		// 3Dシーンの描画
		{
			// renderTextureを背景色で塗りつぶし
			// renderTextureを3D描画のレンダーターゲット
			const ScopedRenderTarget3D target(renderTexture.clear(backGroundColor));

			// 床を描画
			Plane(Vec3::Zero(), 20, 20).draw(uvChecker);

			// プレイヤーを描画
			player.Draw();
		}


		// 3Dシーンを2Dシーンに描画
		{
			// renderTextureをresoleveする前に3D描画を実行する
			Graphics3D::Flush();

			// マルチサンプル・テクスチャのリゾルブ
			renderTexture.resolve();

			// リニアレンダリングされた、renderTexturをシーンに転送
			Shader::LinearToScreen(renderTexture);
		}

		// 2Dシーンの描画
		{
			uiInfo.Draw();
		}
	}

private:

	// 背景色
	const ColorF backGroundColor = ColorF(0.1, 0.1, 0.2).removeSRGBCurve();

	// マルチサンプリング対応レンダーテクスチャ
	const MSRenderTexture renderTexture;

	// 3Dシーンのデバッグ用カメラ
	// 縦方向の視野角30°、カメラの位置(10, 16, -32)
	// 前後移動:[w][s]、左右移動[a][d]、上下移動:[e][x]、注視点移動: アローキー、加速[Shift][Ctrl]
	DebugCamera3D camera;

	// uvチェック用テクスチャ
	// (ミニマップ使用。リニアレンダリング時に正しく扱われるように、sRGBテクスチャであると明示)
	const Texture uvChecker = Texture(U"example/texture/uv.png", TextureDesc::MippedSRGB);

	Player player;
	UIInfo uiInfo;

};
