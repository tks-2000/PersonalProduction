#pragma once
#include"EnemyResource.h"

namespace mainGame {
	namespace enemy {

		const int SPAWN_POS_NUM = 4;

		/// @brief 敵を呼び出すクラス
		class Generator : public IGameObject
		{
		public:
			Generator();
			~Generator();
			void Init(const Vector3& pos);
			void Execute();

			/// @brief 敵を削除
			/// @param enemy 削除する敵のアドレス
			void DeleteEnemy(Enemy* enemy,const int num);
		private:
			void CreateEnemy();

			/// @brief 初期化フラグ
			bool m_isInitd = false;

			/// @brief 敵の出現フラグ
			bool m_isSpawn[MAX_ENEMY_NUM] = { false };

			/// @brief 出現している敵の合計数
			int m_enemySum = 0;
			/// @brief 敵生成器の座標
			Vector3 m_position = g_vec3Zero;

			std::vector<Enemy*> m_enemys;

			/// @brief 生成器から出現する座標までの距離
			Vector3 m_toGeneratorPos[SPAWN_POS_NUM] = {
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero
			};
		};
	}
}
