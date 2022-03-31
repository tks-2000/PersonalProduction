#pragma once

namespace mainGame {
	/// @brief �V�[���̑J�ڂ��s���N���X
	class SceneTransition : public IGameObject
	{
	public:
		SceneTransition();
		~SceneTransition();

		/// @brief ������
		void Init();

		/// @brief ���s
		void Execution();

		/// @brief �t�F�[�h�A�E�g���n�߂�
		/// @param rate �t�F�[�h�A�E�g�̑��x
		void SetFeadOut(const float rate) { m_feadIn = false; m_feadOut = true; m_feadRate = rate; }

		/// @brief �t�F�[�h�C�����n�߂�
		/// @param rate �t�F�[�h�C���̑��x
		void SetFeadIn(const float rate) { m_feadIn = true; m_feadOut = false; m_feadRate = rate; }

		/// @brief �t�F�[�h�A�E�g���Ă���Œ����H
		/// @return true�ł��Ă��� false�ł��Ă��Ȃ�
		const bool IsFeadOut() const { return m_feadOut; }

		/// @brief �t�F�[�h�C�����Ă���Œ����H
		/// @return true�ł��Ă��� false�ł��Ă��Ȃ�
		const bool IsFeadIn() const { return m_feadIn; }

	private:
		/// @brief �������t���O
		bool m_isInitd = false;
		/// @brief �t�F�[�h�A�E�g�t���O
		bool m_feadOut = false;
		/// @brief �t�F�[�h�C���t���O
		bool m_feadIn = false;
		/// @brief �t�F�[�h�̐i�s���x
		float m_feadRate = 0.0f;
		/// @brief �����_�����O�G���W��
		render::RenderingEngine* m_renderingEngine = nullptr;
		/// @brief �s�����x
		float m_opacity = 1.0f;
		/// @brief �V�[���̃J���[
		Vector4 m_sceneColor = g_vec4White;
	};

}