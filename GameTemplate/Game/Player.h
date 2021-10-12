#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"

class SkinModelRender;


namespace mainGame {
	namespace player {
		
		/// @brief プレイヤーの状態を決める列挙型
		enum EnPlayerStates {
			enPlayerIdle,
			enPlayerWark,
			enPlayerRun,
			enPlayerDamage,
			enPlayerStateNum
		};

		class Player : public IGameObject
		{
		public:
			Player();
			~Player();
			bool Start();
			void Update();

			void SetPlayerState(const EnPlayerStates& plState) { m_playerState = plState; }

			/// @brief プレイヤーの状態を入手
			/// @return プレイヤーのステータス
			const EnPlayerStates& GetPlayerStatus() { return m_playerState; }

			/// @brief プレイヤーの座標を入手
			/// @return プレイヤーの座標のconst参照
			const Vector3& GetPlayerPosition() { return m_position; }

			/// @brief プレイヤーの回転角度の変化量を入手
			/// @return プレイヤーの回転角度の変化量
			float GetAngleAmount() { return m_playerRot.GetAngleAmount(); }

			/// @brief プレイヤーの回転角度変化量を元に戻す
			void ResetAngle(){ m_playerRot.AngleReset(); }

			/// @brief 実行
			void Execution();

		private:
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 回転
			Quaternion m_qRot = g_quatIdentity;
			/// @brief モデル
			render::model::SkinModelRender* m_playerModel = nullptr;
			/// @brief ステート
			EnPlayerStates m_playerState = enPlayerIdle;
			/// @brief アニメーション
			Animation m_playerAnimation;
			/// @brief 移動
			Move m_playerMove;
			/// @brief 回転
			Rotation m_playerRot;
		};
	}
}
