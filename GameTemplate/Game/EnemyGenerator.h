#pragma once
#include"EnemyResource.h"

namespace mainGame {
	namespace enemy {

		

		/// @brief �G���Ăяo���N���X
		class Generator : public IGameObject
		{
		public:
			Generator();
			~Generator();

			/// @brief ������
			/// @param pos �G������̒��S���W
			void Init(const Vector3& pos);

			/// @brief ���s
			void Execute();

			/// @brief �o�����Ă���G���폜
			/// @param enemy �폜����G�̃A�h���X
			void DeleteEnemy(Enemy* enemy);

			void DeleteAllEnemy();
		private:

			/// @brief �G���o��������
			void CreateEnemy(const EnEnemyType& type,const Vector3& pos);

			/// @brief �������t���O
			bool m_isInitd = false;

			/// @brief �G�̏o���t���O
			bool m_isSpawn[MAX_ENEMY_NUM] = { false };

			/// @brief �o�����Ă���G�̍��v��
			int m_enemySum = 0;
			/// @brief �G������̍��W
			Vector3 m_position = g_vec3Zero;

			/// @brief �o������G�̔z��
			std::vector<Enemy*> m_enemys;

			/// @brief �����킩��o��������W
			Vector3 m_spawnPos[SPAWN_POS_NUM] = {
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero
			};

			float m_spawnTimer = 0.0f;
		};
	}
}
