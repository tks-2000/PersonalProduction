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

			float GetAngleAmount() { return m_playerRot.GetAngleAmount(); }
			void ResetAngle(){ m_playerRot.AngleReset(); }

		private:

			Vector3 m_position = g_vec3Zero;

			Quaternion m_qRot = g_quatIdentity;

			Render::SkinModelRender* m_playerModel = nullptr;

			PlayerStates m_playerState = enPlayerIdle;

			Animation m_playerAnimation;

			Move m_playerMove;

			Rotation m_playerRot;
		};
	}
}
