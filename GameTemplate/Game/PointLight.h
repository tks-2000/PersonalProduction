#pragma once

namespace render {
	namespace light {

		const int GRADATION_COLOR_NUM = 7;

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
			void SetPosition(const Vector3& pos) { m_pointLight.position = pos; }
			/// @brief �J���[��ݒ�
			/// @param color �ݒ肷��J���[
			void SetColor(const Vector3& color) { m_pointLight.color = color; }
			/// @brief �e���͈͂�ݒ�
			/// @param range �ݒ肷��e���͈�
			void SetRange(const float range) { m_pointLight.range = range; }
			/// @brief �_�ł�ݒ�
			/// @param interval �_�ł̊Ԋu
			void SetBlinking(const float interval);
			/// @brief �_�ł��J�n
			void StartBlinking();
			/// @brief �_�ł��~
			void StopBlinking();
			/// @brief �O���f�B�G�[�V������ݒ�
			/// @param colors �O���f�B�G�[�V����������F��vector�^�z��
			/// @param speed �O���f�B�G�[�V���������鑬�x
			void SetGradation(std::vector<Vector3>& colors, const float speed);
			/// @brief �O���f�B�G�[�V�������J�n
			void StartGradation();
			/// @brief �O���f�B�G�[�V�������~
			void StopGradation();
			/// @brief ���C�g������
			void LightOFF();
			/// @brief �|�C���g���C�g�����
			/// @return �|�C���g���C�g�\���̂�const�Q��
			const StPointLight& GetPointLight() const { return m_pointLight; }
		private:
			/// @brief �_�ł̏������s��
			void Blinking();
			/// @brief �O���f�B�G�[�V�����̏������s��
			void Gradation();
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �_�Ńt���O
			bool m_blinkingFlag = false;
			/// @brief �_�ł��邽�߂̎��Ԃ��v��^�C�}�[
			float m_blinkingTimer = 0.0f;
			/// @brief �_�ŊԊu
			float m_blinkingInterval = 0.0f;
			/// @brief �_�ł���F
			Vector3 m_blinkingColor = g_vec3Zero;
			/// @brief �_�ł���O�̐F
			Vector3 m_saveColor = g_vec3Zero;
			/// @brief �O���f�B�G�[�V�����t���O
			float m_gradationFlag = false;
			/// @brief �O���f�B�G�[�V����������F�̔z��
			std::vector<Vector3> m_gradationColors;
			/// @brief �O���f�B�G�[�V�������鑬�x
			float m_gradationSpeed = 0.0f;
			/// @brief �O���f�B�G�[�V���������邽�߂̎��Ԃ��v��^�C�}�[
			float m_gradationTimer = 0.0f;
			/// @brief �O���f�B�G�[�V�����p�̔z��ɃA�N�Z�X���邽�߂̔ԍ�
			int m_gradationNum = 0;

			/// @brief �|�C���g���C�g
			StPointLight m_pointLight;
		};
	}
}
