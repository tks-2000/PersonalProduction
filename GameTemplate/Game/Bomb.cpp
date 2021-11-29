#include "stdafx.h"
#include "Bomb.h"

namespace mainGame {
	namespace item {

		void Bomb::Init()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_position = { 0.0f,200.0f,0.0f };
		}
	}
}