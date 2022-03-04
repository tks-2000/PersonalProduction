#include "stdafx.h"
#include "TitleModels.h"

namespace mainGame {
	namespace title {
		
		const int PLAYER_ANIMATION_NUM = 2;
		const char* PLAYER_MODEL_FILEPATH = "Assets/modelData/character/HeroPBR.tkm";
		const char* PLAYER_SKELTON_FILEPATH = "Assets/modelData/character/HeroPBR.tks";
		const char* PLAYER_ANIMATION_FILEPATH[PLAYER_ANIMATION_NUM] = {
			"Assets/animData/hero/Hero_Idle.tka",
			"Assets/animData/hero/Hero_Clear.tka"
		};
		const Vector3 PLAYER_MODEL_POS = { 0.0f,0.0f,400.0f };
		const Vector3 PLAYER_MODEL_SCALE = { 2.0f,2.0f,2.0f };
		/// @brief 剣のモデルファイルパス
		const char* SWORD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Sword.tkm";
		/// @brief 盾のモデルファイルパス
		const char* SHIELD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Shield.tkm";
		/// @brief 剣の位置を決めるボーンの名前
		const wchar_t* SWORD_POS_BONE_NAME = L"hand_l";
		/// @brief 盾の位置を決めるボーンの名前
		const wchar_t* SHIELD_POS_BONE_NAME = L"hand_r";

		const int ENEMY_MODEL_NUM = 2;
		const char* ENEMY_MODEL_FILEPATH[ENEMY_MODEL_NUM] = {
			"Assets/modelData/unityChan/utc_green.tkm",
			"Assets/modelData/unityChan/utc_red.tkm"
		};
		const char* ENEMY_SKELTON_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		const char* ENEMY_ANIMATION_FILEPATH = "Assets/animData/unityChan/idle.tka";
		const Vector3 ENEMY_MODEL_POS[ENEMY_MODEL_NUM] = {
			{ 350.0f,0.0f,0.0f },
			{ -350.0f,0.0f,0.0f }
		};

		const char* STAGE_MODEL_FILEPATH = "Assets/modelData/bg/Stage2.tkm";
		const char* BACKGROUND_MODEL_FILEPATH = "Assets/modelData/bg/sky_a.tkm";
		const char* HOUSE_MODEL_FILEPATH = "Assets/modelData/bg/house.tkm";

		const float PLAYER_MODEL_ANGLE = -10.0f;

		const float ENEMY_MODEL_ANGLE[ENEMY_MODEL_NUM] = {
			-150.0f,
			150.0f
		};

		Models::Models()
		{

		}

		Models::~Models()
		{
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
			m_isInitd = true;
		}

		void Models::Execution()
		{
			if (m_isInitd == false) {
				return;
			}
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
			//プレイヤーのスケルトン情報を取得
			Skeleton* heroSkeleton = m_plModel->GetSkeleton();

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