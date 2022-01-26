#include "stdafx.h"
#include "Bomb.h"

namespace mainGame {
	namespace item {

		/// @brief 敵と接触する距離
		const float ENEMY_COLLISION_DISTANCE = 100.0f;
		/// @brief 弾丸と接触する距離
		const float BULLET_COLLISION_DISTANCE = 200.0f;
		/// @brief 爆発半径
		const float EXPLOSION_RADIUS = 500.0f;
		/// @brief 爆発の衝撃力
		const float EXPLOSION_IMPACT = 5000.0f;
		/// @brief 爆発のダメージ量
		const int EXPLOSION_DAMAGE = 0;
		/// @brief 自然消滅する時間
		const float DISAPPEARANCE_TIME = 10.0f;
		/// @brief 爆発してから消滅する時間
		const float EXPLOSION_DISAPPEARANCE_TIME = 3.0f;
		/// @brief プレイヤーの近接攻撃が当たる範囲
		const float PLAYER_MELEE_ATTACK_COLLISION_DISTANCE = 200.0f;
		/// @brief プレイヤーの近接攻撃が当たる角度の一致率
		const float PLAYER_MELEE_ATTACK_COLLISION_DOT_RATE = 0.0f;
		/// @brief 
		const float NORMAL_MOVE_VEROCITY = 1000.0f;
		/// @brief 
		const float FAST_MOVE_SPEED = 2000.0f;

		const float SET_DISTANCE = 150.0f;

		const float SET_HEIGHT = 50.0f;

		const float EXPLOSION_TIME = 5.0f;

		const char16_t* EXPLOSION_EFFECT_FILEPATH = u"Assets/effect/CosmicMist.efk";

		const Vector3 EXPLOSION_EFFECT_SCALE = { 15.0f,15.0f,15.0f };

		const wchar_t* EXPLOSION_SE_FILEPATH = L"Assets/sound/se/explosion.wav";

		const float EXPLOSION_SE_VOLUME = 0.1f;

		Bomb::~Bomb()
		{
			if (m_modelFlag == true) {
				DeleteGO(m_itemModel);
			}

			DeleteGO(m_explosion);
		}

		void Bomb::InitData()
		{
			m_itemType = enItemBomb;

			

			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_explosionSoundID = m_soundPlayer->SetSE(EXPLOSION_SE_FILEPATH);

			m_enemys = m_enemyGenerator->GetEnemys();

			m_bullets = m_player->GetBulletData();

			m_explosion = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_explosion->Init(EXPLOSION_EFFECT_FILEPATH);
			m_explosion->SetScale(EXPLOSION_EFFECT_SCALE);

			m_endTime = DISAPPEARANCE_TIME;
		}

		void Bomb::Spawn()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/item/item_attackup.tkm");
		}

		void Bomb::Activation()
		{
			m_isActivate = true;

			Vector3 setPos = m_player->GetPlayerDirection() * SET_DISTANCE;

			setPos = m_player->GetPlayerPosition() + setPos;

			setPos.y += SET_HEIGHT;

			m_position = setPos;

			CreateModel();
		}

		void Bomb::Efficacy()
		{
			if (m_modelFlag == true) {

				m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
				
				m_itemModel->SetPosition(m_position);
				m_itemModel->Execution();

				PlayerMeleeAttackCollision();

				EnemyCollision();

				BulletCollision();

				if (m_activateTimer > EXPLOSION_TIME) {
					Explosion();
				}
			}

			m_explosion->SetPosition(m_position);
			m_explosion->Execution();
		}

		void Bomb::DeleteEfficacy()
		{
			
		}

		void Bomb::CreateModel()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_modelFlag = true;
		}

		void Bomb::EnemyCollision()
		{
			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//敵のデータを取り出す
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//敵との距離を測る
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//敵との距離が接触距離以下なら…
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					//爆発する
					Explosion();
				}
			}
		}

		void Bomb::BulletCollision()
		{
			//弾丸の数だけ実行する
			for (int bulletNum = 0; bulletNum < m_bullets->size(); bulletNum++) {
				//弾丸の情報を取り出す
				player::Bullet* bulletData = *(m_bullets->begin() + bulletNum);

				//弾丸へ伸びるベクトルを求める
				Vector3 toBulletVec = bulletData->GetPosition() - m_position;

				//弾丸との距離が接触距離以下だったら…
				if (toBulletVec.Length() < BULLET_COLLISION_DISTANCE) {

					//爆発する
					Explosion();
				}

			}
		}

		void Bomb::PlayerMeleeAttackCollision()
		{
			//プレイヤーが攻撃判定を出していなかったら…
			if (m_player->IsAttackJudgement() == false) {
				//処理を終わる
				return;
			}

			//プレイヤーの位置と自身の位置からプレイヤーから自分に伸びるベクトルを求める
			Vector3 playerToVec = m_position - m_player->GetPlayerPosition();
			//y方向の成分を消す
			playerToVec.y = 0.0f;

			
			//プレイヤーから自身までの距離が接触判定内だったら…
			if (playerToVec.Length() < PLAYER_MELEE_ATTACK_COLLISION_DISTANCE) {

				//正規化して大きさ1のベクトルにする
				playerToVec.Normalize();
				//プレイヤーから自分へのベクトルとプレイヤーの向きの内積を求める
				float matchRate = Dot(m_player->GetPlayerDirection(), playerToVec);

				//プレイヤーがフルチャージ状態だったら…
				if (m_player->IsFollCharge() == true) {
					//プレイヤーから自分へのベクトルで速く移動する
					m_moveSpeed = playerToVec * FAST_MOVE_SPEED;
				}
				//プレイヤーがフルチャージ状態でない場合
				else {
					//角度一致率がプレイヤーの攻撃可能な角度一致りつより大きい場合…
					if (matchRate > m_player->GetAttackPossibleMatchRate()) {
						//プレイヤーから自分へのベクトルで移動する
						m_moveSpeed = playerToVec * NORMAL_MOVE_VEROCITY;
					}
				}
			}
		}

		void Bomb::Explosion()
		{
			//アイテムの消滅までの時間を元に戻す
			m_activateTimer = 0.0f;

			//消滅までの時間を新しく設定
			m_endTime = EXPLOSION_DISAPPEARANCE_TIME;

			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//敵のデータを取り出す
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//敵との距離を測る
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//敵との距離が爆発半径以下なら…
				if (toEnemyVec.Length() < EXPLOSION_RADIUS) {

					//敵へと伸びるベクトルを正規化
					toEnemyVec.Normalize();

					//敵に衝撃を加える
					enemyData->SetMoveSpeed(toEnemyVec * EXPLOSION_IMPACT);

					//敵をダメージ状態に変更
					//enemyData->SetState(enemy::enEnemyDamage);

					//敵に爆発のダメージを与える
					enemyData->ReceiveDamage(EXPLOSION_DAMAGE);
				}
			}

			m_explosion->Play(false);
			m_soundPlayer->SetSEVolume(m_explosionSoundID, EXPLOSION_SE_VOLUME);
			m_soundPlayer->PlaySE(m_explosionSoundID);


			//モデルを削除
			DeleteGO(m_itemModel);

			m_modelFlag = false;
		}
	}
}