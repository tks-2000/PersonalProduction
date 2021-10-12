#pragma once



namespace render {
	class RenderingEngine;
	namespace font {

		struct FontData
		{
			/// @brief �t�H���g
			Font font;
			/// @brief �e�L�X�g
			std::wstring text;
			/// @brief �t�H���g�̍��W
			Vector2 pos = g_vec2Zero;
			/// @brief �t�H���g�̃J���[
			Vector4 color = g_vec4White;
			/// @brief �t�H���g�̉�]
			float rotation = 0.0f;
			/// @brief �t�H���g�̊g�嗦
			float scale = 1.0f;
			/// @brief �t�H���g�̒��S
			Vector2 pivot = { 0.5f,0.5f };
		};

		class FontRender : public IGameObject
		{
		public:
			FontRender();
			~FontRender();
			bool Start();
			void Update();

			/// @brief ���s
			void Execution();

			/// @brief ������
			/// @param text �\������e�L�X�g
			void Init(const wchar_t* text);

			/// @brief �\������e�L�X�g��ݒ�
			/// @param text �\��������������
			void SetText(const wchar_t* text);
			/// @brief �t�H���g��\��������W��ݒ�
			/// @param pos �t�H���g�ɐݒ肷����W
			void SetPosition(const Vector2& pos) { m_fontData.pos = pos; }
			/// @brief �t�H���g�̉�]��ݒ�
			/// @param rotation �t�H���g�ɐݒ肷���]�p�x
			void SetRotation(const float rotation) { m_fontData.rotation = rotation; }
			/// @brief �t�H���g�̊g�嗦��ݒ�
			/// @param scale �t�H���g�ɐݒ肷��g��{��
			void SetScale(const float scale) { m_fontData.scale = scale; }
			/// @brief �t�H���g�̃J���[��ݒ�
			/// @param color �t�H���g�ɐݒ肷��J���[
			void SetColor(const Vector4& color) { m_fontData.color = color; }
			/// @brief �t�H���g�̒��S��ݒ�
			/// @param pivot �t�H���g�ɐݒ肷�钆�S�ʒu
			void SetPivot(const Vector2& pivot) { m_fontData.pivot = pivot; }
			/// @brief �t�F�[�h�̏���
			void Fade();
			/// @brief �t�H���g�̃t�F�[�h�C�����J�n
			/// @param rate �t�F�[�h�̃��[�g
			void FadeIn(float rate) { m_fadeInFlag = true; m_fadeOutFlag = false; m_fadeRate = rate; }
			/// @brief �t�H���g�̃t�F�[�h�A�E�g���J�n
			/// @param rate �t�F�[�h�̃��[�g
			void FadeOut(float rate) { m_fadeOutFlag = true; m_fadeInFlag = false; m_fadeRate = rate; }
			/// @brief �t�H���g�̕s�����x�����
			/// @return �J���[�̃A���t�@�l
			float GetOpacity() { return m_color.w; }
			/// @brief �t�H���g���s������?
			/// @return �s�����Ȃ�true �������������Ȃ�false
			bool IsOpacity();
			/// @brief �t�H���g���������H
			/// @return �����Ȃ�true �s�������������Ȃ�false
			bool IsTransparent();
			/// @brief �t�H���g���ړ�������
			/// @param targetPos �ړ������������W
			/// @param velocity �ړ����鑬�x
			void MoveStart(const Vector2& targetPos, float velocity);

			void Render(RenderContext& rc);

		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �t�H���g
			Font m_font;
			/// @brief �e�L�X�g
			std::wstring m_text;
			const wchar_t* m_texUnsafe = nullptr;
			/// @brief �t�H���g�̍��W
			Vector2 m_position = Vector2::Zero;
			/// @brief �t�H���g�̃J���[
			Vector4 m_color = Vector4::White;
			/// @brief �t�H���g�̉�]
			float m_rotation = 0.0f;
			/// @brief �t�H���g�̊g�嗦
			float m_scale = 1.0f;
			/// @brief �t�H���g�̒��S
			Vector2 m_pivot = { 1.0f,1.0f };

			/// @brief �ړ�����ڕW�̍��W
			Vector2 m_targetPos = Vector2::Zero;
			/// @brief �ړ����x
			Vector2 m_moveSpeed = Vector2::Zero;
			/// @brief �ړ�����������O�̍��W
			Vector2 m_previousPos = Vector2::Zero;
			/// @brief �t�F�[�h�C���t���O
			bool m_fadeInFlag = false;
			/// @brief �t�F�[�h�A�E�g�t���O
			bool m_fadeOutFlag = false;
			/// @brief �t�F�[�h��
			float m_fadeRate = 0.0f;

			/// @brief �ړ��t���O
			bool m_moveFlag = false;

			/// @brief �����_�����O�G���W��
			RenderingEngine* m_renderingEngine = nullptr;

			FontData m_fontData;

			void Move();
		};
	}
}