#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"

class SkinModelRender;


namespace mainGame {
	namespace player {
		
		/// @brief �v���C���[�̏�Ԃ����߂�񋓌^
		enum EnPlayerStates {
			enPlayerIdle,
			enPlayerWark,
			enPlayerRun,
			enPlayerDamage,
			enPlayerStateNum
		};

		class Player : public IGameObject
		{
		public:
			Player();
			~Player();
			bool Start();
			void Update();

			void SetPlayerState(const EnPlayerStates& plState) { m_playerState = plState; }

			/// @brief �v���C���[�̏�Ԃ����
			/// @return �v���C���[�̃X�e�[�^�X
			const EnPlayerStates& GetPlayerStatus() { return m_playerState; }

			/// @brief �v���C���[�̍��W�����
			/// @return �v���C���[�̍��W��const�Q��
			const Vector3& GetPlayerPosition() { return m_position; }

			/// @brief �v���C���[�̉�]�p�x�̕ω��ʂ����
			/// @return �v���C���[�̉�]�p�x�̕ω���
			float GetAngleAmount() { return m_playerRot.GetAngleAmount(); }

			/// @brief �v���C���[�̉�]�p�x�ω��ʂ����ɖ߂�
			void ResetAngle(){ m_playerRot.AngleReset(); }

			/// @brief ���s
			void Execution();

		private:
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ��]
			Quaternion m_qRot = g_quatIdentity;
			/// @brief ���f��
			render::model::SkinModelRender* m_playerModel = nullptr;
			/// @brief �X�e�[�g
			EnPlayerStates m_playerState = enPlayerIdle;
			/// @brief �A�j���[�V����
			Animation m_playerAnimation;
			/// @brief �ړ�
			Move m_playerMove;
			/// @brief ��]
			Rotation m_playerRot;
		};
	}
}
