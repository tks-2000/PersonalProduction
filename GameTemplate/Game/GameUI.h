#pragma once
#include "OwnedItem.h"
#include "BaseEndurance.h"
#include "TimeLimit.h"
#include "RemainingBullets.h"

namespace mainGame {

	class GameScene;

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
			
			/// @brief �Q�[���I�����̉摜��\������
			void DisplayGameEndSprite();
			
		private:
			
			/// @brief �Q�[���I�����̉摜�\�������s
			void GameEndSpriteExecution();
			/// @brief �������t���O
			bool m_isInitd = false;
			
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
			GameScene* m_gameScene = nullptr;
			/// @brief �^�C�}�[
			timer::Timer* m_timer = nullptr;
		};
	}
}
