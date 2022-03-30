#include "stdafx.h"
#include "PlayerAnimation.h"

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
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//����������
			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�Q�[���V�[���̏�Ԃɂ���čĐ�����A�j���[�V������ς���
			switch (m_gameScene->GetGameSceneState())
			{
				//�Q�[���J�n��
			case enGameSceneStart: {
				//�ҋ@�A�j���[�V�������Đ�
				m_playerAnimState = enPlayerAnimationIdle;
			}break;
				//�Q�[�����s��
			case enGameSceneInProgress: {
				
				//�v���C���[�̏�Ԃɂ���čĐ�����A�j���[�V������ς���
				switch (m_player->GetPlayerStatus())
				{
					//�ҋ@��
				case enPlayerIdle: {
					//�ҋ@�A�j���[�V�������Đ�
					m_playerAnimState = enPlayerAnimationIdle;
				}break;
					//���s��
				case enPlayerWark: {
					//���s�A�j���[�V�������Đ�
					m_playerAnimState = enPlayerAnimationWark;
				}break;
					//���s��
				case enPlayerRun: {
					//���s�A�j���[�V�������Đ�
					m_playerAnimState = enPlayerAnimationRun;
				}break;
					//�U����
				case enPlayerAttack: {
					//�U���A�j���[�V�������Đ�
					m_playerAnimState = enPlayerAnimationAttack;
				}break;
					//�_���[�W��
				case enPlayerDamage: {
					//�_���[�W�A�j���[�V�������Đ�
					m_playerAnimState = enPlayerAnimationDamage;
				}break;
				default:
					break;
				}
			}break;
				//�Q�[���N���A��
			case enGameSceneClear: {
				//�N���A�̃A�j���[�V�������Đ�
				m_playerAnimState = enPlayerAnimationClear;
			}break;
				//�Q�[���I�[�o�[��
			case enGameSceneOver: {
				//�Q�[���I�[�o�[�̃A�j���[�V�������Đ�
				m_playerAnimState = enPlayerAnimationKneelDown;
			}
			default:
				break;
			}
		}
		
	}
}