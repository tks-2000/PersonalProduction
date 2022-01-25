#pragma once
#include "Item.h"

class Effect;

namespace mainGame {

	namespace enemy {
		class Enemy;
		class Generator;
	}

	namespace item {

		/// @brief 爆弾クラス
		class Bomb : public Item
		{
		public:
			~Bomb();

			/// @brief 効果発動時の処理
			void Activation();

		private:
			/// @brief 個別の情報の初期化
			void InitData();

			/// @brief 効果発動中の処理
			void Efficacy();

			/// @brief モデルを作成
			void CreateModel();

			/// @brief 敵との接触を判定
			void EnemyCollision();

			/// @brief 弾丸との接触を判定
			void BulletCollision();

			/// @brief プレイヤーの近接攻撃との接触を判定
			void PlayerMeleeAttackCollision();

			/// @brief 爆発時の処理
			void Explosion();

			bool m_modelFlag = false;

			Vector3 m_moveSpeed = g_vec3Zero;

			/// @brief 敵の配列のポインタ
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief 敵生成器
			enemy::Generator* m_enemyGenerator = nullptr;

			/// @brief 弾丸の配列のポインタ
			std::vector<player::Bullet*>* m_bullets = nullptr;

			Effect m_explosion;

			int m_explosionSoundID = 0;

			sound::SoundPlayer* m_soundPlayer = nullptr;
		};

	}
}