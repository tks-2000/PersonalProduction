#include "stdafx.h"
#include "MiniMap.h"
namespace mainGame {
	namespace map {

		const Vector3 MINI_MAP_CAMERA_POS = { 0.0f,2000.0f,0.0f };

		const Vector3 MINI_MAP_POS = { 500.0f,200.0f,0.0f };

		const float FRICTION = 20.0f;

		const Vector3 MINI_MAP_TPS_CAMERA_UP = { 0.0f,0.0f,1.0f };

		MiniMap::MiniMap()
		{
			//未初期化で開始
			m_isInitd = false;
			m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		}

		MiniMap::~MiniMap()
		{
		
			m_renderingEngine->DeleteExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP);
			m_renderingEngine->DeleteExpansionModelsRenderTarget(MINI_MAP_RENDER_GROUP);
			//マップ画像を削除
			DeleteGO(m_miniMapSprite);
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

			//マップを映すカメラの初期化
			m_mapCameraPos = MINI_MAP_CAMERA_POS;
			m_miniMapCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
			m_miniMapCamera.SetWidth(1500.0f);
			m_miniMapCamera.SetHeight(1500.0f);
			m_miniMapCamera.SetTarget({ 0.0f, 0.0f, 0.0f });
			m_miniMapCamera.SetUp(m_mapCameraUp);
			m_miniMapCamera.SetPosition(m_mapCameraPos);

			//マップに表示するモデルを描画するレンダリングターゲットを作成
			m_miniMapRenderTarget.Create(
				128,
				128,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			m_renderingEngine->SetExpansionModlsRenderTarget(MINI_MAP_RENDER_GROUP, &m_miniMapRenderTarget);

			//マップ画像を作成
			m_miniMapSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapSprite->InitTexture(&m_miniMapRenderTarget.GetRenderTargetTexture(), 128, 128);
			m_miniMapSprite->SetRotation(m_spriteQrot);
			m_miniMapSprite->SetPosition(MINI_MAP_POS);

			//レンダリングエンジンに自身の情報を渡す
			m_renderingEngine->SetExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP, &m_miniMapCamera);

			m_isInitd = true;
		}

		void MiniMap::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//カメラの角度からマップ画像の回転角度を求める
			float angle = m_gameCamera->GetCameraYAngleAmount() - m_spriteAngle;

			if (m_gameCamera->GetCameraMode() == enCameraModeTps) {
				//m_mapCameraUp = MINI_MAP_TPS_CAMERA_UP;
				m_gameCamera->GetCameraYRot().Apply(m_mapCameraUp);
			}
			else {
				Vector3 up = m_gameCamera->GetCameraTarget() - m_gameCamera->GetCameraPos();
				up.y = 0.0f;
				up.Normalize();
				m_mapCameraUp = up;
			}

			//カメラの角度との差がカメラの移動停止距離以下だったら…
			if (angle < m_gameCamera->GetCameraMoveStopDistance()) {
				//角度をそのまま足す
				m_spriteAngle += angle;
			}
			//そうでないなら…
			else {
				//角度に摩擦力を加えた物を足す
				m_spriteAngle += angle / m_gameCamera->GetCameraFriction();
			}

			//画像の回転を決める
			m_spriteQrot.SetRotationZ(m_spriteAngle);

			//画像を更新
			//m_miniMapSprite->SetRotation(m_spriteQrot);
			m_miniMapSprite->Execute();

			m_miniMapPos = m_player->GetPlayerPosition();
			m_miniMapCamera.SetTarget(m_player->GetPlayerPosition());
			m_miniMapPos.y += 1000.0f;

			m_miniMapCamera.SetPosition(m_miniMapPos);
			m_miniMapCamera.SetUp(m_mapCameraUp);
			//マップを映すカメラを更新
			m_miniMapCamera.Update();
		}

		void MiniMap::MapRender(RenderContext& rc)
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//マップ用のレンダリングターゲットを設定
			rc.WaitUntilToPossibleSetRenderTarget(m_miniMapRenderTarget);
			rc.SetRenderTargetAndViewport(m_miniMapRenderTarget);
			rc.ClearRenderTargetView(m_miniMapRenderTarget);

			//マップ用のモデルを全てドローする
			for (int modelNum = 0; modelNum < m_drawModels.size(); modelNum++) {
				m_drawModels[modelNum]->Draw(rc, m_miniMapCamera);
			}

			//レンダリングターゲットへ書き込み終了
			rc.WaitUntilFinishDrawingToRenderTarget(m_miniMapRenderTarget);

			// レンダリングターゲットをフレームバッファに戻す
			rc.SetRenderTarget(
				g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
				g_graphicsEngine->GetCurrentFrameBuffuerDSV()
			);
			rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
		}
	}
}