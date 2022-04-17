#include "stdafx.h"
#include "NutritionDrink.h"

namespace mainGame {

	namespace item {
		/// @brief アイテムモデルのファイルパス
		const char* DRINK_MODEL_FILEPATH = "Assets/modelData/item/item_speedup.tkm";
		/// @brief 効果終了までの時間
		const float DISAPPEARANCE_TIME = 10.0f;
		/// @brief エネミーと接触する距離
		const float ENEMY_COLLISION_DISTANCE = 150.0f;
		/// @brief 体当たりの衝撃量
		const float BODY_BLOW_IMPACT = 5000.0f;
		/// @brief 体当たりのダメージ
		const int BODY_BLOW_DAMAGE = 100;
		/// @brief 加算する速度
		const float ADD_MOVE_VEROCITY = 10.0f;
		/// @brief パワーアップエフェクトのファイルパス
		const char16_t* POWERUP_EFFECT_FILEPATH = u"Assets/effect/itembuff_attackup.efk";
		/// @brief パワーアップエフェクトの拡大率
		const Vector3 POWERUP_EFFECT_SCALE = { 10.0f,10.0f,10.0f };

		NutritionDrink::~NutritionDrink()
		{
			//エフェクトを停止し削除
			m_powerUpEffect->Stop(true);
			DeleteGO(m_powerUpEffect);
		}

		void NutritionDrink::Activation()
		{
			//エフェクトを再生
			m_powerUpEffect->Play(true);
			//効果発動フラグを立てる
			m_isActivate = true;
		}

		void NutritionDrink::InitData()
		{
			//変数を初期化
			m_itemType = enItemNutritionDrink;
			m_endTime = DISAPPEARANCE_TIME;

			//使用する情報を初期化
			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);
			m_enemys = m_enemyGenerator->GetEnemys();

			//エフェクトを作成
			m_powerUpEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_powerUpEffect->Init(POWERUP_EFFECT_FILEPATH);
			m_powerUpEffect->SetScale(POWERUP_EFFECT_SCALE);
		}

		void NutritionDrink::Spawn()
		{
			//
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->InitDeferrd(DRINK_MODEL_FILEPATH);
		}

		void NutritionDrink::Efficacy()
		{
			//座標をプレイヤーの座標に設定する
			m_position = m_player->GetPlayerPosition();

			//エフェクトの処理を実行
			m_powerUpEffect->SetPosition(m_position);
			m_powerUpEffect->Execution();

			//プレイヤーの速度を加算
			m_player->SetAddVerocity(ADD_MOVE_VEROCITY);

			//エネミーと当たり判定を取る
			EnemyCollision();
		}

		void NutritionDrink::EnemyCollision()
		{
			//エネミーの数だけ実行
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//エネミーのデータを取り出す
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//エネミーとの距離を測る
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//エネミーとの距離が接触距離以下なら…
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && enemyData->GetState() != enemy::enEnemyDown) {

					//エネミーへと伸びるベクトルを正規化
					toEnemyVec.Normalize();

					//エネミーに衝撃を加える
					enemyData->SetMoveSpeed(toEnemyVec * BODY_BLOW_IMPACT);

					//エネミーに接触のダメージを与える
					enemyData->ReceiveDamage(BODY_BLOW_DAMAGE);
				}
			}
		}

		void NutritionDrink::DeleteEfficacy()
		{
			//プレイヤーに加算する速度を0にする
			m_player->SetAddVerocity(0.0f);
		}
	}
}