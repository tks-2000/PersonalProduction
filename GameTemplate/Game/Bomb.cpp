#include "stdafx.h"
#include "Bomb.h"

namespace mainGame {
	namespace item {

		void Bomb::InitData()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_position = { -200.0f,50.0f,200.0f };

			m_endTime = 5.0f;
		}

		void Bomb::Efficacy()
		{
			m_player->SetMoveSpeed({ 0.0f,100.0f,0.0f });
		}
	}
}