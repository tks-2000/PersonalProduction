#include "stdafx.h"
#include "Item.h"

namespace mainGame {
	namespace item {

		const float ITEM_GET_DISTANCE = 100.0f;

		Item::Item()
		{

		}

		Item::~Item()
		{
			if (m_isPlayerGet == false) {
				DeleteGO(m_itemModel);
			}
		}

		void Item::Init(ItemGenerator* itemGenerator)
		{
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_itemGenerator = itemGenerator;

			m_isPlayerGet = false;

			m_isActivate = false;

			InitData();

			m_isInitd = true;

		}

		void Item::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (m_isPlayerGet == false) {
				
				m_itemModel->SetPosition(m_position);

				m_itemModel->Execution();

				PlayerCollision();
			}

			if (m_isActivate == true) {
				Efficacy();
				m_activateTimer += g_gameTime->GetFrameDeltaTime();

				if (m_activateTimer >= m_endTime) {
					m_itemGenerator->DeleteItem(this);
					DeleteGO(this);
				}
			}
		}

		void Item::InitData()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_position = { 200.0f,50.0f,200.0f };

			m_endTime = 10.0f;

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
				}

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
		
	}
}