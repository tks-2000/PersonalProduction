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
			
		private:
			/// @brief �ߐڍU�������s
			void MeleeAttack();
			/// @brief 
			void BulletFiring();

			void BulletExecution();

			

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �U���̏Ռ���
			float m_attackPower = 0.0f;
			/// @brief �U���\�Ȕ͈�
			float m_attackRange = 0.0f;
			/// @brief �v���C���[�N���X
			Player* m_player = nullptr;
			/// @brief �G�N���X�̏����܂Ƃ߂��z��
			std::vector<enemy::Enemy*> m_enemys;
			/// @brief �o�����Ă���e�ۂ̐�
			int m_bulletNum = 0;
			/// @brief �e�ۂ��܂Ƃ߂��z��
			std::vector<Bullet*> m_bullets;
			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
		};
	}
}
