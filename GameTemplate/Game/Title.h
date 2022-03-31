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
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();

		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �摜
			render::sprite::SpriteRender* m_titleSprite = nullptr;
			/// @brief �t�H���g
			render::font::FontRender* m_font = nullptr;
			/// @brief �Q�[��
			Game* m_game = nullptr;
			/// @brief �^�C�g�����f��
			Models m_models;
			/// @brief �^�C�g���T�E���hID
			int m_titleSoundID = 0;
			/// @brief �X�^�[�g�T�E���hID
			int m_startSoundID = 0;
			/// @brief �T�E���h�v���C���[
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief �I���t���O
			bool m_endFlag = false;
			/// @brief �V�[���J��
			SceneTransition* m_sceneTransition = nullptr;
		};
	}
}
