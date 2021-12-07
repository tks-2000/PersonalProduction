#pragma once
#include "OwnedItem.h"
#include "BaseEndurance.h"
#include "TimeLimit.h"
#include "RemainingBullets.h"

namespace mainGame {

	class Game;

	namespace timer {
		class Timer;
	}

	namespace ui {
		class GameUI : public IGameObject
		{
		public:
			GameUI();
			~GameUI();
			void Init();
			void Execution();

			void DisplayStartFont();

			void DisplayGameEndSprite();

			void ApplyBaseDamage() { m_baseEndurance.ApplyDamage(); }
		private:

			void StartFontExecution();

			void GameEndSpriteExecution();

			bool m_isInitd = false;

			bool m_startFontFlag = false;

			render::font::FontRender* m_startFont = nullptr;

			float m_startFontDisplayTimer = 0.0f;

			bool m_gameEndSpriteFlag = false;

			render::sprite::SpriteRender* m_gameEndSprite = nullptr;

			OwnedItem m_oenedItem;

			BaseEndurance m_baseEndurance;

			TimeLimit m_timeLimit;

			RemainingBullets m_remainingBullets;

			Game* m_game = nullptr;

			timer::Timer* m_timer = nullptr;
		};
	}
}
