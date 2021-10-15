#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief “G‚Ì‰ñ“]‚ğ§Œä‚·‚éƒNƒ‰ƒX
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			void Init(const int num);
			const Quaternion& RotationExecute(const Vector3& speed);
		private:

			bool m_isInitd = false;

			Quaternion m_qRot = g_quatIdentity;

			/// @brief Šp“x
			float m_angle = 0.0f;
			/// @brief •Ï‰»‚·‚é‘O‚ÌŠp“x
			float m_oldAngle = 0.0f;
			/// @brief Šp“x‚Ì•Ï‰»—Ê
			float m_angleAmount = 0.0f;

			Enemy* m_enemy = nullptr;
		};
	}
}
