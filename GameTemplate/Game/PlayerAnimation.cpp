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
			m_playerAnimationClip[enPlayerAnimationIdle].Load("Assets/animData/hero/Hero_Idle.tka");
			m_playerAnimationClip[enPlayerAnimationIdle].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationWark].Load("Assets/animData/hero/Hero_Walk.tka");
			m_playerAnimationClip[enPlayerAnimationWark].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationRun].Load("Assets/animData/hero/Hero_Run.tka");
			m_playerAnimationClip[enPlayerAnimationRun].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationAttack].Load("Assets/animData/hero/Hero_Attack.tka");
			m_playerAnimationClip[enPlayerAnimationAttack].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationClear].Load("Assets/animData/hero/Hero_Clear.tka");
			m_playerAnimationClip[enPlayerAnimationClear].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationDamage].Load("Assets/animData/hero/Hero_Damage.tka");
			m_playerAnimationClip[enPlayerAnimationDamage].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationKneelDown].Load("Assets/animData/hero/Hero_Down.tka");
			m_playerAnimationClip[enPlayerAnimationKneelDown].SetLoopFlag(false);
		}

		Animation::~Animation()
		{

		}

		void Animation::Init(Player* pl)
		{
			//�f�[�^���擾
			m_player = pl;

			m_game = FindGO<Game>(GAME_NAME);

			//����������
			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			switch (m_game->GetGameState())
			{
			case enGameStart: {
				m_playerAnimState = enPlayerAnimationIdle;
			}break;
			case enGameInProgress: {
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
					m_playerAnimState = enPlayerAnimationRun;
				}break;
				case enPlayerAttack: {
					m_playerAnimState = enPlayerAnimationAttack;
				}break;
				case enPlayerDamage: {
					m_playerAnimState = enPlayerAnimationDamage;
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