#pragma once

namespace render {
	namespace light {
		/// @brief �|�C���g���C�g�\����
		struct StPointLight
		{
			Vector3 position = Vector3::Zero;	//�ʒu
			float pad0 = 0.0f;					//�p�f�B���O
			Vector3 color = Vector3::Zero;		//�J���[
			float range = 0.0f;					//�e���͈�
		};

		/// @brief �|�C���g���C�g�̋@�\���܂Ƃ߂��N���X
		class PointLight
		{
		public:
			PointLight();
			~PointLight();
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief ���W��ݒ�
			/// @param pos �ݒ肷����W
			void SetPosition(const Vector3 pos) { m_pointLight.position = pos; }
			/// @brief �J���[��ݒ�
			/// @param color �ݒ肷��J���[
			void SetColor(const Vector3& color) { m_pointLight.color = color; }
			/// @brief �e���͈͂�ݒ�
			/// @param range �ݒ肷��e���͈�
			void SetRange(const float range) { m_pointLight.range = range; }
			/// @brief ���C�g������
			void LightOFF();
			/// @brief �|�C���g���C�g�����
			/// @return �|�C���g���C�g�\���̂�const�Q��
			const StPointLight& GetPointLight() const { return m_pointLight; }
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �|�C���g���C�g
			StPointLight m_pointLight;
		};
	}
}
