#pragma once
#include "Item.h"

class Effect;

namespace mainGame {

	namespace enemy {
		class Enemy;
		class Generator;
	}

	namespace item {

		/// @brief ���e�N���X
		class Bomb : public Item
		{
		public:
			~Bomb();

			/// @brief ���ʔ������̏���
			void Activation();

		private:
			/// @brief �ʂ̏��̏�����
			void InitData();

			/// @brief ���ʔ������̏���
			void Efficacy();

			/// @brief ���f�����쐬
			void CreateModel();

			/// @brief �G�Ƃ̐ڐG�𔻒�
			void EnemyCollision();

			/// @brief �e�ۂƂ̐ڐG�𔻒�
			void BulletCollision();

			/// @brief �v���C���[�̋ߐڍU���Ƃ̐ڐG�𔻒�
			void PlayerMeleeAttackCollision();

			/// @brief �������̏���
			void Explosion();

			bool m_modelFlag = false;

			Vector3 m_moveSpeed = g_vec3Zero;

			/// @brief �G�̔z��̃|�C���^
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief �G������
			enemy::Generator* m_enemyGenerator = nullptr;

			/// @brief �e�ۂ̔z��̃|�C���^
			std::vector<player::Bullet*>* m_bullets = nullptr;

			Effect m_explosion;

			int m_explosionSoundID = 0;

			sound::SoundPlayer* m_soundPlayer = nullptr;
		};

	}
}