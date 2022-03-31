#include "stdafx.h"
#include "TitleModels.h"

namespace mainGame {
	namespace title {
		
		/// @brief �v���C���[���f���̃t�@�C���p�X
		const char* PLAYER_MODEL_FILEPATH = "Assets/modelData/character/HeroPBR.tkm";
		/// @brief �v���C���[�̃X�P���g���t�@�C���p�X
		const char* PLAYER_SKELTON_FILEPATH = "Assets/modelData/character/HeroPBR.tks";
		/// @brief �v���C���[�̃A�j���[�V�����t�@�C���p�X
		const char* PLAYER_ANIMATION_FILEPATH[enTitlePlAnimNum] = {
			"Assets/animData/hero/Hero_Idle.tka",
			"Assets/animData/hero/Hero_Clear.tka"
		};
		/// @brief �v���C���[���f���̍��W
		const Vector3 PLAYER_MODEL_POS = { 0.0f,0.0f,400.0f };
		/// @brief �v���C���[���f���̊g�嗦
		const Vector3 PLAYER_MODEL_SCALE = { 2.0f,2.0f,2.0f };
		/// @brief ���̃��f���t�@�C���p�X
		const char* SWORD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Sword.tkm";
		/// @brief ���̃��f���t�@�C���p�X
		const char* SHIELD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Shield.tkm";
		/// @brief ���̈ʒu�����߂�{�[���̖��O
		const wchar_t* SWORD_POS_BONE_NAME = L"hand_l";
		/// @brief ���̈ʒu�����߂�{�[���̖��O
		const wchar_t* SHIELD_POS_BONE_NAME = L"hand_r";
		/// @brief �G�l�~�[���f���̐�
		const int ENEMY_MODEL_NUM = 2;
		/// @brief �G�l�~�[���f���̃t�@�C���p�X
		const char* ENEMY_MODEL_FILEPATH[ENEMY_MODEL_NUM] = {
			"Assets/modelData/unityChan/utc_PBR.tkm",
			"Assets/modelData/unityChan/utc_PBR_red.tkm"
		};
		/// @brief �G�l�~�[�̃X�P���g���t�@�C���p�X
		const char* ENEMY_SKELTON_FILEPATH = "Assets/modelData/unityChan/utc_PBR.tks";
		/// @brief �G�l�~�[�̃A�j���[�V�����t�@�C���p�X
		const char* ENEMY_ANIMATION_FILEPATH = "Assets/animData/unityChan/idle.tka";
		/// @brief �G�l�~�[���f���̍��W
		const Vector3 ENEMY_MODEL_POS[ENEMY_MODEL_NUM] = {
			{ 350.0f,0.0f,0.0f },
			{ -350.0f,0.0f,0.0f }
		};
		/// @brief �X�e�[�W���f���̃t�@�C���p�X
		const char* STAGE_MODEL_FILEPATH = "Assets/modelData/bg/Stage2.tkm";
		/// @brief �w�i���f���̃t�@�C���p�X
		const char* BACKGROUND_MODEL_FILEPATH = "Assets/modelData/bg/sky_a.tkm";
		/// @brief �Ƃ̃��f���t�@�C���p�X
		const char* HOUSE_MODEL_FILEPATH = "Assets/modelData/bg/house.tkm";
		/// @brief �v���C���[���f���̊p�x
		const float PLAYER_MODEL_ANGLE = -10.0f;
		/// @brief �G�l�~�[���f���̊p�x
		const float ENEMY_MODEL_ANGLE[ENEMY_MODEL_NUM] = {
			-150.0f,
			150.0f
		};

		Models::Models()
		{

		}

		Models::~Models()
		{
			//�o�������f�����폜
			DeleteGO(m_plModel);
			DeleteGO(m_swordModel);
			DeleteGO(m_shieldModel);
			for (int enemyModelNum = 0; enemyModelNum < ENEMY_MODEL_NUM; enemyModelNum++) {
				DeleteGO(m_enemyModel[enemyModelNum]);
			}
			DeleteGO(m_stageModel);
			DeleteGO(m_backgroundModel);
			DeleteGO(m_houseModel);
		}

		void Models::Init(Title* title)
		{
			//�e���f�����쐬��������
			m_plAnim[enTitlePlIdle].Load(PLAYER_ANIMATION_FILEPATH[enTitlePlIdle]);
			m_plAnim[enTitlePlIdle].SetLoopFlag(true);
			m_plAnim[enTitlePlClear].Load(PLAYER_ANIMATION_FILEPATH[enTitlePlClear]);
			m_plAnim[enTitlePlClear].SetLoopFlag(false);
			m_plModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_plModel->InitDeferrd(
				PLAYER_MODEL_FILEPATH,
				true,
				PLAYER_SKELTON_FILEPATH,
				m_plAnim,
				enTitlePlAnimNum
			);
			m_plModel->SetPosition(PLAYER_MODEL_POS);
			m_plModel->SetScale(PLAYER_MODEL_SCALE);
			Quaternion qRot;
			qRot.SetRotationDegY(PLAYER_MODEL_ANGLE);
			m_plModel->SetRotation(qRot);
			m_plModel->CreateShadow();
			m_plAnimState = enTitlePlIdle;

			m_swordModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_swordModel->InitDeferrd(SWORD_MODEL_FILEPATH,true);
			m_swordModel->CreateShadow();

			m_shieldModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_shieldModel->InitDeferrd(SHIELD_MODEL_FILEPATH,true);
			m_shieldModel->CreateShadow();

			m_enemyAnim[enTitleEnemyIdle].Load(ENEMY_ANIMATION_FILEPATH);
			m_enemyAnim[enTitleEnemyIdle].SetLoopFlag(true);

			for (int enemyModelNum = 0; enemyModelNum < ENEMY_MODEL_NUM; enemyModelNum++) {
				m_enemyModel[enemyModelNum] = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
				m_enemyModel[enemyModelNum]->InitDeferrd(
					ENEMY_MODEL_FILEPATH[enemyModelNum],
					false,
					ENEMY_SKELTON_FILEPATH,
					m_enemyAnim,
					enTitleEnemyAnimNum,
					EnModelUpAxis::enModelUpAxisY
					);
				m_enemyModel[enemyModelNum]->SetPosition(ENEMY_MODEL_POS[enemyModelNum]);
				qRot.SetRotationDegY(ENEMY_MODEL_ANGLE[enemyModelNum]);
				m_enemyModel[enemyModelNum]->SetRotation(qRot);
			}

			m_stageModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_stageModel->InitDeferrd(STAGE_MODEL_FILEPATH,true);

			m_backgroundModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_backgroundModel->InitDeferrd(BACKGROUND_MODEL_FILEPATH,true);

			m_houseModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_houseModel->InitDeferrd(HOUSE_MODEL_FILEPATH,true);

			m_title = title;
			//����������
			m_isInitd = true;
		}

		void Models::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�e���f���̏��������s
			m_plModel->PlayAnimation(m_plAnimState);
			m_plModel->Execution();
			for (int enemyModelNum = 0; enemyModelNum < ENEMY_MODEL_NUM; enemyModelNum++) {
				m_enemyModel[enemyModelNum]->Execution();
			}
			m_stageModel->Execution();
			m_backgroundModel->Execution();
			m_houseModel->Execution();
			SetWeapons();
		}

		void Models::SetWeapons()
		{
			//�v���C���[�̃X�P���g�������擾
			Skeleton* heroSkeleton = m_plModel->GetSkeleton();
			//���̃��f���̍��W��ݒ肷��{�[���̔ԍ������
			int boneId = heroSkeleton->FindBoneID(SWORD_POS_BONE_NAME);
			//�{�[���̔ԍ�����ݒ肷��{�[�������
			Bone* hand = heroSkeleton->GetBone(boneId);
			//�{�[���̃��[���h�s������
			Matrix boneMatrix = hand->GetWorldMatrix();
			//���̃��f���̃��[���h�s���ݒ�
			m_swordModel->SetWorldMatrix(boneMatrix);
			m_swordModel->Execution();

			//���̃��f���̍��W��ݒ肷��{�[���̔ԍ������
			boneId = heroSkeleton->FindBoneID(SHIELD_POS_BONE_NAME);
			//�{�[���̔ԍ�����ݒ肷��{�[�������
			hand = heroSkeleton->GetBone(boneId);
			//�{�[���̃��[���h�s������
			boneMatrix = hand->GetWorldMatrix();
			//���̃��f���̃��[���h�s���ݒ�
			m_shieldModel->SetWorldMatrix(boneMatrix);
			m_shieldModel->Execution();
		}
	}
}