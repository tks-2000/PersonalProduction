#include "stdafx.h"
#include "ItemEffect.h"

namespace mainGame {
	namespace item {
		/// @brief �o���G�t�F�N�g�̃t�@�C���p�X
		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/boxopen.efk";
		/// @brief �o���G�t�F�N�g�̊g�嗦
		const Vector3 SPAWN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief ����G�t�F�N�g�̃t�@�C���p�X
		const char16_t* GET_EFFECT_FILEPATH = u"Assets/effect/itemaura.efk";
		/// @brief ����G�t�F�N�g�̊J�n���̊g�嗦
		const Vector3 GET_EFFECT_START_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief ����G�t�F�N�g�̊g�嗦�ቺ��
		const Vector3 GET_EFFECT_DOWN_SCALE_RATE = { 0.1f,0.1f,0.1f };



		EffectGenerator::EffectGenerator()
		{

		}

		EffectGenerator::~EffectGenerator()
		{
			//�쐬�����G�t�F�N�g���폜
			DeleteGO(m_spawnEffect);
			DeleteGO(m_getEffect);
		}

		void EffectGenerator::Init(Item* item)
		{
			//�o��������G�t�F�N�g��������
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_spawnEffect->Init(SPAWN_EFFECT_FILEPATH);
			m_spawnEffect->SetScale(SPAWN_EFFECT_SCALE);

			m_getEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_getEffect->Init(GET_EFFECT_FILEPATH);
			m_getEffectScale = GET_EFFECT_START_SCALE;

			//�g�p��������擾
			m_item = item;

			//����������
			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�G�t�F�N�g�̏��������s
			PlaySpawnEffect();
			PlayGetEffect();

		}

		void EffectGenerator::PlaySpawnEffect()
		{
			//�A�C�e�����o�����Ă��āA�o���G�t�F�N�g�Đ��t���O�������Ă��Ȃ��ꍇ�c
			if (m_item->IsSpawn() == true && m_isSpawnEffectPlay == false) {
				//�o���G�t�F�N�g���Đ�
				m_spawnEffect->SetPosition(m_item->GetPosition());
				m_spawnEffect->Play(false);
				m_isSpawnEffectPlay = true;
			}

			//�o���G�t�F�N�g�̏��������s
			m_spawnEffect->Execution();
		}

		void EffectGenerator::PlayGetEffect()
		{
			//�A�C�e�����v���C���[�ɓ��肳��Ă��āA����G�t�F�N�g�Đ��t���O�������Ă��Ȃ��ꍇ�c
			if (m_item->IsPlayerGet() == true && m_isGetEffectPlay == false) {
				//����G�t�F�N�g���Đ�
				m_getEffect->SetPosition(m_item->GetPosition());
				m_getEffect->Play(false);
				m_isGetEffectPlay = true;
			}

			//����G�t�F�N�g�̍Đ��t���O�������Ă���ꍇ
			if (m_isGetEffectPlay == true) {
				//����G�t�F�N�g�̊g�嗦��������
				m_getEffectScale -= GET_EFFECT_DOWN_SCALE_RATE;
			}

			//����G�t�F�N�g�̏��������s
			m_getEffect->SetScale(m_getEffectScale);
			m_getEffect->Execution();
		}
	}
}