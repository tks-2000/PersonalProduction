#pragma once

namespace render {
	namespace light {
		/// @brief �X�|�b�g���C�g�\����
		struct StSpotLight
		{
			Vector3 position = Vector3::Zero;	//�ʒu
			float pad0 = 0.0f;					//�p�f�B���O
			Vector3 color = Vector3::Zero;		//�J���[
			float range = 0.0f;					//�e���͈�
			Vector3 direction = Vector3::Zero;	//�ˏo����
			float angle = 0.0f;					//�ˏo�p�x

		};

		/// @brief �X�|�b�g���C�g�̋@�\���܂Ƃ߂��N���X
		class SpotLight
		{
		public:
			SpotLight();
			~SpotLight();
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief ���W��ݒ�
			/// @param pos �ݒ肷����W
			void SetPosition(const Vector3& pos) { m_spotLight.position = pos; }
			/// @brief �Ƃ炷�ڕW��ݒ�
			/// @param target �Ƃ炷�ڕW�̍��W 
			void SetTarget(const Vector3& target) { m_spotLight.direction = target - m_spotLight.position; m_spotLight.direction.Normalize(); }
			/// @brief �J���[��ݒ�
			/// @param color �ݒ肷��J���[
			void SetColor(const Vector3& color) { m_spotLight.color = color; }
			/// @brief �e���͈͂�ݒ�
			/// @param range �ݒ肷��e���͈�
			void SetRange(const float range) { m_spotLight.range = range; }
			/// @brief �ˏo������ݒ�
			/// @param dir �ݒ肷��ˏo�����E���K���x�N�g����n���ĉ�����
			void SetDirection(const Vector3& direction) { m_spotLight.direction = direction; }
			/// @brief �ˏo�p�x��ݒ�
			/// @param angle �ݒ肷��ˏo�p�x
			void SetAngle(const float angle) { m_spotLight.angle = angle; }
			/// @brief ���C�g������
			void LightOFF();
			/// @brief �X�|�b�g���C�g�����
			/// @return �X�|�b�g���C�g�\���̂�const�Q��
			const StSpotLight& GetSpotLight() const { return m_spotLight; }
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �X�|�b�g���C�g
			StSpotLight m_spotLight;
		};
	}
}


