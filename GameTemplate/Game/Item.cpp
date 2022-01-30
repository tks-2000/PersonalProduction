#include "stdafx.h"
#include "Item.h"

namespace mainGame {
	namespace item {

		const float ITEM_SPAWN_TIME = 2.0f;

		const float ITEM_GET_DISTANCE = 100.0f;

		const float CANTGET_TIMER_LOOP_TIME = 1.0f;

		const float CANTGET_MOVE_START_TIME = 0.4f;

		const float CANTGET_MOVE_END_TIME = CANTGET_TIMER_LOOP_TIME - CANTGET_MOVE_START_TIME;

		const float VEROCITY = 200.0f;

		const float MOVE_STOP_LENGTH = 0.01f;

		Item::Item()
		{

		}

		Item::~Item()
		{
			if (m_isPlayerGet == false) {
				DeleteGO(m_itemModel);
			}
		}

		void Item::Init(ItemGenerator* itemGenerator, const Vector3& spawnPos)
		{
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_itemGenerator = itemGenerator;

			m_isPlayerGet = false;

			m_isActivate = false;

			InitData();

			m_itemEffect.Init(this);

			m_itemSound.Init(this);

			m_spawnPos = spawnPos;

			m_position = spawnPos;

			m_isInitd = true;

		}

		void Item::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (m_isSpawn == false) {
				m_spawnTimer += g_gameTime->GetFrameDeltaTime();
				if (m_spawnTimer > ITEM_SPAWN_TIME) {
					Spawn();
					m_isSpawn = true;
				}
				return;
			}

			if (m_isPlayerGet == false) {

				CantGetMove();
				
				m_itemModel->SetPosition(m_position);

				m_itemModel->Execution();

				PlayerCollision();
			}

			if (m_isActivate == true) {
				Efficacy();
				m_activateTimer += g_gameTime->GetFrameDeltaTime();

				if (m_activateTimer >= m_endTime) {
					m_itemGenerator->DeleteItem(this);
					DeleteEfficacy();
					DeleteGO(this);
				}
			}

			m_itemEffect.Execution();
			m_itemSound.Execution();
		}

		void Item::InitData()
		{
			

			m_position = { 200.0f,50.0f,200.0f };

			m_endTime = 10.0f;

		}

		void Item::Spawn()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");
		}

		void Item::PlayerCollision()
		{
			//プレイヤーとの距離を測る
			Vector3 toPlayerPos = m_player->GetPlayerPosition() - m_position;

			//距離が一定以下でモデルを消す
			if (toPlayerPos.Length() < ITEM_GET_DISTANCE) {
				

				if (m_player->SetItemSlot(this) == true) {
					m_isPlayerGet = true;
					DeleteGO(m_itemModel);
					m_isCantGet = false;
				}
				else {
					m_isCantGet = true;
				}

			}
			else {
				m_isCantGet = false;
			}

		}

		void Item::CantGetMove()
		{
			if (m_isCantGet == true) {
				
				m_cantGetTimer += g_gameTime->GetFrameDeltaTime();
				
				if (m_cantGetTimer > CANTGET_MOVE_START_TIME && m_cantGetTimer < CANTGET_MOVE_END_TIME) {
					if (m_cantGetTimer < CANTGET_TIMER_LOOP_TIME / 2.0f) {
						m_position.y += VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
					else {
						m_position.y -= VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
				}
				else {
					Vector3 moveSpeed = m_spawnPos - m_position;

					if (moveSpeed.Length() > MOVE_STOP_LENGTH) {
						moveSpeed.Normalize();
						m_position += moveSpeed * VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
				}

				if (m_cantGetTimer > CANTGET_TIMER_LOOP_TIME) {
					m_cantGetTimer = 0.0f;
				}
			}
			else {
				Vector3 moveSpeed = m_spawnPos - m_position;

				if (moveSpeed.Length() > MOVE_STOP_LENGTH) {
					moveSpeed.Normalize();
					m_position += moveSpeed * VEROCITY * g_gameTime->GetFrameDeltaTime();
				}

				m_cantGetTimer = 0.0f;
			}
		}

		void Item::Activation()
		{
			m_isActivate = true;
		}

		void Item::Efficacy()
		{
			m_player->SetMoveSpeed({ 100.0f,0.0f,0.0f });
		}

		void Item::DeleteEfficacy()
		{
			
		}
		
	}
}