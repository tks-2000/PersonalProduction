#include "stdafx.h"
#include "Enemy.h"

namespace mainGame {
	namespace enemy {

		/// @brief �G���f���̃t�@�C���p�X
		/*const char* ENEMY_MODEL_TKM_FILEPATH[enEnemyTypeNum] = {
			"Assets/modelData/unityChan/utc_green.tkm",
			"Assets/modelData/unityChan/utc_red.tkm",
			"Assets/modelData/unityChan/utc_blue.tkm"
		};*/

		//const char* ENEMY_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";


		/// @brief �G���f���̃X�P���g���t�@�C���p�X
		//const char* ENEMY_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief �G�̍ő�̗�
		//const int MAX_HP = 3;

		/// @brief �A�j���[�V�����⊮��
		//const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief �폜�����܂ł̎���
		const float DELETE_TIME = 5.0f;

		Enemy::Enemy()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Enemy::~Enemy()
		{
			
			DeleteGO(m_enemyModel);

			DeleteGO(m_enemyMapModel);
		}

		void Enemy::Init(const EnemyInitData& initData)
		{
			//�������ς݁E��������񂪐������Ȃ��ꍇ���s���Ȃ�
			if (m_isInitd == true || initData.enemyType == enEnemyTypeNum) {
				return;
			}

			//���g�̔ԍ���ݒ�
			m_enemyNum = initData.enemyNum;
			
			//���g�̃^�C�v��ݒ�
			m_enemyType = initData.enemyType;

			//�������W��ݒ�
			m_position = initData.enemyStartPos;


			InitData(initData);

			m_game = FindGO<Game>(GAME_NAME);
			//�G������̏������
			m_generator = FindGO<Generator>(ENEMY_GENERATOR_NAME);
			//�v���C���[�̏������
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_defensiveTarget = FindGO < defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
			//�v���C���[�Ɏ����̏���ǉ�
			m_player->SetEnemyData(this);
			//�ҋ@���ŊJ�n
			m_state = enEnemyIdle;
			//����������
			m_isInitd = true;
		}

		

		void Enemy::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			if (m_defeatFlag == true) {
				DeleteEnemy();
				return;
			}

			ExecuteBehavior();
		
			//�A�j���[�V������i�߂�
			//m_enemyAnimation.AnimationUpdate();

			//���f���ɍX�V���ꂽ����`����
			m_enemyModel->SetPosition(m_position);

			m_enemyMapModel->SetPosition(m_position);

			m_enemyModel->SetRotation(m_qRot);

			m_enemyMapModel->SetRotation(m_qRot);

			//m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_enemyModel->Execution();

			m_enemyMapModel->Execution();


			if (m_position.y < -1000.0f) {
				//������ɍ폜��`����
				m_generator->DeleteEnemy(this);
				m_player->DeleteEnemyData(this);
				//���g���폜
				DeleteGO(this);
			}
		}

		void Enemy::SetMoveSpeed(const Vector3& speed)
		{
			//m_enemyRouteMove.SetMoveSpeed(speed);
		}
		

		void Enemy::ReceiveDamage(const int damage)
		{
			//�_���[�W���󂯂�
			m_hp -= damage;

			//m_enemyRotation.StartSeeTheSituation();

			//�̗͂�0�ȉ��ɂȂ�����
			if (m_hp <= 0) {
				//�_�E����ԂɈڍs
				m_state = enEnemyDown;
				m_hp = 0;
			}
		}

		void Enemy::DeleteEnemy()
		{
			//������ɍ폜��`����
			m_generator->DeleteEnemy(this);
			m_player->DeleteEnemyData(this);
			//���g���폜
			DeleteGO(this);
		}

		void Enemy::InitData(const EnemyInitData& initData)
		{
			//�̗�
			m_hp = 0;

			//�폜����
			m_deleteTime = DELETE_TIME;

			//�����o�N���X��������
			//m_enemyMove.Init(this);
			//m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			//m_enemyAttack.Init(this);
			//m_enemyAnimation.Init(this);

			//���f����������
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				"Assets/modelData/unityChan/utc_green.tkm",
				render::model::enMainRenderTarget
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init("Assets/modelData/miniMap/enemyMapModel.tkm", render::model::enExpandModelGroup1);
		}

		void Enemy::ExecuteBehavior()
		{
			switch (m_game->GetGameState())
			{
			case enGameStart: {

			}break;
			case enGameInProgress: {
				//m_enemyRouteMove.Execution();
				//m_qRot = m_enemyRotation.RotationExecute(m_enemyRouteMove.GetMoveSpeed());
				//m_enemyAttack.Execution();
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

		}

		void Enemy::DownExecution()
		{
			//�폜�܂ł̎��Ԃ�i�߂�
			m_deleteTimer += g_gameTime->GetFrameDeltaTime();

			//�폜���ԂɒB������c
			if (m_deleteTimer >= m_deleteTime) {
				m_defeatFlag = true;
			}
		}

		
	}
}