#include "stdafx.h"
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief アイテムの出現する時間
		const float ITEM_SPAWN_TIME = 2.0f;
		/// @brief アイテムを入手できる距離
		const float ITEM_GET_DISTANCE = 100.0f;
		/// @brief 入手不可タイマーのループ時間
		const float CANTGET_TIMER_LOOP_TIME = 1.0f;
		/// @brief 入手不可の移動開始時間
		const float CANTGET_MOVE_START_TIME = 0.4f;
		/// @brief 入手不可の移動終了時間
		const float CANTGET_MOVE_END_TIME = CANTGET_TIMER_LOOP_TIME - CANTGET_MOVE_START_TIME;
		/// @brief 速度
		const float VEROCITY = 200.0f;
		/// @brief 移動を停止する距離
		const float MOVE_STOP_LENGTH = 0.01f;

		Item::Item()
		{

		}

		Item::~Item()
		{
			//プレイヤーに入手されていない場合…
			if (m_isPlayerGet == false) {
				//モデルを削除
				DeleteGO(m_itemModel);
			}
		}

		void Item::Init(ItemGenerator* itemGenerator, const Vector3& spawnPos)
		{
			//使用する情報を持って来る
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//メンバ変数を初期化
			m_itemGenerator = itemGenerator;
			m_isPlayerGet = false;
			m_isActivate = false;
			InitData();
			m_itemEffect.Init(this);
			m_itemSound.Init(this);
			m_spawnPos = spawnPos;
			m_position = spawnPos;

			//初期化完了
			m_isInitd = true;
		}

		void Item::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//出現していない場合…
			if (m_isSpawn == false) {
				//出現タイマーを加算
				m_spawnTimer += g_gameTime->GetFrameDeltaTime();
				//タイマーが出現時間を超えたら
				if (m_spawnTimer > ITEM_SPAWN_TIME) {
					//出現時の処理を実行
					Spawn();
					m_isSpawn = true;
				}
				//出現していないので処理を終わる
				return;
			}

			//プレイヤーに入手されていない場合…
			if (m_isPlayerGet == false) {

				//入手不可演出の移動処理を実行
				CantGetMove();
				
				//アイテムのモデルを更新
				m_itemModel->SetPosition(m_position);
				m_itemModel->Execution();

				//プレイヤーとの接触判定を行う
				PlayerCollision();
			}

			//効果発動中の場合…
			if (m_isActivate == true) {
				//発動時の処理を実行
				Efficacy();

				//発動時のタイマーを加算
				m_activateTimer += g_gameTime->GetFrameDeltaTime();

				//タイマーが終了時間に達したら…
				if (m_activateTimer >= m_endTime) {
					//自身を削除
					m_itemGenerator->DeleteItem(this);
					DeleteEfficacy();
					DeleteGO(this);
				}
			}

			//エフェクトとサウンドを実行
			m_itemEffect.Execution();
			m_itemSound.Execution();
		}

		void Item::InitData()
		{
			

			

		}

		void Item::Spawn()
		{
			
		}

		void Item::PlayerCollision()
		{
			//プレイヤーとの距離を測る
			Vector3 toPlayerPos = m_player->GetPlayerPosition() - m_position;

			//プレイヤーとの距離が入手距離内の場合…
			if (toPlayerPos.Length() < ITEM_GET_DISTANCE) {
				
				//プレイヤーのアイテムスロットに入れることが出来た場合…
				if (m_player->SetItemSlot(this) == true) {
					//プレイヤーに入手されたフラグを立てる
					m_isPlayerGet = true;
					DeleteGO(m_itemModel);
					m_isCantGet = false;
				}
				//プレイヤーのアイテムスロットに入れることが出来なかった場合…
				else {
					//入手不可フラグを立てる
					m_isCantGet = true;
				}

			}
			//プレイヤーとの距離が入手距離外の場合…
			else {
				//入手不可フラグを降ろす
				m_isCantGet = false;
			}

		}

		void Item::CantGetMove()
		{
			//入手不可フラグが立っている場合…
			if (m_isCantGet == true) {
				
				//入手不可タイマーを加算
				m_cantGetTimer += g_gameTime->GetFrameDeltaTime();
				
				//タイマーが移動開始時間を超えていて、移動終了時間未満の場合…
				if (m_cantGetTimer > CANTGET_MOVE_START_TIME && m_cantGetTimer < CANTGET_MOVE_END_TIME) {
					//タイマーがループ時間の半分未満の場合…
					if (m_cantGetTimer < CANTGET_TIMER_LOOP_TIME / 2.0f) {
						//y座標を加算
						m_position.y += VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
					//タイマーがループ時間の半分を超えている場合…
					else {
						//y座標を減算
						m_position.y -= VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
				}
				//タイマーが移動開始時間より前、移動終了時間を超えている場合…
				else {
					//現在の座標から出現時の座標へ伸びるベクトルを入手
					Vector3 moveSpeed = m_spawnPos - m_position;

					//出現時の座標との距離が移動停止距離より大きい場合…
					if (moveSpeed.Length() > MOVE_STOP_LENGTH) {
						//出現時の位置に向かって移動する
						moveSpeed.Normalize();
						m_position += moveSpeed * VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
				}

				//タイマーがループ時間を超えた場合…
				if (m_cantGetTimer > CANTGET_TIMER_LOOP_TIME) {
					//タイマーを0に戻す
					m_cantGetTimer = 0.0f;
				}
			}
			//入手不可フラグが立っていない場合…
			else {
				//現在の座標から出現時の座標へ伸びるベクトルを入手
				Vector3 moveSpeed = m_spawnPos - m_position;

				//出現時の座標との距離が移動停止距離より大きい場合…
				if (moveSpeed.Length() > MOVE_STOP_LENGTH) {
					//出現時の位置に向かって移動する
					moveSpeed.Normalize();
					m_position += moveSpeed * VEROCITY * g_gameTime->GetFrameDeltaTime();
				}

				//入手不可タイマーを0にする
				m_cantGetTimer = 0.0f;
			}
		}

		void Item::Activation()
		{
			m_isActivate = true;
		}

		void Item::Efficacy()
		{
			
		}

		void Item::DeleteEfficacy()
		{
			
		}
		
	}
}