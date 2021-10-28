#pragma once
#include "PlayerBullet.h"

namespace mainGame {

	class GameCamera;

	namespace enemy {
		class Enemy;
	}

	namespace player {
		class Player;

		/// @brief プレイヤーの攻撃を制御するクラス
		class Attack
		{
		public:
			Attack();
			~Attack();

			/// @brief 初期化
			/// @param pl 処理を適用するプレイヤーのアドレス
			void Init(Player* pl);

			/// @brief 実行
			void Execute();

			/// @brief 敵の情報を入手
			/// @param enemy 敵クラスのアドレス
			void AddEnemyData(enemy::Enemy* enemy) { m_enemys.push_back(enemy); }

			/// @brief 敵の情報を削除
			/// @param enemy 敵クラスのアドレス
			void DeleteEnemyData(enemy::Enemy* enemy);

			void DeleteBullet(Bullet* bullet);
			
		private:
			/// @brief 近接攻撃を実行
			void MeleeAttack();
			/// @brief 
			void BulletFiring();

			void BulletExecution();

			

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 攻撃の衝撃力
			float m_attackPower = 0.0f;
			/// @brief 攻撃可能な範囲
			float m_attackRange = 0.0f;
			/// @brief プレイヤークラス
			Player* m_player = nullptr;
			/// @brief 敵クラスの情報をまとめた配列
			std::vector<enemy::Enemy*> m_enemys;
			/// @brief 出現している弾丸の数
			int m_bulletNum = 0;
			/// @brief 弾丸をまとめた配列
			std::vector<Bullet*> m_bullets;
			/// @brief ゲームカメラ
			GameCamera* m_gameCamera = nullptr;
		};
	}
}
