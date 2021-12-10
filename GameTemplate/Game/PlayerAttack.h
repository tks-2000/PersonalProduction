#pragma once
#include "PlayerBullet.h"

namespace mainGame {

	class GameCamera;

	namespace enemy {
		class Enemy;
	}

	namespace player {
		class Player;

		/// @brief �v���C���[�̍U���𐧌䂷��N���X
		class Attack
		{
		public:
			Attack();
			~Attack();

			/// @brief ������
			/// @param pl ������K�p����v���C���[�̃A�h���X
			void Init(Player* pl);

			/// @brief ���s
			void Execute();

			/// @brief �G�̏������
			/// @param enemy �G�N���X�̃A�h���X
			void AddEnemyData(enemy::Enemy* enemy) { m_enemys.push_back(enemy); }

			/// @brief �G�̏����폜
			/// @param enemy �G�N���X�̃A�h���X
			void DeleteEnemyData(enemy::Enemy* enemy);

			void DeleteBullet(Bullet* bullet);

			/// @brief �e�ۂ̏������
			/// @return �e�ۂ̔z��̃A�h���X
			std::vector<Bullet*>* GetBullets() { return &m_bullets; }


			const int GetRemainingBullets()const { return m_remainingBullets; }
			
			const bool IsAttackJudgement() const { return m_isAttackJudgement; }

			const bool IsFollCharge() const{ return m_isFollCharge; }

			const float GetAttackPossibleMatchRate() const{ return m_attackPossibleMatchRate; }

		private:
			/// @brief �ߐڍU�������s
			void MeleeAttack();
			/// @brief �`���[�W�ߐڍU�������s
			void ChargeMeleeAttack();
			/// @brief 
			void BulletFiring();

			void BulletExecution();

			

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �ߐڍU���{�^����������Ă��邩�H
			bool m_isMeleeAttackButtonHold = false;
			/// @brief �ߐڍU���̃`���[�W����
			float m_chargeMeleeAttackTimer = 0.0f;
			/// @brief �ߐڍU���̃`���[�W���������鎞��
			float m_chargeMeleeAttackTime = 0.0f;
			/// @brief �`���[�W�����t���O
			bool m_isFollCharge = false;
			/// @brief �U���̏Ռ���
			float m_attackPower = 0.0f;
			/// @brief �U���\�Ȕ͈�
			float m_attackRange = 0.0f;
			/// @brief �U���\�ȕ�����v��
			float m_attackPossibleMatchRate = 0.0f;
			/// @brief �U�����肪�o�Ă�H
			bool m_isAttackJudgement = false;
			/// @brief �U������̎��Ԃ��v��^�C�}�[
			float m_attackJudgementTimer = 0.0f;

			/// @brief �v���C���[�N���X
			Player* m_player = nullptr;
			/// @brief �G�N���X�̏����܂Ƃ߂��z��
			std::vector<enemy::Enemy*> m_enemys;
			/// @brief �c�e��
			int m_remainingBullets = 0;
			/// @brief �e�ۂ̍ő及����
			int m_maxBulletNum = 0;
			/// @brief �e�ۂ̍đ��U�܂ł̎��Ԃ��v��^�C�}�[
			float m_bulletReloadTimer = 0.0f;
			/// @brief �e�ۂ̍đ��U���������鎞��
			float m_bulletReloadTime = 0.0f;
			/// @brief �e�ۂ��܂Ƃ߂��z��
			std::vector<Bullet*> m_bullets;
			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
		};
	}
}
