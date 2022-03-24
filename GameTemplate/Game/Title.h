#pragma once
#include "TitleModels.h"

namespace mainGame {

	class Game;

	namespace title {
		/// @brief �^�C�g����ʂł̏������s���N���X
		class Title : public IGameObject
		{
		public:
			Title();
			~Title();
			void Init();
			void Execution();

		private:
			bool m_isInitd = false;

			render::sprite::SpriteRender* m_titleSprite = nullptr;

			render::font::FontRender* m_font = nullptr;

			Game* m_game = nullptr;

			Models m_models;

			int m_titleSoundID = 0;

			int m_startSoundID = 0;

			sound::SoundPlayer* m_soundPlayer = nullptr;

			bool m_endFlag = false;

			SceneTransition* m_sceneTransition = nullptr;
		};
	}
}
