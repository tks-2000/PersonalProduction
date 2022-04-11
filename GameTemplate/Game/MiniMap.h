#pragma once

class RenderingEngine;

namespace mainGame {

	namespace player {
		class Player;
	}

	class GameCamera;

	namespace ui {
		/// @brief �~�j�}�b�v�摜��\������N���X
		class MiniMap
		{
		public:
			MiniMap();
			~MiniMap();

			/// @brief	������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief �}�b�v�J�����̏������ݒ�
			/// @param up 
			void SetMapCameraUp(const Vector3& up) { m_mapCameraUp = up; }
			/// @brief UI���\��
			void HideUI();
		
		private:

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �}�b�v�J�����̍��W
			Vector3 m_mapCameraPos = g_vec3Zero;
			/// @brief �}�b�v�J�����̏����
			Vector3 m_mapCameraUp = { 0.0f,0.0f,1.0f };
			/// @brief �}�b�v��`�悷�郌���_�����O�^�[�Q�b�g
			RenderTarget m_miniMapRenderTarget;
			/// @brief �}�b�v��\�����邽�߂̃J����
			Camera m_miniMapCamera;
			/// @brief �}�b�v�摜
			render::sprite::SpriteRender* m_miniMapSprite = nullptr;
			/// @brief �}�b�v�̉��n�摜
			render::sprite::SpriteRender* m_miniMapBase = nullptr;
			/// @brief �}�b�v�̘g�摜
			render::sprite::SpriteRender* m_miniMapFrame = nullptr;
			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
			/// @brief �����_�����O�G���W��
			render::RenderingEngine* m_renderingEngine = nullptr;
			/// @brief �v���C���[
			player::Player* m_player = nullptr;
		};
	}
}