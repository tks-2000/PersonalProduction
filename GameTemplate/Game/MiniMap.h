#pragma once

class RenderingEngine;

namespace mainGame {

	namespace player {
		class Player;
	}

	class GameCamera;

	namespace ui {
		class MiniMap
		{
		public:
			MiniMap();
			~MiniMap();

			/// @brief	初期化
			void Init();
			/// @brief 実行
			void Execution();

			/// @brief マップに表示するモデルを追加
			/// @param model マップに表示するモデルのアドレス
			void SetDrawModel(Model* model);

			/// @brief マップに表示しているモデルを削除
			/// @param model 削除するモデルのアドレス
			void DeleteDrawModel(Model* model);

			/// @brief マップにモデルを書き込む
			/// @param rc レンダリングコンテキスト
			void MapRender(RenderContext& rc);

			void SetMapCameraUp(const Vector3& up) { m_mapCameraUp = up; }

			void HideUI();
		
		private:

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief ミニマップの表示座標
			Vector3 m_miniMapPos = g_vec3Zero;
			/// @brief マップカメラの座標
			Vector3 m_mapCameraPos = g_vec3Zero;
			/// @brief マップカメラの上方向
			Vector3 m_mapCameraUp = { 0.0f,0.0f,1.0f };
			/// @brief マップ画像の回転
			float m_spriteAngle = 0.0f;

			/// @brief マップを描画するレンダリングターゲット
			RenderTarget m_miniMapRenderTarget;
			/// @brief マップを表示するためのカメラ
			Camera m_miniMapCamera;
			/// @brief マップに表示するモデルの配列
			std::vector<Model*> m_drawModels;
			/// @brief マップ画像
			render::sprite::SpriteRender* m_miniMapSprite = nullptr;
			render::sprite::SpriteRender* m_miniMapBase = nullptr;
			render::sprite::SpriteRender* m_miniMapFrame = nullptr;
			/// @brief マップ画像の回転
			Quaternion m_spriteQrot = g_quatIdentity;
			/// @brief ゲームカメラ
			GameCamera* m_gameCamera = nullptr;
			/// @brief レンダリングエンジン
			render::RenderingEngine* m_renderingEngine = nullptr;

			player::Player* m_player = nullptr;
		};
	}
}