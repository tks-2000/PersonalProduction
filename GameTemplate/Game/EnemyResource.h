#pragma once
namespace mainGame{
	namespace enemy {
		/// @brief “G‚Ìí—Ş‚ğ•\‚·—ñ‹“Œ^
		enum EnEnemyType {
			/// @brief ’Êí‚Ì“G
			enEnemyTypeNormal,
			/// @brief —Í‚Ì‹­‚¢“G
			enEnemyTypePowerful,
			/// @brief ‘f‘‚¢“G
			enEnemyTypeFast,
			/// @brief “G‚Ìí—Ş‚Ì‡Œv”
			enEnemyTypeNum
		};

		/// @brief ‰Šú‰»‚³‚ê‚Ä‚¢‚È‚¢ˆµ‚¢‚Ì”Ô†
		static const int ENEMY_UNINITD_NUMBER = 100;

		/// @brief “G‚Ì‰Šú‰»î•ñ‚ğ‚Ü‚Æ‚ß‚½\‘¢‘Ì
		struct EnemyInitData {
			/// @brief “G‚Ì”Ô†
			int enemyNum = ENEMY_UNINITD_NUMBER;
			/// @brief “G‚Ìí—Ş
			EnEnemyType enemyType = enEnemyTypeNum;
			/// @brief “G‚Ì‰ŠúÀ•W
			Vector3 enemyStartPos = g_vec3Zero;
		};

		static const int MAX_ENEMY_NUM = 20;
		static const int SPAWN_POS_NUM = 8;
	}
}