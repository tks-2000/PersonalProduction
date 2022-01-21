#include "stdafx.h"
#include "Chaser.h"

namespace mainGame {
	namespace enemy {
		const char* CHASER_MODEL_TKM_FILEPATH = "Assets/modelData/unityChan/utc_green.tkm";

		const char* CHASER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";
		/// @brief �G���f���̃X�P���g���t�@�C���p�X
		const char* CHASER_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief �G�̍ő�̗�
		const int CHASER_MAX_HP = 3;
		/// @brief �A�j���[�V�����⊮��
		const float CHASER_ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief �폜�����܂ł̎���
		const float CHASER_DELETE_TIME = 5.0f;

		const float SEARCH_DISTANCE = 500.0f;

		const float SEARCH_ANGLE_MATCH_RATE = 0.7f;

		const float CHASE_END_TIME = 5.0f;

		void Chaser::InitData(const EnemyInitData& enemyInitData)
		{
			//�̗�
			m_hp = CHASER_MAX_HP;

			//�폜����
			m_deleteTime = CHASER_DELETE_TIME;

			//�����o�N���X��������
			//m_enemyMove.Init(this);
			m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttackThePlayer.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);
			m_enemyEffect.Init(this);

			//���f�����A�j���[�V�����L��ŏ�����
			/*m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				CHASER_MODEL_TKM_FILEPATH,
				render::model::enMainRenderTarget,
				CHASER_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init(CHASER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);

			m_isModelDisplay = true;*/

			m_tkmFilepath = CHASER_MODEL_TKM_FILEPATH;
			m_tksFilepath = CHASER_MODEL_TKS_FILEPATH;
			m_animation = m_enemyAnimation.GetAnimationClip();
			m_animationNum = m_enemyAnimation.GetAnimationNum();
			m_mapModelFilepath = CHASER_MAP_MODEL_FILEPATH;

			//CreateModel();

			/*m_player = FindGO<player::Player>(player::PLAYER_NAME);
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);*/
		}

		const bool Chaser::IsHitAttack()
		{
			if (m_enemyAttack.IsHit() == true || m_enemyAttackThePlayer.IsHit() == true) {
				return true;
			}

			return false;
		}

		void Chaser::ExecuteBehavior()
		{
			switch (m_game->GetGameState())
			{
			case enGameStart: {

			}break;
			case enGameInProgress: {

				//�v���C���[��T��
				PlayerSearch();

				//�����Ă���Ƃ��c
				if (m_state == enEnemyMove) {
					//�ǐՏ�ԂȂ�c
					if (m_chaseMode == true) {
						//�ړ��ڕW���v���C���[�ɐݒ�
						m_enemyRouteMove.SetMoveTarget(m_player->GetPlayerPosition());
						
					}
					//�ǐՂ��Ă��Ȃ���ԂȂ�c
					else {
						//�ړ��ڕW��h�q�Ώۂɐݒ�
						m_enemyRouteMove.SetMoveTarget(m_defensiveTarget->GetPosition());
					}
				}
				//�ړ������s
				m_enemyRouteMove.Execution();
				//��]�����s
				m_enemyRotation.RotationExecute();

				m_enemyEffect.Execution();

				//�ǐՏ�ԂȂ�c
				if (m_chaseMode == true) {
					//�v���C���[�ɑ΂���U�������s
					m_enemyAttackThePlayer.Execution();
				}
				//�ǐՏ�ԂłȂ��Ȃ�c
				else {
					//�h�q�Ώۂɑ΂���U�������s
					m_enemyAttack.Execution();
				}

				//�_�E����Ԃ̂Ƃ��̓_�E����Ԃ̏������s��
				if (m_state == enEnemyDown) {
					DownExecution();
				}
				

			}break;
			case enGameClear: {

			}break;
			case enGameOver: {

			}break;
			default:
				break;
			}

			//�A�j���[�V������i�߂�
			m_enemyAnimation.AnimationUpdate();

			if (m_isModelDisplay == true) {
				m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), CHASER_ANIMATION_COMPLEMENTARY_RATE);
			}
			
		}

		void Chaser::PlayerSearch()
		{
			//�_���[�W����_�E�����͎��s���Ȃ�
			if (m_state == enEnemyDamage || m_state == enEnemyDown) {
				return;
			}

			//�v���C���[�Ɍ������x�N�g�������߂�
			Vector3 toPlayerPosition = m_player->GetPlayerPosition() - m_position;

			//�v���C���[�Ƃ̋������T���͈͓��̂Ƃ��c
			if (toPlayerPosition.Length() < SEARCH_DISTANCE) {

				//�v���C���[�֐L�т�x�N�g���𐳋K��
				toPlayerPosition.Normalize();

				//�����̌����ƃv���C���[�ւ̃x�N�g���̓��ς����߂�
				float rate = Dot(toPlayerPosition, m_enemyRotation.GetDirection());

				//���ς̌��ʂ��T���͈͓��̂Ƃ��c
				if (rate >= SEARCH_ANGLE_MATCH_RATE) {
					if (m_chaseMode == false) {
						//���̏�ŏ������˂�
						Vector3 speed = { 0.0f,2000.0f,0.0f };
						m_enemyRouteMove.SetMoveSpeed(speed);
						//�ړ����J�n
						m_state = enEnemyMove;
						//�ǐՏ�ԂɈڍs
						m_chaseMode = true;
					}
				}
				//���ς̌��ʂ��T���͈͊O�̂Ƃ��c
				else {
					//�ǐՏ�ԂȂ�c
					if (m_chaseMode == true) {
						//�ǐՎ��Ԃ𑝂₷
						m_chaseTimer += g_gameTime->GetFrameDeltaTime();
					}
				}
			}
			//�v���C���[�Ƃ̋������T���͈͊O�̂Ƃ��c
			else {
				//�ǐՏ�ԂȂ�c
				if (m_chaseMode == true) {
					//�ǐՎ��Ԃ𑝂₷
					m_chaseTimer += g_gameTime->GetFrameDeltaTime();
				}
			}

			//�ǐՎ��Ԃ��ǐՏI�����Ԃ܂ŒB������c
			if (m_chaseTimer >= CHASE_END_TIME) {
				//�ǐՎ��Ԃ����ɖ߂�
				m_chaseTimer = 0.0f;
				//�ǐՏ�Ԃ���߂�
				m_chaseMode = false;
				//���̏�ŗl�q������
				m_enemyRotation.StartSeeTheSituation();
				m_state = enEnemySeeTheSituation;
				m_enemyRouteMove.SetMoveTarget(m_defensiveTarget->GetPosition());
			}
		}
	}
}