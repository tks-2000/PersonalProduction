#pragma once

class RenderingEngine;

namespace mainGame {

	namespace player {
		class Player;
	}

	class GameCamera;

	namespace ui {
		/// @brief ミニマップ画像を表示するクラス
		class MiniMap
		{
		public:
			MiniMap();
			~MiniMap();

			/// @brief	初期化
			void Init();
			/// @brief 実行
			void Execution();
			/// @brief マップカメラの上方向を設定
			/// @param up 
			void SetMapCameraUp(const Vector3& up) { m_mapCameraUp = up; }
			/// @brief UIを非表示
			void HideUI();
		
		private:

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief マップカメラの座標
			Vector3 m_mapCameraPos = g_vec3Zero;
			/// @brief マップカメラの上方向
			Vector3 m_mapCameraUp = { 0.0f,0.0f,1.0f };
			/// @brief マップを描画するレンダリングターゲット
			RenderTarget m_miniMapRenderTarget;
			/// @brief マップを表示するためのカメラ
			Camera m_miniMapCamera;
			/// @brief マップ画像
			render::sprite::SpriteRender* m_miniMapSprite = nullptr;
			/// @brief マップの下地画像
			render::sprite::SpriteRender* m_miniMapBase = nullptr;
			/// @brief マップの枠画像
			render::sprite::SpriteRender* m_miniMapFrame = nullptr;
			/// @brief ゲームカメラ
			GameCamera* m_gameCamera = nullptr;
			/// @brief レンダリングエンジン
			render::RenderingEngine* m_renderingEngine = nullptr;
			/// @brief プレイヤー
			player::Player* m_player = nullptr;
		};
	}
}