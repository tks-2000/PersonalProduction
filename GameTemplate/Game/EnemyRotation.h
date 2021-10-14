#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief 敵の回転を制御するクラス
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			void Init();
			const Quaternion& RotationExecute(const Vector3& speed);
		private:

			bool m_isInitd = false;

			Quaternion m_qRot = g_quatIdentity;

			/// @brief 角度
			float m_angle = 0.0f;
			/// @brief 変化する前の角度
			float m_oldAngle = 0.0f;
			/// @brief 角度の変化量
			float m_angleAmount = 0.0f;

			Enemy* m_enemy = nullptr;
		};
	}
}
