#pragma once

class SkinModelRender;

namespace mainGame {
	namespace stage {
		/// @brief ステージの情報をまとめたクラス
		class Stage : public IGameObject
		{
		public:
			Stage();
			~Stage();
			/// @brief	初期化
			void Init();
			/// @brief 実行
			void Execution();
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 回転
			Quaternion m_qRot = g_quatIdentity;
			/// @brief 拡大率
			Vector3 m_scale = g_vec3One;
			/// @brief ステージモデル
			render::model::SkinModelRender* m_stageModel = nullptr;
			/// @brief 静的物理オブジェクト
			PhysicsStaticObject m_staticStageObject;
			/// @brief 背景モデル
			render::model::SkinModelRender* m_bgModel = nullptr;
			/// @brief ミニマップモデル
			render::model::SkinModelRender* m_miniMapModel = nullptr;
			/// @brief ステージのサウンドID
			int m_stageSoundID = 0;
			/// @brief サウンドプレイヤー
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief ゲームシーン
			GameScene* m_gameScene = nullptr;
		};
	}
}
