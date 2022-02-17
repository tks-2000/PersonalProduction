#pragma once

namespace render {
	namespace light {
		/// @brief �f�B���N�V�������C�g�\����
		struct StDirectionLight
		{
			Vector3 direction = Vector3::Zero;	//���C�g�̕���
			float pad0 = 0.0f;					//�p�f�B���O
			Vector3 color = Vector3::Zero;		//���C�g�̃J���[
			float pad1 = 0.0f;					//�p�f�B���O

		};

		/// @brief �f�B���N�V�������C�g���Ǘ�����N���X
		class DirectionLight
		{
		public:
			DirectionLight();
			~DirectionLight();
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief ���z�I�Ȉʒu��ݒ�
			/// @param pos �����̈ʒu
			void SetVirtualPosition(const Vector3& pos);
			/// @brief ���z�I�̖ڕW��ݒ�
			/// @param target �ڕW�̈ʒu
			void SetVirtualTarget(const Vector3& target);
			/// @brief ������ݒ�
			/// @param direction �ݒ肵���������E���K���x�N�g����ݒ肵�ĉ�����
			void SetDirection(const Vector3& direction) { m_directionLight.direction = direction; }
			/// @brief �J���[��ݒ�
			/// @param color �ݒ肵�����F
			void SetColor(const Vector3& color) { m_directionLight.color = color; }
			/// @brief ��]��ݒ�
			/// @param Axis ��]��
			/// @param angle ��]�p�x
			void SetRotation(const Vector3& axis, const float angle);
			/// @brief ��]���~
			void StopRotation() { m_rotationFlag = false; }
			/// @brief ���C�g������
			void LightOFF();
			/// @brief �f�B���N�V�������C�g���擾
			/// @return �f�B���N�V�������C�g�\���̂�const�Q��
			const StDirectionLight& GetDirectionLight() const { return m_directionLight; }
			
		private:

			void Rotation();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �f�B���N�V�������C�g
			StDirectionLight m_directionLight;
			/// @brief ���z�I�Ȉʒu�E�����݂̂̃��C�g�Ȃ̂Ōv�Z���ĕ��������߂�
			Vector3 m_virtualPosition = g_vec3Zero;
			/// @brief ���z�I�ȖڕW�E�����݂̂̃��C�g�Ȃ̂Ōv�Z���ĕ��������߂�
			Vector3 m_virtualTarget = g_vec3Zero;
			/// @brief ��]�t���O
			bool m_rotationFlag = false;
			/// @brief ��]��
			Vector3 m_rotationAxis = g_vec3Zero;
			/// @brief ��]�p�x
			float m_rotationAngle = 0.0f;
		};
	}
}
