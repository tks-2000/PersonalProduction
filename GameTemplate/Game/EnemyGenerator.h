#pragma once
#include"EnemyResource.h"

namespace mainGame {
	namespace enemy {

		

		/// @brief 敵を呼び出すクラス
		class Generator : public IGameObject
		{
		public:
			Generator();
			~Generator();

			/// @brief 初期化
			/// @param pos 敵生成器の中心座標
			void Init(const Vector3& pos);

			/// @brief 実行
			void Execute();

			/// @brief 出現している敵を削除
			/// @param enemy 削除する敵のアドレス
			void DeleteEnemy(Enemy* enemy);

			void DeleteAllEnemy();
		private:

			/// @brief 敵を出現させる
			void CreateEnemy(const EnEnemyType& type,const Vector3& pos);

			/// @brief 初期化フラグ
			bool m_isInitd = false;

			/// @brief 敵の出現フラグ
			bool m_isSpawn[MAX_ENEMY_NUM] = { false };

			/// @brief 出現している敵の合計数
			int m_enemySum = 0;
			/// @brief 敵生成器の座標
			Vector3 m_position = g_vec3Zero;

			/// @brief 出現する敵の配列
			std::vector<Enemy*> m_enemys;

			/// @brief 生成器から出現する座標
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
