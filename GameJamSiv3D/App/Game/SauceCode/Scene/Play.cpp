#include "Play.hpp"
#include "../Object/Player.hpp"
#include "../Object/PersonHelp.hpp"
#include "../Object/Meteo.hpp"
#include "../Object/UI.hpp"

Play::Play(const InitData& init)
	:IScene(init)
	, renderTexture(Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes)
	, camera(std::make_shared<BasicCamera3D>(renderTexture.size(), 30_deg, Vec3(0, 5, -20)))
{
	// プレイヤーをインスタンス化
	player = std::make_shared<Player>();

	ui = std::make_shared<UI>();

	// 助ける人たちをインスタンス化
	for (int i = 0; i < personHelpMax; ++i)
	{
		personHelps.push_back(std::make_shared<PersonHelp>());
	}
	for (int i = 0; i < meteoMax; ++i)
	{
		meteos.push_back(std::make_shared<Meteo>());
	}
}

void Play::update()
{
	player->SetCamera(camera);
	// プレイヤーの更新
	player->Update();
	// カメラの更新
	//camera.update(2.0);
	camera->setView(player->GetPos() + player->GetQuaternion() * offsetPos, player->GetPos());

	// 助ける人たちの更新
	for (auto x : personHelps)
	{
		if (!x->IsSave())
		{
			x->Update();
		}
	}

	for (auto x : meteos)
	{
		x->Update();
	}

	for (auto x : personHelps)
	{
		if (player->GetCollider().intersects(x->GetCollider()) && !x->IsSave())
		{
			x->SaveOk();
			ui->PersonPurasu();
		}
	}
	for (auto x : meteos)
	{
		if (player->GetCollider().intersects(x->GetCollider()))
		{
			player->HPDown();
		}
	}
	ui->SetHp(player->GetHP());
	ui->Update();
	if (ui->GetPersonHelp() >= 5)
	{
		changeScene(SceneState::Result);
	}
	if (player->GetHP() <= 0)
	{
		changeScene(SceneState::Result);

	}
}

void Play::draw() const
{
	// [3D シーンの描画]
	{
		const ScopedRenderTarget3D target{ renderTexture.clear(backGroundColor) };
		// カメラを設定
		Graphics3D::SetCameraTransform(*camera);

		// [3Dモデルを描画]
		{

			// 助ける人達の描画
			{
				for (auto x : personHelps)
				{
					if (!x->IsSave())
					{
						x->Draw();
					}
				}
			}

			// 惑星を描画
			{
				for (auto x : meteos)
				{
					x->Draw();
				}
			}
			// プレイヤーの描画
			{
				player->Draw();
			}
		}
	}


	// [RenderTexture を 2D シーンに描画]
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}

	// 2Dの描画
	{
		ui->Draw();
	}
}

