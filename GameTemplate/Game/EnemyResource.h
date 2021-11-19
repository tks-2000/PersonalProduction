#pragma once
namespace mainGame{
	namespace enemy {
		/// @brief �G�̎�ނ�\���񋓌^
		enum EnEnemyType {
			/// @brief �ʏ�̓G
			enEnemyTypeNormal,
			/// @brief �͂̋����G
			enEnemyTypePowerful,
			/// @brief �f�����G
			enEnemyTypeFast,
			/// @brief �G�̎�ނ̍��v��
			enEnemyTypeNum
		};

		/// @brief ����������Ă��Ȃ������̔ԍ�
		static const int ENEMY_UNINITD_NUMBER = 100;

		/// @brief �G�̏����������܂Ƃ߂��\����
		struct EnemyInitData {
			/// @brief �G�̔ԍ�
			int enemyNum = ENEMY_UNINITD_NUMBER;
			/// @brief �G�̎��
			EnEnemyType enemyType = enEnemyTypeNum;
			/// @brief �G�̏������W
			Vector3 enemyStartPos = g_vec3Zero;
		};

		static const int MAX_ENEMY_NUM = 20;
		static const int SPAWN_POS_NUM = 8;
	}
}