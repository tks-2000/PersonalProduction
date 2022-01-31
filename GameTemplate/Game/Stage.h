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
			/// @brief 
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

			render::model::SkinModelRender* m_bgModel = nullptr;

			render::model::SkinModelRender* m_miniMapModel = nullptr;

			int m_stageSoundID = 0;

			sound::SoundPlayer* m_soundPlayer = nullptr;

			GameScene* m_gameScene = nullptr;
		};
	}
}
