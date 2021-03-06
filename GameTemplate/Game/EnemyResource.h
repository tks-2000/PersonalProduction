#pragma once
namespace mainGame{
	namespace enemy {
		/// @brief 敵の種類を表す列挙型
		enum EnEnemyType {
			/// @brief 通常の敵
			enEnemyTypeNormal,
			/// @brief 力の強い敵
			enEnemyTypePowerful,
			/// @brief 素早い敵
			enEnemyTypeFast,
			/// @brief 敵の種類の合計数
			enEnemyTypeNum
		};

		/// @brief 初期化されていない扱いの番号
		static const int ENEMY_UNINITD_NUMBER = 100;

		/// @brief 敵の初期化情報をまとめた構造体
		struct EnemyInitData {
			/// @brief 敵の番号
			int enemyNum = ENEMY_UNINITD_NUMBER;
			/// @brief 敵の種類
			EnEnemyType enemyType = enEnemyTypeNum;
			/// @brief 敵の初期座標
			Vector3 enemyStartPos = g_vec3Zero;
		};

		/// @brief エネミーの最大出現数
		static const int MAX_ENEMY_NUM = 20;
		/// @brief 出現位置の数
		static const int SPAWN_POS_NUM = 16;
	}
}