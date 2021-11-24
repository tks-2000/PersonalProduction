#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"
#include "PlayerAttack.h"

class SkinModelRender;


namespace mainGame {

	class Game;

	namespace player {
		
		/// @brief �v���C���[�̏�Ԃ����߂�񋓌^
		enum EnPlayerStates {
			/// @brief �ҋ@
			enPlayerIdle,
			/// @brief ����
			enPlayerWark,
			/// @brief ����
			enPlayerRun,
			/// @brief �_���[�W
			enPlayerDamage,
			/// @brief �v���C���[�̃X�e�[�^�X�̍��v��
			enPlayerStateNum
		};

		/// @brief ���삷��v���C���[�̋@�\���܂Ƃ߂��N���X
		class Player : public IGameObject
		{
		public:
			Player();
			~Player();

			void Init();
			bool Start();
			void Update();

			/// @brief �v���C���[�̏�Ԃ�ݒ�
			/// @param plState �ݒ肷��v���C���[�̏��
			void SetPlayerState(const EnPlayerStates& plState) { m_playerState = plState; }

			/// @brief �v���C���[�̏�Ԃ����
			/// @return �v���C���[�̃X�e�[�^�X
			const EnPlayerStates& GetPlayerStatus() { return m_playerState; }

			/// @brief �v���C���[�̍��W�����
			/// @return �v���C���[�̍��W��const�Q��
			const Vector3& GetPlayerPosition() { return m_position; }

			/// @brief �v���C���[�̍��W��ݒ�
			/// @param pos �ݒ肷��v���C���[�̍��W 
			void SetPlayerPosition(const Vector3& pos) { m_position = pos; }

			float GetPlayerAngle() { return m_playerRot.GetAngle(); }

			/// @brief �v���C���[�̕��������
			/// @return �v���C���[�̌����Ă��������const�Q��
			const Vector3& GetPlayerDirection() { return m_playerRot.GetDirection(); }

			/// @brief �v���C���[�̉�]�p�x�̕ω��ʂ����
			/// @return �v���C���[�̉�]�p�x�̕ω���
			float GetAngleAmount() { return m_playerRot.GetAngleAmount(); }

			/// @brief �v���C���[�̉�]�p�x�ω��ʂ����ɖ߂�
			void ResetAngle(){ m_playerRot.AngleReset(); }

			/// @brief �G�̏����Z�b�g
			/// @param enemy �Z�b�g����G�N���X�̃A�h���X
			void SetEnemyData(enemy::Enemy* enemy) { m_playerAttack.AddEnemyData(enemy); }

			/// @brief �G�̏����폜
			/// @param enemy �폜����G�N���X�̃A�h���X
			void DeleteEnemyData(enemy::Enemy* enemy) { m_playerAttack.DeleteEnemyData(enemy); }

			/// @brief ���s
			void Execution();

		private:
			void GameStartExecution();
			void GameInProgressExecution();
			void GameClearExecution();
			void GameOverExecution();

			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ��]
			Quaternion m_qRot = g_quatIdentity;
			/// @brief ���f��
			render::model::SkinModelRender* m_playerModel = nullptr;

			render::model::SkinModelRender* m_plMapModel = nullptr;
			/// @brief �X�e�[�g
			EnPlayerStates m_playerState = enPlayerIdle;
			/// @brief �A�j���[�V����
			Animation m_playerAnimation;
			/// @brief �ړ�
			Move m_playerMove;
			/// @brief ��]
			Rotation m_playerRot;
			/// @brief �U��
			Attack m_playerAttack;

			Game* m_game = nullptr;
		};
	}
}
