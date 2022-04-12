#pragma once
#include "Item.h"

class Effect;

namespace mainGame {

	namespace enemy {
		class Enemy;
		class Generator;
	}

	namespace item {

		/// @brief �G�l�~�[�𐁂���΂����e
		class Bomb : public Item
		{
		public:
			~Bomb();

			/// @brief ���ʔ������̏���
			void Activation() override;

		private:
			/// @brief �ʂ̏��̏�����
			void InitData() override;

			/// @brief �o�����̏���
			void Spawn() override;

			/// @brief ���ʔ������̏���
			void Efficacy() override;

			void DeleteEfficacy() override;

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

			/// @brief ���f���o�����̃t���O
			bool m_modelFlag = false;
			/// @brief �ړ����x
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief �G�̔z��̃|�C���^
			std::vector<enemy::Enemy*>* m_enemys = nullptr;
			/// @brief �G������
			enemy::Generator* m_enemyGenerator = nullptr;
			/// @brief �e�ۂ̔z��̃|�C���^
			std::vector<player::Bullet*>* m_bullets = nullptr;
			/// @brief �G�t�F�N�g
			render::effect::EffectRender* m_explosion = nullptr;
			/// @brief �����T�E���h��ID
			int m_explosionSoundID = 0;
			/// @brief �T�E���h�v���C���[
			sound::SoundPlayer* m_soundPlayer = nullptr;
		};

	}
}