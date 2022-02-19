#include "stdafx.h"
#include "PointLight.h"

namespace render {
	namespace light {

		const Vector3 START_POSITION = { 0.0f,100.0f,0.0f };

		const Vector3 START_COLOR = { 1.0f,1.0f,1.0f };

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

			Blinking();
			Gradation();
			
		}

		void PointLight::SetBlinking(const float interval)
		{
			//�_�łɕK�v�ȏ���ݒ�
			m_blinkingInterval = interval;
		}

		void PointLight::StartBlinking()
		{
			m_blinkingTimer = 0.0f;

			m_blinkingColor = g_vec3Zero;

			m_saveColor = m_pointLight.color;

			m_blinkingFlag = true;
		}

		void PointLight::StopBlinking()
		{
			if (m_blinkingFlag == false) {
				return;
			}

			m_pointLight.color = m_saveColor;

			m_blinkingFlag = false;
		}

		void PointLight::SetGradation(std::vector<Vector3>& colors, const float speed)
		{
			//�O���f�B�G�[�V�����̂��߂ɕK�v�ȏ���ݒ�
			m_gradationColors = colors;

			m_gradationSpeed = speed;

			m_gradationTimer = 0.0f;

			m_gradationNum = 0;

		}

		void PointLight::StartGradation()
		{
			m_gradationFlag = true;
		}

		void PointLight::StopGradation()
		{
			if (m_gradationFlag == false) {
				return;
			}

			m_gradationFlag = false;
		}

		void PointLight::LightOFF()
		{
			m_pointLight.position = g_vec3Zero;
			m_pointLight.color = g_vec3Zero;
			m_pointLight.range = 0.0f;
		}

		void PointLight::Blinking()
		{
			if (m_blinkingFlag == false) {
				return;
			}
			
			//�^�C�}�[��i�߂�
			m_blinkingTimer += g_gameTime->GetFrameDeltaTime();

			//�^�C�}�[���_�Ŏ��ԂɒB������
			if (m_blinkingTimer > m_blinkingInterval) {

				//���݂̃J���[�Ɠ_�ŗp�̃J���[�����ւ���
				Vector3 color = m_pointLight.color;
				m_pointLight.color = m_blinkingColor;
				m_blinkingColor = color;

				//�^�C�}�[��0�ɖ߂�
				m_blinkingTimer = 0.0f;
			}

		}

		void PointLight::Gradation()
		{
			if (m_gradationFlag == false) {
				return;
			}

			//�^�C�}�[�𑬓x�ɉ����Đi�߂�
			m_gradationTimer += g_gameTime->GetFrameDeltaTime() * m_gradationSpeed;
			//�⊮�p�̎��̃J���[�z��ɃA�N�Z�X����ԍ���p��
			int colorNum = m_gradationNum + 1;
			//�ԍ����z��̗v�f���Ɠ����ɂȂ��Ă�����c
			if (colorNum == m_gradationColors.size()) {
				//���݂̗v�f���z��̍Ō���Ȃ̂Ő擪�̔ԍ������̃J���[�z��̔ԍ��Ƃ���
				colorNum = 0;
			}
			//�^�C�}�[�̒l�Ɨv�f�ԍ����g���ăO���f�B�G�[�V�����p�̃J���[�z�����`�⊮����
			m_pointLight.color.Lerp(m_gradationTimer, m_gradationColors[m_gradationNum], m_gradationColors[colorNum]);

			//�^�C�}�[��1.0�𒴂�����c
			if (m_gradationTimer > 1.0f) {
				//�J���[�z��ɃA�N�Z�X����ԍ������Z
				m_gradationNum++;
				//�^�C�}�[�����ɖ߂�
				m_gradationTimer = 0.0f;
				//�J���[�z��ɃA�N�Z�X����ԍ����z��̗v�f���Ɠ����ɂȂ��Ă�����c
				if (m_gradationNum == m_gradationColors.size()) {
					//�擪�̔ԍ��ɖ߂�
					m_gradationNum = 0;
				}
			}
		}
	}
}