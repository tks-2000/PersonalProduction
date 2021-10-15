#pragma once
#include"EnemyResource.h"

namespace mainGame {
	namespace enemy {

		const int SPAWN_POS_NUM = 4;

		/// @brief �G���Ăяo���N���X
		class Generator : public IGameObject
		{
		public:
			Generator();
			~Generator();
			void Init(const Vector3& pos);
			void Execute();

			/// @brief �G���폜
			/// @param enemy �폜����G�̃A�h���X
			void DeleteEnemy(Enemy* enemy,const int num);
		private:
			void CreateEnemy();

			/// @brief �������t���O
			bool m_isInitd = false;

			/// @brief �G�̏o���t���O
			bool m_isSpawn[MAX_ENEMY_NUM] = { false };

			/// @brief �o�����Ă���G�̍��v��
			int m_enemySum = 0;
			/// @brief �G������̍��W
			Vector3 m_position = g_vec3Zero;

			std::vector<Enemy*> m_enemys;

			/// @brief �����킩��o��������W�܂ł̋���
			Vector3 m_toGeneratorPos[SPAWN_POS_NUM] = {
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero
			};
		};
	}
}
