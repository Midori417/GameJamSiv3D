#include "Play.hpp"
#include "../Object/Player.hpp"

Play::Play(const InitData& init)
	:IScene(init)
	, renderTexture(Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes)
	, camera(renderTexture.size(), 30_deg, Vec3(0, 5, -20))
{
	player.reset(new Player);
}

void Play::update()
{
	player->Update();
	camera.setView(player->GetPos() + player->GetQuaternion() * offsetPos, player->GetPos());
}

void Play::draw() const
{
	// [3D シーンの描画]
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(backGroundColor) };
		// カメラを設定
		Graphics3D::SetCameraTransform(camera);

		// [3Dモデルを描画]
		{
			// プレイヤーの描画
			{
				player->Draw();
			}
			// 床を描画
			Plane{ 64 }.draw(Palette::White);
		}
	}


	// [RenderTexture を 2D シーンに描画]
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}
}
