#pragma once

namespace mainGame {
	namespace enemy {
		

		/// @brief �G�l�~�[�̃G�t�F�N�g������
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();

			/// @brief ������
			/// @param enemy �G�l�~�[�N���X�̃A�h���X
			void Init(Enemy* enemy);

			/// @brief ���s
			void Execution();
		private:

			/// @brief �o���G�t�F�N�g�����̎��s
			void SpawnEffectExecution();

			/// @brief �_���[�W�G�t�F�N�g�����̎��s
			void DamageEffectExecution();

			/// @brief �U���G�t�F�N�g�����̎��s
			void AttackEffectExecution();

			/// @brief ���S�G�t�F�N�g�����̎��s
			void DeathEffectExecution();
			
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �o���G�t�F�N�g
			render::effect::EffectRender* m_spawnEffect = nullptr;
			/// @brief �_���[�W�G�t�F�N�g
			render::effect::EffectRender* m_damageEffect = nullptr;
			/// @brief �X�^���G�t�F�N�g
			render::effect::EffectRender* m_stanEffect = nullptr;
			/// @brief �U���G�t�F�N�g
			render::effect::EffectRender* m_attackEffect = nullptr;
			/// @brief ���S�G�t�F�N�g
			render::effect::EffectRender* m_deathEffect = nullptr;
			/// @brief �G�̃f�[�^
			Enemy* m_enemy = nullptr;
		};
	}
}
