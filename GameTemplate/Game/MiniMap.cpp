#include "stdafx.h"
#include "MiniMap.h"
namespace mainGame {
	namespace ui {
		/// @brief ミニマップカメラの座標
		const Vector3 MINI_MAP_CAMERA_POS = { 0.0f,2000.0f,0.0f };
		/// @brief ミニマップカメラの高さ
		const float MINI_MAP_CAMERA_POS_HEIGHT = 1000.0f;
		/// @brief ミニマップカメラの映す横幅
		const float MINI_MAP_CAMERA_WIDTH = 1500.0f;
		/// @brief ミニマップカメラの映す縦幅
		const float MINI_MAP_CAMERA_HEIGHT = 1500.0f;
		/// @brief ミニマップの横幅
		const int MINI_MAP_WIDTH = 128;
		/// @brief ミニマップの縦幅
		const int MINI_MAP_HEIGHT = 128;
		/// @brief ミニマップの座標
		const Vector3 MINI_MAP_POS = { -500.0f,-220.0f,0.0f };
		/// @brief ミニマップの下地画像のファイルパス
		const char* MINI_MAP_BASE_FILEPATH = "Assets/Image/base_sprite_3.dds";
		/// @brief ミニマップの下地画像の横幅
		const int MINI_MAP_BASE_WIDTH = 300;
		/// @brief ミニマップの下地画像の縦幅
		const int MINI_MAP_BASE_HEIGHT = 520;
		/// @brief ミニマップの下地画像のカラー
		const Vector4 MINI_MAP_BASE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief ミニマップの枠画像のファイルパス
		const char* MINI_MAP_FRAME_FILEPATH = "Assets/Image/base_sprite_4.dds";
		/// @brief ミニマップの枠画像の横幅
		const int MINI_MAP_FRAME_WIDTH = 290;
		/// @brief ミニマップの枠画像の縦幅
		const int MINI_MAP_FRAME_HEIGHT = 480;

		MiniMap::MiniMap()
		{
			//未初期化で開始
			m_isInitd = false;
			
		}

		MiniMap::~MiniMap()
		{
			//ミニマップ描画に使ったレンダリングターゲットを消す
			m_renderingEngine->DeleteExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP);
			m_renderingEngine->DeleteExpansionModelsRenderTarget(MINI_MAP_RENDER_GROUP);
			//マップ画像を削除
			DeleteGO(m_miniMapSprite);
			DeleteGO(m_miniMapBase);
			DeleteGO(m_miniMapFrame);
		}

		void MiniMap::Init()
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//必要なデータを持って来る
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_player = FindGO<player::Player>(player::PLAYER_NAME);
			m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);

			//マップを映すカメラの初期化
			m_mapCameraPos = MINI_MAP_CAMERA_POS;
			m_miniMapCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
			m_miniMapCamera.SetWidth(MINI_MAP_CAMERA_WIDTH);
			m_miniMapCamera.SetHeight(MINI_MAP_CAMERA_HEIGHT);
			m_miniMapCamera.SetTarget(m_player->GetPlayerPosition());
			m_miniMapCamera.SetUp(m_mapCameraUp);
			m_miniMapCamera.SetPosition(m_mapCameraPos);

			//マップに表示するモデルを描画するレンダリングターゲットを作成
			m_miniMapRenderTarget.Create(
				MINI_MAP_WIDTH,
				MINI_MAP_HEIGHT,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			//マップ用のレンダリングターゲットとカメラをレンダリングエンジンに渡す
			m_renderingEngine->SetExpansionModlsRenderTarget(MINI_MAP_RENDER_GROUP, &m_miniMapRenderTarget);
			m_renderingEngine->SetExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP, &m_miniMapCamera);

			//ミニマップの下地画像を作成
			m_miniMapBase = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapBase->Init(MINI_MAP_BASE_FILEPATH, MINI_MAP_BASE_WIDTH, MINI_MAP_BASE_HEIGHT);
			m_miniMapBase->SetPosition(MINI_MAP_POS);
			m_miniMapBase->SetColor(MINI_MAP_BASE_COLOR);

			//ミニマップの枠画像を作成
			m_miniMapFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapFrame->Init(MINI_MAP_FRAME_FILEPATH, MINI_MAP_FRAME_WIDTH, MINI_MAP_FRAME_HEIGHT);
			m_miniMapFrame->SetPosition(MINI_MAP_POS);

			//ミニマップ画像を作成
			m_miniMapSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapSprite->InitTexture(&m_miniMapRenderTarget.GetRenderTargetTexture(), MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
			m_miniMapSprite->SetPosition(MINI_MAP_POS);

			//初期化完了
			m_isInitd = true;
		}

		void MiniMap::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//画像を更新
			m_miniMapSprite->Execute();
			m_miniMapBase->Execute();
			m_miniMapFrame->Execute();

			//マップカメラの注視点と座標を更新
			m_mapCameraPos = m_player->GetPlayerPosition();
			m_miniMapCamera.SetTarget(m_player->GetPlayerPosition());
			m_mapCameraPos.y += MINI_MAP_CAMERA_POS_HEIGHT;
			m_miniMapCamera.SetPosition(m_mapCameraPos);

			//マップカメラの上方向を更新
			m_mapCameraUp = m_gameCamera->GetCameraGazePointPos() - m_gameCamera->GetCameraPos();
			m_mapCameraUp.Normalize();
			m_miniMapCamera.SetUp(m_mapCameraUp);

			//マップを映すカメラを更新
			m_miniMapCamera.Update();
		}

		void MiniMap::HideUI()
		{
			//表示しているUIを全て透明にする
			m_miniMapSprite->SetColor(render::COLORLESS);
			m_miniMapBase->SetColor(render::COLORLESS);
			m_miniMapFrame->SetColor(render::COLORLESS);
		}
	}
}