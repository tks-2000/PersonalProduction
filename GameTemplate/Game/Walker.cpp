#include "stdafx.h"
#include "Walker.h"

namespace mainGame {
	namespace enemy {

		const char* WALKER_MODEL_TKM_FILEPATH = "Assets/modelData/unityChan/utc_red.tkm";

		const char* WALKER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";
		/// @brief �G���f���̃X�P���g���t�@�C���p�X
		const char* WALKER_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief �G�̍ő�̗�
		const int WALKER_MAX_HP = 3;
		/// @brief �A�j���[�V�����⊮��
		const float WALKER_ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief �폜�����܂ł̎���
		const float WALKER_DELETE_TIME = 5.0f;

		void Walker::InitData(const EnemyInitData& enemyInitData)
		{
			//�̗�
			m_hp = WALKER_MAX_HP;

			//�폜����
			m_deleteTime = WALKER_DELETE_TIME;

			//�����o�N���X��������
			//m_enemyMove.Init(this);
			m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);
			m_enemyEffect.Init(this);

			//���f�����A�j���[�V�����L��ŏ�����
			/*m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				WALKER_MODEL_TKM_FILEPATH,
				render::model::enMainRenderTarget,
				WALKER_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init(WALKER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);*/

			m_tkmFilepath = WALKER_MODEL_TKM_FILEPATH;
			m_tksFilepath = WALKER_MODEL_TKS_FILEPATH;
			m_animation = m_enemyAnimation.GetAnimationClip();
			m_animationNum = m_enemyAnimation.GetAnimationNum();
			m_mapModelFilepath = WALKER_MAP_MODEL_FILEPATH;

			
		}

		void Walker::ExecuteBehavior()
		{
			switch (m_game->GetGameState())
			{
			case enGameStart: {

			}break;
			case enGameInProgress: {
				m_enemyRouteMove.Execution();
				m_enemyRotation.RotationExecute();
				m_enemyAttack.Execution();
				m_enemyEffect.Execution();
				if (m_state == enEnemyDown) {
					DownExecution();
				}

			}break;
			case enGameClear: {
				m_state = enEnemyDown;
			}break;
			case enGameOver: {
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