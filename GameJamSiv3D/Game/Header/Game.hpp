#pragma once

#include "Common.hpp"

/// @brief ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init)
		: IScene(init)
		, m_Texture(U"🚀"_emoji)
		,renderTexture(Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes)
	{
		debugCamera = DebugCamera3D(renderTexture.size(), 30_deg, Vec3(10, 16, -32));
	}

	~Game()
	{
	}

	void update() override
	{
		ClearPrint();
		//デバッグカメラの更新(移動スピード:2.0)
		debugCamera.update(2.0);
		Print << U"eyePositon: {:.1f}"_fmt(debugCamera.getEyePosition());
		Print << U"focusPosition: {:.1f}"_fmt(debugCamera.getFocusPosition());
		Print << U"verticalFOV: {:.1f}°"_fmt(Math::ToDegrees(debugCamera.getVerticalFOV()));
		// 3Dシーンにカメラを設定
		Graphics3D::SetCameraTransform(debugCamera);


		// 左クリックで
		if (MouseL.down()) {
			// ゲームシーンに変更
			changeScene(State::Title);
		}
	}
	void draw() const override
	{
		// 3Dの描画
		{
			// renderTextureを背景色で塗りつぶし
			// renderTextureを3D描画のレンダーターゲット
			const ScopedRenderTarget3D target(renderTexture.clear(backgroundColor));

			// 床を描画
			Plane(64).draw(uvChecker);

			// 球体の描画
			// 中心8(0,2,0)半径が2の球にテクスチャを張り付ける
			Sphere(0, 2, 0, 2).draw(earthTexture);

			// ボックスを描画
			Box(-8, 2, 0, 4).draw(ColorF(0.8, 0.6, 0.4).removeSRGBCurve());


			// 2 点を指定して直方体を作成
			Cylinder(Vec3{ -8, 2, -8 }, Vec3{ 0, 0, -12 }, 0.5).draw();
			Cylinder(Vec3{ 0, 2, -8 }, Vec3{ 4, 0, -16 }, 5).draw();
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
	}

private:

	const ColorF backgroundColor = ColorF(0.4, 0.6, 0.8).removeSRGBCurve();
	Texture m_Texture;
	MSRenderTexture renderTexture;
	DebugCamera3D debugCamera;
	// uvチェック用テクスチャ
	// (ミニマップ使用。リニアレンダリング時に正しく扱われるように、sRGBテクスチャであると明示)
	const Texture uvChecker = Texture(U"example/texture/uv.png", TextureDesc::MippedSRGB);

	// 地球テクスチャ
	const Texture earthTexture = Texture(U"example/texture/earth.jpg", TextureDesc::MippedSRGB);


};
