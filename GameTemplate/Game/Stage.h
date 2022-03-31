#pragma once

class SkinModelRender;

namespace mainGame {
	namespace stage {
		/// @brief �X�e�[�W�̏����܂Ƃ߂��N���X
		class Stage : public IGameObject
		{
		public:
			Stage();
			~Stage();
			/// @brief	������
			void Init();
			/// @brief ���s
			void Execution();
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ��]
			Quaternion m_qRot = g_quatIdentity;
			/// @brief �g�嗦
			Vector3 m_scale = g_vec3One;
			/// @brief �X�e�[�W���f��
			render::model::SkinModelRender* m_stageModel = nullptr;
			/// @brief �ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_staticStageObject;
			/// @brief �w�i���f��
			render::model::SkinModelRender* m_bgModel = nullptr;
			/// @brief �~�j�}�b�v���f��
			render::model::SkinModelRender* m_miniMapModel = nullptr;
			/// @brief �X�e�[�W�̃T�E���hID
			int m_stageSoundID = 0;
			/// @brief �T�E���h�v���C���[
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief �Q�[���V�[��
			GameScene* m_gameScene = nullptr;
		};
	}
}
