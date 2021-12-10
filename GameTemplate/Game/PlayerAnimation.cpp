#include "stdafx.h"
#include "PlayerAnimation.h"

namespace {
	
}

namespace mainGame {
	namespace player {

		Animation::Animation()
		{
			//未初期化で開始
			m_isInitd = false;

			//アニメーションクリップをロード
			m_playerAnimationClip[enPlayerAnimationIdle].Load("Assets/animData/unityChan/idle.tka");
			m_playerAnimationClip[enPlayerAnimationIdle].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationWark].Load("Assets/animData/unityChan/walk.tka");
			m_playerAnimationClip[enPlayerAnimationWark].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationRun].Load("Assets/animData/unityChan/run.tka");
			m_playerAnimationClip[enPlayerAnimationRun].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationClear].Load("Assets/animData/unityChan/clear.tka");
			m_playerAnimationClip[enPlayerAnimationClear].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationKneelDown].Load("Assets/animData/unityChan/KneelDown.tka");
			m_playerAnimationClip[enPlayerAnimationKneelDown].SetLoopFlag(false);
		}

		Animation::~Animation()
		{

		}

		void Animation::Init(Player* pl)
		{
			//データを取得
			m_player = pl;

			m_game = FindGO<Game>(GAME_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			switch (m_game->GetGameState())
			{
			case enGameStart: {
				m_playerAnimState = enPlayerAnimationIdle;
			}break;
			case enGameInProgress: {
				//状態によって再生するアニメーションを変える
				switch (m_player->GetPlayerStatus())
				{
				case enPlayerIdle: {
					m_playerAnimState = enPlayerAnimationIdle;
				}break;
				case enPlayerWark: {
					m_playerAnimState = enPlayerAnimationWark;
				}break;
				case enPlayerRun: {
					m_playerAnimState = enPlayerAnimationRun;
				}break;
				case enPlayerAttack: {
					m_playerAnimState = enPlayerAnimationClear;
				}break;
				case enPlayerDamage: {
					m_playerAnimState = enPlayerAnimationIdle;
				}break;
				default:
					break;
				}
			}break;
			case enGameClear: {
				m_playerAnimState = enPlayerAnimationClear;
			}break;
			case enGameOver: {
				m_playerAnimState = enPlayerAnimationKneelDown;
			}
			default:
				break;
			}

			
		}
		
	}
}