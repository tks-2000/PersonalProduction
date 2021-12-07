#pragma once
#include "Item.h"

namespace mainGame {

	namespace enemy {
		class Enemy;
		class Generator;
	}

	namespace item {
		class Bomb : public Item
		{
		public:
			~Bomb();

			void Activation();

		private:
			void InitData();

			void Efficacy();

			void CreateModel();

			void EnemyCollision();

			void BulletCollision();

			void Explosion();

			bool m_modelFlag = false;

			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			enemy::Generator* m_enemyGenerator = nullptr;

			std::vector<player::Bullet*>* m_bullets = nullptr;
		};

	}
}