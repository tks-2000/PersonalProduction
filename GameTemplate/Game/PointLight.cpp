#include "stdafx.h"
#include "PointLight.h"

namespace render {
	namespace light {

		const Vector3 START_POSITION = { 0.0f,100.0f,0.0f };

		const Vector3 START_COLOR = { 0.0f,1.5f,0.0f };

		const float START_RANGE = 1000.0f;


		PointLight::PointLight()
		{

		}

		PointLight::~PointLight()
		{

		}

		void PointLight::Init()
		{
			m_pointLight.position = START_POSITION;
			m_pointLight.color = START_COLOR;
			m_pointLight.range = START_RANGE;

			m_isInitd = true;
		}

		void PointLight::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

		}

		void PointLight::LightOFF()
		{
			m_pointLight.position = g_vec3Zero;
			m_pointLight.color = g_vec3Zero;
			m_pointLight.range = 0.0f;
		}
	}
}