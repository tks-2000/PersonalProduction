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
		/// @brief �Q�[������UI�𐧌䂷��N���X
		class GameUI : public IGameObject
		{
		public:
			GameUI();
			~GameUI();
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief �X�^�[�g���̃t�H���g��\������
			void DisplayStartFont();
			/// @brief �Q�[���I�����̉摜��\������
			void DisplayGameEndSprite();
			
		private:
			/// @brief �X�^�[�g���̃t�H���g�\�������s
			void StartFontExecution();
			/// @brief �Q�[���I�����̉摜�\�������s
			void GameEndSpriteExecution();
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �X�^�[�g���̃t�H���g�\���t���O
			bool m_startFontFlag = false;
			/// @brief �X�^�[�g���̃t�H���g
			render::font::FontRender* m_startFont = nullptr;
			/// @brief �X�^�[�g���̃t�H���g��������܂ł̃^�C�}�[
			float m_startFontDisplayTimer = 0.0f;
			/// @brief �Q�[���I�����̉摜�\���t���O
			bool m_gameEndSpriteFlag = false;
			/// @brief �Q�[���I�����̉摜
			render::sprite::SpriteRender* m_gameEndSprite = nullptr;

			/// @brief ���L�A�C�e��
			OwnedItem m_oenedItem;
			/// @brief ���_�̑ϋv��
			BaseEndurance m_baseEndurance;
			/// @brief ��������
			TimeLimit m_timeLimit;
			/// @brief �c�e
			RemainingBullets m_remainingBullets;

			/// @brief �Q�[��
			Game* m_game = nullptr;
			/// @brief �^�C�}�[
			timer::Timer* m_timer = nullptr;
		};
	}
}
