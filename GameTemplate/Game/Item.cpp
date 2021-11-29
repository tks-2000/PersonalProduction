#include "stdafx.h"
#include "Item.h"

namespace mainGame {
	namespace item {
		Item::Item()
		{

		}

		Item::~Item()
		{
			DeleteGO(m_itemModel);
		}

		void Item::Init()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_position = { 0.0f,100.0f,0.0f };

		}

		void Item::Execution()
		{
			m_itemModel->SetPosition(m_position);

			m_itemModel->Execution();
		}
	}
}