#pragma once

namespace mainGame {
	namespace enemy {
		/// @brief �G�t�F�N�g�̏����܂Ƃ߂��\����
		struct EffectData
		{
			/// @brief �G�t�F�N�g
			Effect effect;
			/// @brief ���W
			Vector3 pos = g_vec3Zero;
			/// @brief ��]
			Quaternion qRot = Quaternion::Identity;
			/// @brief �g�嗦
			Vector3 scale = g_vec3One;
			/// @brief �C�ӂő��삷��Đ��t���O
			bool playFlag = false;

		};

		/// @brief �G�t�F�N�g������
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();

			/// @brief ������
			/// @param enemy �G�N���X�̃A�h���X
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

			/// @brief �G�t�F�N�g�����X�V
			/// @param effectData �X�V�G�t�F�N�g���
			void UpdateEffect(EffectData& effectData);
			
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �o���G�t�F�N�g
			EffectData m_spawnEffect;
			/// @brief �_���[�W�G�t�F�N�g
			EffectData m_damageEffect;
			/// @brief �X�^���G�t�F�N�g
			EffectData m_stanEffect;
			/// @brief �U���G�t�F�N�g
			EffectData m_attackEffect;
			/// @brief ���S�G�t�F�N�g
			EffectData m_deathEffect;
			/// @brief �G�̃f�[�^
			Enemy* m_enemy = nullptr;
		};
	}
}
