#include "stdafx.h"
#include "SceneTransition.h"

namespace mainGame{
	SceneTransition::SceneTransition()
	{

	}

	SceneTransition::~SceneTransition()
	{

	}

	void SceneTransition::Init()
	{
		//�g�p��������擾
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		//�ϐ���������
		m_opacity = 0.0f;
		//����������
		m_isInitd = true;
	}

	void SceneTransition::Execution()
	{
		//���������Ȃ���s���Ȃ�
		if (m_isInitd == false) {
			return;
		}

		//�t�F�[�h�C����
		if (m_feadIn == true) {
			//�s�����x���グ��
			m_opacity += g_gameTime->GetFrameDeltaTime() * m_feadRate;
			//�s�����x���ő�ɒB������c
			if (m_opacity >= 1.0f) {
				//�t�F�[�h�C�����I������
				m_opacity = 1.0f;
				m_feadIn = false;
			}
		}
		//�t�F�[�h�A�E�g��
		if (m_feadOut == true) {
			//�s�����x��������
			m_opacity -= g_gameTime->GetFrameDeltaTime() * m_feadRate;
			//�s�����x���ŏ��ɒB������c
			if (m_opacity <= 0.0f) {
				//�t�F�[�h�A�E�g���I������
				m_opacity = 0.0f;
				m_feadOut = false;
			}
		}

		//�V�[���̃J���[�ɕs�����x��ݒ肷��
		m_sceneColor.x = m_opacity;
		m_sceneColor.y = m_opacity;
		m_sceneColor.z = m_opacity;

		//�s�����x���V�[���̃X�v���C�g�ɐݒ�
		m_renderingEngine->SetFinalSpriteColor(m_sceneColor);
	}
}