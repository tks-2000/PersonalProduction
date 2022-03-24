#pragma once

class RenderingEngine;

namespace mainGame {

	namespace player {
		class Player;
	}

	class GameCamera;

	namespace ui {
		class MiniMap
		{
		public:
			MiniMap();
			~MiniMap();

			/// @brief	������
			void Init();
			/// @brief ���s
			void Execution();

			/// @brief �}�b�v�ɕ\�����郂�f����ǉ�
			/// @param model �}�b�v�ɕ\�����郂�f���̃A�h���X
			void SetDrawModel(Model* model);

			/// @brief �}�b�v�ɕ\�����Ă��郂�f�����폜
			/// @param model �폜���郂�f���̃A�h���X
			void DeleteDrawModel(Model* model);

			/// @brief �}�b�v�Ƀ��f������������
			/// @param rc �����_�����O�R���e�L�X�g
			void MapRender(RenderContext& rc);

			void SetMapCameraUp(const Vector3& up) { m_mapCameraUp = up; }

			void HideUI();
		
		private:

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �~�j�}�b�v�̕\�����W
			Vector3 m_miniMapPos = g_vec3Zero;
			/// @brief �}�b�v�J�����̍��W
			Vector3 m_mapCameraPos = g_vec3Zero;
			/// @brief �}�b�v�J�����̏����
			Vector3 m_mapCameraUp = { 0.0f,0.0f,1.0f };
			/// @brief �}�b�v�摜�̉�]
			float m_spriteAngle = 0.0f;

			/// @brief �}�b�v��`�悷�郌���_�����O�^�[�Q�b�g
			RenderTarget m_miniMapRenderTarget;
			/// @brief �}�b�v��\�����邽�߂̃J����
			Camera m_miniMapCamera;
			/// @brief �}�b�v�ɕ\�����郂�f���̔z��
			std::vector<Model*> m_drawModels;
			/// @brief �}�b�v�摜
			render::sprite::SpriteRender* m_miniMapSprite = nullptr;
			render::sprite::SpriteRender* m_miniMapBase = nullptr;
			render::sprite::SpriteRender* m_miniMapFrame = nullptr;
			/// @brief �}�b�v�摜�̉�]
			Quaternion m_spriteQrot = g_quatIdentity;
			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
			/// @brief �����_�����O�G���W��
			render::RenderingEngine* m_renderingEngine = nullptr;

			player::Player* m_player = nullptr;
		};
	}
}