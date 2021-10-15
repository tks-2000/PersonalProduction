#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief �G�̉�]�𐧌䂷��N���X
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

			/// @brief �p�x
			float m_angle = 0.0f;
			/// @brief �ω�����O�̊p�x
			float m_oldAngle = 0.0f;
			/// @brief �p�x�̕ω���
			float m_angleAmount = 0.0f;

			Enemy* m_enemy = nullptr;
		};
	}
}
