#include "stdafx.h"
#include "RenderingEngine.h"

namespace Render {
	RenderingEngine::RenderingEngine()
	{
		m_lig = NewGO<Lighting>(0, LIGHTING_NAME);
		m_shadow = NewGO<Shadow>(0, SHADOW_NAME);
	}

	RenderingEngine::~RenderingEngine()
	{
		DeleteGO(m_lig);
		DeleteGO(m_shadow);
	}

	bool RenderingEngine::Start()
	{
		m_lig->SetHemiSphereLifhtGroundColor({ 0.3f,0.0f,0.0f });
		m_lig->SetHemiSphereLifhtSkyColor({ 0.0f,0.0f,0.3f });
		m_lig->SetPointLightColor(0, { 0.0f,1.0f,0.0f });
		m_lig->SetPointLightRange(0, 300.0f);
		m_lig->SetSpotLightColor(0, { 1.0f,1.0f,1.0f });
		

		return true;
	}

	void RenderingEngine::Update()
	{

	}
}