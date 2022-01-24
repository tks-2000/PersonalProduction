#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace enemy {

		class Enemy;

		/// @brief �v���C���[�ւ̍U���𐧌䂷��N���X
		class AttackThePlayer
		{
		public:
			AttackThePlayer();
			~AttackThePlayer();
			/// @brief ������
			/// @param enemy �G�l�~�[�̃A�h���X
			void Init(Enemy* enemy);
			/// @brief ���s
			void Execution();
			/// @brief �U���ڕW��ݒ�
			/// @param target �U���ڕW�̍��W
			void SetAttackTarget(const Vector3& target) { m_attackTarget = target; }
			/// @brief �U�����s�������H
			/// @return true�ōs���� false�ōs���Ă��Ȃ�
			const bool IsAttack() { return m_isAttack; }

			/// @brief �U���������������H
			/// @return true�œ������� false�œ������Ă��Ȃ�
			const bool IsHit() { return m_isHit; }

		private:
			/// @brief �v���C���[�Ƀ_���[�W��^����
			void DamageThePlayer();
			/// @brief �������t���O
			bool m_isInitd = false;

			Vector3 m_attackTarget = g_vec3Zero;

			float m_attackTimer = 0.0f;

			bool m_isAttack = false;

			bool m_isHit = false;

			Enemy* m_enemy = nullptr;

			player::Player* m_player = nullptr;

		};
	}
}
