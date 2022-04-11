#include "stdafx.h"
#include "BaseEndurance.h"

namespace mainGame {
	namespace ui {
		
		/// @brief �ϋv�l�̉��n�摜�̃t�@�C���p�X
		const char* ENDURANCE_BASE_SPRITE_FILEPATH = "Assets/Image/base_sprite_5.dds";
		/// @brief �ϋv�l�̉��n�摜�̉���
		const int ENDURANCE_BASE_SPRITE_WIDTH = 1100;
		/// @brief �ϋv�l�̉��n�摜�̏c��
		const int ENDURANCE_BASE_SPRITE_HEIGHT = 700;
		/// @brief �ϋv�l�̉��n�摜�̍��W
		const Vector3 ENDURANCE_BASE_SPRITE_POS = { 0.0f,300.0f,0.0f };
		/// @brief �ϋv�l�̉��n�摜�̃J���[
		const Vector4 ENDURANCE_BASE_SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief �ϋv�l�̘g�摜�̃t�@�C���p�X
		const char* ENDURANCE_FRAME_SPRITE_FILEPATH = "Assets/Image/base_sprite_6.dds";
		/// @brief �ϋv�l�̉摜�̃t�@�C���p�X
		const char* ENDURANCE_SPRITE_FILEPATH = "Assets/Image/WB.dds";
		/// @brief �ϋv�l�̉摜�̉���
		const int ENDURANCE_SPRITE_WIDTH = 1000;
		/// @brief �ϋv�l�̉摜�̏c��
		const int ENDURANCE_SPRITE_HEIGHT = 30;
		/// @brief �ϋv�l�̉摜�̈ʒu
		const Vector3 ENDURANCE_SPRITE_POS = { -500.0f,300.0f,0.0f };
		/// @brief �ϋv�l�̉摜�̍Œ�l�̃J���[
		const Vector4 ENDURANCE_SPRITE_MIN_COLOR = { 0.0f,2.0f,0.0f,0.5f };
		/// @brief �ϋv�l�̉摜�̍ō��l�̃J���[
		const Vector4 ENDURANCE_SPRITE_MAX_COLOR = { 2.0f,0.0f,0.0f,0.5f };
		/// @brief �ϋv�l�̉��̉摜�̃J���[
		const Vector4 ENDURANCE_UNDER_SPRITE_COLOR = { 0.1f,0.1f,0.1f,0.5f };
		/// @brief �ϋv�l�̉摜�̒��S�ʒu
		const Vector2 ENDURANCE_SPRITE_PIVOT = { 0.0f,0.5f };

		BaseEndurance::BaseEndurance()
		{
			m_isInitd = false;
		}

		BaseEndurance::~BaseEndurance()
		{
			//�쐬�����摜���폜
			DeleteGO(m_enduranceBaseSprite);
			DeleteGO(m_enduranceBaseFrame);
			DeleteGO(m_enduranceUnderSprite);
			DeleteGO(m_enduranceSprite);
		}

		void BaseEndurance::Init()
		{
			//�ϋv�͂̉摜���쐬
			m_enduranceBaseSprite = NewGO <render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceBaseFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceUnderSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			
			
			//�摜�̏����p�����[�^�[������
			m_enduranceBaseSprite->Init(ENDURANCE_BASE_SPRITE_FILEPATH, ENDURANCE_BASE_SPRITE_WIDTH, ENDURANCE_BASE_SPRITE_HEIGHT);
			m_enduranceBaseFrame->Init(ENDURANCE_FRAME_SPRITE_FILEPATH, ENDURANCE_BASE_SPRITE_WIDTH, ENDURANCE_BASE_SPRITE_HEIGHT);
			m_enduranceBaseSprite->SetColor(ENDURANCE_BASE_SPRITE_COLOR);
			m_enduranceUnderSprite->Init(ENDURANCE_SPRITE_FILEPATH, ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);
			m_enduranceSprite->Init(ENDURANCE_SPRITE_FILEPATH, ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);
			m_enduranceUnderSprite->SetColor(ENDURANCE_UNDER_SPRITE_COLOR);
			m_enduranceSpritePos = ENDURANCE_SPRITE_POS;
			m_enduranceSpriteColor = ENDURANCE_SPRITE_MIN_COLOR;
			m_enduranceBaseFrame->SetPosition(ENDURANCE_BASE_SPRITE_POS);
			m_enduranceBaseSprite->SetPosition(ENDURANCE_BASE_SPRITE_POS);
			m_enduranceUnderSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceUnderSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);
			m_enduranceSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);

			//�g�p������������ė���
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//����������
			m_isInitd = true;
		}

		void BaseEndurance::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�_���[�W��K�p����
			ApplyDamage();
			
			//�Q�[���V�[���̃X�e�[�g���Q�[���N���A�ł��Q�[���I�[�o�[�ł��Ȃ��ꍇ�c
			if (m_gameScene->GetGameSceneState() != enGameSceneClear && m_gameScene->GetGameSceneState() != enGameSceneOver) {
				//�ϋv�l�̉摜�̏����X�V����
				m_enduranceSprite->SetScale(m_enduranceSpriteScale);
				m_enduranceSprite->SetColor(m_enduranceSpriteColor);
			}

			//�摜�̏��������s
			m_enduranceBaseFrame->Execute();
			m_enduranceBaseSprite->Execute();
			m_enduranceUnderSprite->Execute();
			m_enduranceSprite->Execute();
		}

		void BaseEndurance::ApplyDamage()
		{
			//�h�q�Ώۂ̌��ݑϋv�͂��ő�ϋv�͂ŏ��Z����1�`0�̊Ԃ̗̑͂̊������擾����
			float hpRatio = m_defensiveTarget->GetDefensiveTargetHp() / m_defensiveTarget->GetDefensiveTargetMaxHp();

			//�摜�̉������̊g�嗦�ɖh�q�Ώۂ̑ϋv�͂̊�����ݒ肷��
			m_enduranceSpriteScale.x = hpRatio;

			//�ϋv�͂̊����Ŏc��ϋv�͂̃J���[���ő�l�̃J���[�ƍŏ��l�̃J���[����`�⊮�����l�ɂ���
			m_enduranceSpriteColor.Lerp(hpRatio,
				ENDURANCE_SPRITE_MAX_COLOR,
				ENDURANCE_SPRITE_MIN_COLOR);
		}

		void BaseEndurance::HIdeUI()
		{
			//�\�����Ă���UI�𓧖��ɂ���
			m_enduranceBaseSprite->SetColor(render::COLORLESS);
			m_enduranceBaseFrame->SetColor(render::COLORLESS);
			m_enduranceSprite->SetColor(render::COLORLESS);
			m_enduranceUnderSprite->SetColor(render::COLORLESS);
		}
	}
}