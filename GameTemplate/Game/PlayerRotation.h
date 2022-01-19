#pragma once

namespace mainGame {

	class GameCamera;

	namespace player {

		class Player;

		/// @brief プレイヤーの回転を制御するクラス
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			/// @brief 初期化
			/// @param pl 処理を適用するプレイヤーのアドレス
			void Init(Player* pl);

			/// @brief 回転クォータニオンを取得
			/// @param moveSpeed 回転させるための移動速度
			/// @return 速度によって決まった回転クォータニオン
			const Quaternion& RotationExecution(const Vector3& moveSpeed);

			const Quaternion& GetRotation() { return m_qRot; }

			const Vector3& GetDirection() { return m_direction; }

			const float GetAngle() { return m_angle; }

			/// @brief 回転角度の変化量を取得
			/// @return 角度の変化量
			const float GetAngleAmount() { return m_angleAmount; }

			/// @brief 角度の変化量を元に戻す
			void AngleReset() { m_angleAmount = 0.0f; }
		private:
			/// @brief Tpsカメラの時の回転を取得
			/// @param moveSpeed 移動速度
			/// @return 移動速度に応じた回転クォータニオン
			const Quaternion& TpsRotationExecution(const Vector3& moveSpeed);

			/// @brief Fpsカメラの時の回転を取得
			/// @return カメラの向きに応じた回転クォータニオン
			const Quaternion& FpsRotationExecution();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief プレイヤーの向いている方向
			Vector3 m_direction = g_vec3Zero;
			/// @brief 回転クォータニオン
			Quaternion m_qRot = g_quatIdentity;
			/// @brief 角度
			float m_angle = 0.0f;
			/// @brief 変化する前の角度
			float m_oldAngle = 0.0f;
			/// @brief 角度の変化量
			float m_angleAmount = 0.0f;
			/// @brief プレイヤークラス
			Player* m_player = nullptr;
			/// @brief ゲームカメラ
			GameCamera* m_gameCamera = nullptr;
		};
	}
}