#pragma once
#include "OwnedItem.h"
#include "BaseEndurance.h"
#include "TimeLimit.h"

namespace mainGame {
	namespace ui {
		class GameUI : public IGameObject
		{
		public:
			GameUI();
			~GameUI();
			void Init();
			void Execution();

			void ApplyBaseDamage() { m_baseEndurance.ApplyDamage(); }
		private:

			bool m_isInitd = false;

			render::font::FontRender* m_test = nullptr;

			OwnedItem m_oenedItem;

			BaseEndurance m_baseEndurance;

			TimeLimit m_timeLimit;

		};
	}
}
