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
			m_playerAnimationClip[enPlayerIdle].Load("Assets/animData/idle.tka");
			m_playerAnimationClip[enPlayerIdle].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerWark].Load("Assets/animData/walk.tka");
			m_playerAnimationClip[enPlayerWark].SetLoopFlag(true);
		}

		Animation::~Animation()
		{

		}

		void Animation::Init()
		{
			//データを取得
			m_player = FindGO<Player>(PLAYER_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

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
				//m_playerAnimState = enPlayerAnimationNum;
			}break;
			case enPlayerDamage: {
				m_playerAnimState = enPlayerAnimationIdle;
			}break;
			default:
				break;
			}
		}
		
	}
}