#include "stdafx.h"
#include "BaseEndurance.h"

namespace mainGame {
	namespace ui {

		/// @brief �ϋv�l�̉��n�摜�̉���
		const int ENDURANCE_BASE_SPRITE_WIDTH = 1100;
		/// @brief �ϋv�l�̉��n�摜�̏c��
		const int ENDURANCE_BASE_SPRITE_HEIGHT = 700;
		/// @brief �ϋv�l�̉��n�摜�̍��W
		const Vector3 ENDURANCE_BASE_SPRITE_POS = { 0.0f,300.0f,0.0f };

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
			
			m_enduranceBaseSprite->Init("Assets/Image/base_sprite_5.dds", ENDURANCE_BASE_SPRITE_WIDTH, ENDURANCE_BASE_SPRITE_HEIGHT);
			m_enduranceBaseFrame->Init("Assets/Image/base_sprite_6.dds", ENDURANCE_BASE_SPRITE_WIDTH, ENDURANCE_BASE_SPRITE_HEIGHT);
			m_enduranceBaseSprite->SetColor({ 1.0f,1.0f,1.0f,0.5f });
			m_enduranceUnderSprite->Init("Assets/Image/WB.dds", ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);
			
			m_enduranceSprite->Init("Assets/Image/WB.dds", ENDURANCE_SPRITE_WIDTH,ENDURANCE_SPRITE_HEIGHT);
			

			//�摜�̏����p�����[�^�[������
			//m_enduranceBaseSprite->SetColor(g_vec4Black);
			m_enduranceUnderSprite->SetColor(ENDURANCE_UNDER_SPRITE_COLOR);
			m_enduranceSpritePos = ENDURANCE_SPRITE_POS;
			m_enduranceSpriteColor = ENDURANCE_SPRITE_MIN_COLOR;
			m_enduranceBaseFrame->SetPosition(ENDURANCE_BASE_SPRITE_POS);
			m_enduranceBaseSprite->SetPosition(ENDURANCE_BASE_SPRITE_POS);
			m_enduranceUnderSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceUnderSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);
			m_enduranceSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);

			//�h�q�Ώۂ̏��������ė���
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			//����������
			m_isInitd = true;
		}

		void BaseEndurance::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			//�_���[�W��K�p����
			ApplyDamage();
			
			//�摜�̏����X�V����
			m_enduranceSprite->SetScale(m_enduranceSpriteScale);
			m_enduranceSprite->SetColor(m_enduranceSpriteColor);

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
	}
}