#include "stdafx.h"
#include "PlayerAnimation.h"

namespace {
	
}

namespace mainGame {
	namespace player {

		Animation::Animation()
		{
			//���������ŊJ�n
			m_isInitd = false;

			//�A�j���[�V�����N���b�v�����[�h
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
			//�f�[�^���擾
			m_player = FindGO<Player>(PLAYER_NAME);

			//����������
			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//��Ԃɂ���čĐ�����A�j���[�V������ς���
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