#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief �v���C���[�̃��f���t�@�C���p�X
	const char* PLAYER_TKM_FILEPATH = "Assets/modelData/character/HeroPBR.tkm";
	/// @brief �v���C���[�̃X�P���g���t�@�C���p�X
	const char* PLAYER_TKS_FILEPATH = "Assets/modelData/character/HeroPBR.tks";
	/// @brief �v���C���[�̃~�j�}�b�v��̃��f���t�@�C���p�X
	const char* PLAYER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/plMapModel.tkm";
	/// @brief ���̃��f���t�@�C���p�X
	const char* SWORD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Sword.tkm";
	/// @brief ���̃��f���t�@�C���p�X
	const char* SHIELD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Shield.tkm";
	/// @brief ���̈ʒu�����߂�{�[���̖��O
	const wchar_t* SWORD_POS_BONE_NAME = L"hand_l";
	/// @brief ���̈ʒu�����߂�{�[���̖��O
	const wchar_t* SHIELD_POS_BONE_NAME = L"hand_r";
	/// @brief �A�j���[�V�����⊮��
	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
	/// @brief �v���C���[�̏������W
	const Vector3 PLAYER_START_POS = { 0.0f,500.0f,0.0f };
	/// @brief �_���[�W���畜�A����܂ł̎���
	const float PLAYER_DAMAGE_RETURN_TIME = 1.0f;

	const float PLAYER_INVINCIBLE_RETURN_TIME = 3.0f;
}
namespace mainGame {
	namespace player {
		Player::Player()
		{
			m_isInitd = false;
		}

		Player::~Player()
		{
			DeleteGO(m_playerModel);
			DeleteGO(m_swordModel);
			DeleteGO(m_shieldModel);
			DeleteGO(m_plMapModel);
		}

		void Player::Init()
		{
			if (m_isInitd == true) {
				return;
			}

			//�����ʒu��ݒ�
			m_position = PLAYER_START_POS;

			//�f�[�^�����o�N���X��������
			m_playerMove.Init(this);
			m_playerRot.Init(this);
			m_playerAnimation.Init(this);
			m_playerAttack.Init(this);
			m_playerEffect.Init(this);
			m_playerSound.Init(this);
			m_itemSlot.Init(this);

			//�v���C���[�̃��f����������
			m_playerModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_playerModel->InitDeferrd(
				PLAYER_TKM_FILEPATH,
				PLAYER_TKS_FILEPATH,
				m_playerAnimation.GetAnimatonClip(),
				m_playerAnimation.GetAnimationNum()
			);
			m_playerModel->SetScale({ 2.0f,2.0f,2.0f });

			m_swordModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_swordModel->InitDeferrd(SWORD_MODEL_FILEPATH);
			m_swordModel->CreateShadow();

			m_shieldModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_shieldModel->InitDeferrd(SHIELD_MODEL_FILEPATH);
			m_shieldModel->CreateShadow();

			m_plMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_plMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_plMapModel->Init(PLAYER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);

			//�v���C���[���f���̉e�𐶐�
			m_playerModel->CreateShadow();

			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			m_isInitd = true;
		}

		bool Player::Start()
		{
			

			return true;
		}

		void Player::Update()
		{
			
		}

		void Player::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			switch (m_gameScene->GetGameSceneState())
			{
			case enGameSceneStart: {
				
			}break;
			case enGameSceneInProgress: {
				m_playerMove.Execution();

				m_playerAttack.Execute();

				m_qRot = m_playerRot.RotationExecution(m_playerMove.GetMoveSpssd());

				m_playerEffect.Execution();

				

				m_itemSlot.Execution();

				if (m_playerState == enPlayerDamage) {
					DamageExecution();
				}
				if (m_invincibleFlag == true) {
					InvincibleExecution();
				}
			}break;
			case enGameSceneClear: {
				m_playerState = enPlayerIdle;
			}break;
			case enGameSceneOver: {
				m_playerState = enPlayerIdle;
			}break;
			default:
				break;
			}

			m_playerAnimation.AnimationUpdate();

			m_playerModel->SetPosition(m_position);

			m_plMapModel->SetPosition(m_position);

			m_playerModel->SetRotation(m_qRot);

			m_plMapModel->SetRotation(m_qRot);

			m_playerModel->PlayAnimation(m_playerAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_playerModel->Execution();

			m_plMapModel->Execution();

			m_playerSound.Execution();

			SetWeapons();

			if (m_position.y < -1000.0f) {
				m_position = PLAYER_START_POS;
				m_playerMove.SetPosition(m_position);
			}
		}

		void Player::DamageExecution()
		{
			m_damageTimer += g_gameTime->GetFrameDeltaTime();
			m_invincibleFlag = true;

			if (m_damageTimer > PLAYER_DAMAGE_RETURN_TIME) {
				m_playerState = enPlayerIdle;
				m_damageTimer = 0.0f;
			}
		}

		void Player::InvincibleExecution()
		{
			m_invincibleTimer += g_gameTime->GetFrameDeltaTime();
			if (m_invincibleTimer > PLAYER_INVINCIBLE_RETURN_TIME) {
				m_invincibleFlag = false;
				m_invincibleTimer = 0.0f;
			}
		}

		void Player::SetWeapons()
		{
			//�v���C���[�̃X�P���g�������擾
			Skeleton* heroSkeleton = m_playerModel->GetSkeleton();

			int boneId = heroSkeleton->FindBoneID(SWORD_POS_BONE_NAME);

			Bone* hand = heroSkeleton->GetBone(boneId);

			Matrix boneMatrix = hand->GetWorldMatrix();

			m_swordModel->SetWorldMatrix(boneMatrix);
			m_swordModel->Execution();

			boneId = heroSkeleton->FindBoneID(SHIELD_POS_BONE_NAME);

			hand = heroSkeleton->GetBone(boneId);

			boneMatrix = hand->GetWorldMatrix();

			m_shieldModel->SetWorldMatrix(boneMatrix);
			m_shieldModel->Execution();

		}
		
	}
}