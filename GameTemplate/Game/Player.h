#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"

class SkinModelRender;


namespace MainGame {
	namespace Player {
		class Animation;

		/// @brief プレイヤーの状態を決める列挙型
		enum PlayerStates {
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

			void SetPlayerState(const PlayerStates& plState) { m_playerState = plState; }

			/// @brief プレイヤーの状態を入手
			/// @return プレイヤーのステータス
			const PlayerStates& GetPlayerStatus() { return m_playerState; }

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
			Render::SkinModelRender* m_playerModel = nullptr;
			/// @brief ステート
			PlayerStates m_playerState = enPlayerIdle;
			/// @brief アニメーション
			Animation m_playerAnimation;
			/// @brief 移動
			Move m_playerMove;
			/// @brief 回転
			Rotation m_playerRot;
		};
	}
}
