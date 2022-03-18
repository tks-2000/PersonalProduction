#include "stdafx.h"
#include "Walker.h"

namespace mainGame {
	namespace enemy {

		const char* WALKER_MODEL_TKM_FILEPATH = "Assets/modelData/unityChan/utc_PBR_red.tkm";

		const char* WALKER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";
		/// @brief �G���f���̃X�P���g���t�@�C���p�X
		const char* WALKER_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/utc_PBR.tks";
		/// @brief �G�̍ő�̗�
		const int WALKER_MAX_HP = 3;
		/// @brief �A�j���[�V�����⊮��
		const float WALKER_ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief �폜�����܂ł̎���
		const float WALKER_DELETE_TIME = 5.0f;

		Walker::Walker()
		{

		}

		Walker::~Walker()
		{
			if (m_isModelDisplay == true) {
				DeleteGO(m_enemyModel);
				DeleteGO(m_enemyMapModel);
			}
		}

		void Walker::InitData(const EnemyInitData& enemyInitData)
		{
			//�̗�
			m_hp = WALKER_MAX_HP;

			//�폜����
			m_deleteTime = WALKER_DELETE_TIME;

			SearchAttackPointAndTarget();

			//�����o�N���X��������
			//m_enemyMove.Init(this);
			m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);
			m_enemyEffect.Init(this);

			m_enemyRouteMove.SetMoveTarget(m_moveTarget);

			m_tkmFilepath = WALKER_MODEL_TKM_FILEPATH;
			m_tksFilepath = WALKER_MODEL_TKS_FILEPATH;
			m_animation = m_enemyAnimation.GetAnimationClip();
			m_animationNum = m_enemyAnimation.GetAnimationNum();
			m_mapModelFilepath = WALKER_MAP_MODEL_FILEPATH;
			
			
		}

		void Walker::ExecuteBehavior()
		{
			switch (m_gameScene->GetGameSceneState())
			{
			case enGameSceneStart: {

			}break;
			case enGameSceneInProgress: {
				
				m_enemyRouteMove.Execution();
				m_enemyRotation.RotationExecute();
				m_enemyAttack.Execution();
				m_enemyEffect.Execution();
				if (m_state == enEnemyDown) {
					DownExecution();
				}

			}break;
			case enGameSceneClear: {
				m_state = enEnemyDown;
			}break;
			case enGameSceneOver: {
				m_state = enEnemyIdle;
			}break;
			default:
				break;
			}

			//�A�j���[�V������i�߂�
			m_enemyAnimation.AnimationUpdate();

			if (m_isModelDisplay == true) {
				m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), WALKER_ANIMATION_COMPLEMENTARY_RATE);
			}
		}
	}
}