#include "stdafx.h"
#include "GameUI.h"

namespace mainGame {
	namespace ui {
		GameUI::GameUI()
		{

		}

		GameUI::~GameUI()
		{
			//DeleteGO(m_test);
		}

		void GameUI::Init()
		{
			//m_test = NewGO <render::font::FontRender>(PRIORITY_VERYLOW);
			//m_test->Init(L"test");

			m_oenedItem.Init();

			m_baseEndurance.Init();

			m_timeLimit.Init();

			m_isInitd = true;
		}

		void GameUI::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			//m_test->Execution();

			m_oenedItem.Execution();

			m_baseEndurance.Execution();

			m_timeLimit.Execution();
		}
	}
}