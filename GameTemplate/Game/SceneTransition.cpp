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
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		m_opacity = 0.0f;
		m_isInitd = true;
	}

	void SceneTransition::Execution()
	{
		if (m_isInitd == false) {
			return;
		}

		if (m_feadIn == true) {
			m_opacity += g_gameTime->GetFrameDeltaTime() * m_feadRate;
			if (m_opacity >= 1.0f) {
				m_opacity = 1.0f;
				m_feadIn = false;
			}
		}
		if (m_feadOut == true) {
			m_opacity -= g_gameTime->GetFrameDeltaTime() * m_feadRate;

			if (m_opacity <= 0.0f) {
				m_opacity = 0.0f;
				m_feadOut = false;
			}
		}

		m_sceneColor.x = m_opacity;
		m_sceneColor.y = m_opacity;
		m_sceneColor.z = m_opacity;


		m_renderingEngine->SetFinalSpriteColor(m_sceneColor);
	}
}