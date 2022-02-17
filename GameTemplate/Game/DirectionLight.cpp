#include "stdafx.h"
#include "DirectionLight.h"

namespace render {
	namespace light {

		const Vector3 START_COLOR = { 0.5f,0.5f,0.5f };

		const Vector3 START_DIRECTION = { 1.0f,0.0f,0.0f };

		DirectionLight::DirectionLight()
		{

		}

		DirectionLight::~DirectionLight()
		{

		}

		void DirectionLight::Init()
		{
			//���C�g��������
			m_directionLight.color = START_COLOR;
			m_directionLight.direction = START_DIRECTION;

			m_isInitd = true;
		}

		void DirectionLight::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			Rotation();
		}

		void DirectionLight::SetVirtualPosition(const Vector3& pos)
		{
			//�ݒ肳�ꂽ���z�ʒu������������߂�
			m_virtualPosition = pos;

			m_directionLight.direction = m_virtualTarget - m_virtualPosition;

			m_directionLight.direction.Normalize();
		}

		void DirectionLight::SetVirtualTarget(const Vector3& target)
		{
			//�ݒ肳�ꂽ���z�ڕW������������߂�
			m_virtualTarget = target;

			m_directionLight.direction = m_virtualTarget - m_virtualPosition;

			m_directionLight.direction.Normalize();
		}

		void DirectionLight::SetRotation(const Vector3& axis, const float angle)
		{
			//��]���Ɗp�x��ݒ肵��]���n�߂�
			m_rotationAxis = axis;
			m_rotationAngle = angle;
			m_rotationFlag = true;
		}

		void DirectionLight::LightOFF()
		{
			m_directionLight.color = g_vec3Zero;
			m_directionLight.direction = g_vec3Zero;
		}

		void DirectionLight::Rotation()
		{
			//��]�t���O�������Ă��Ȃ�������c
			if (m_rotationFlag == false) {
				//���s�����I��������
				return;
			}
			
			Quaternion qRot = Quaternion::Identity;
			//��]���Ɖ�]�p�x�����]���쐬
			qRot.SetRotation(m_rotationAxis, m_rotationAngle);
			//���C�g�̕����ɉ�]��K�p����
			qRot.Apply(m_directionLight.direction);
		}
	}
}