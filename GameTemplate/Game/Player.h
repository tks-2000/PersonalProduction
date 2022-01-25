#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"
#include "PlayerAttack.h"
#include "PlayerEffect.h"
#include "PlayerSound.h"
#include "ItemSlot.h"
#include "ItemResource.h"

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
			/// @brief �U�����Ă���
			enPlayerAttack,
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

			/// @brief �v���C���[�̍Đ����̃A�j���[�V���������
			/// @return �v���C���[�̃A�j���[�V�����̃X�e�[�^�X
			const EnPlayerAnimations& GetPlayerAnimation() { return m_playerAnimation.GetAnimationState(); }

			/// @brief �v���C���[�̍��W�����
			/// @return �v���C���[�̍��W��const�Q��
			const Vector3& GetPlayerPosition() { return m_position; }

			/// @brief �v���C���[�̍��W��ݒ�
			/// @param pos �ݒ肷��v���C���[�̍��W 
			void SetPlayerPosition(const Vector3& pos) { m_position = pos; }

			const Vector3& GetMoveSpeed() { return m_playerMove.GetMoveSpssd(); }

			void SetMoveSpeed(const Vector3& speed) { m_playerMove.SetMoveSpeed(speed); }

			void SetAddVerocity(const float addVerocity) { m_playerMove.SetAddVerocity(addVerocity); }

			float GetPlayerAngle() { return m_playerRot.GetAngle(); }

			const Quaternion& GetPlayerRotation() {return m_playerRot.GetRotation(); }

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

			/// @brief �A�C�e���X���b�g�ɃA�C�e����ǉ�
			/// @param item �ǉ�����A�C�e��
			/// @return true�Œǉ��ł��� false�Œǉ��o���Ȃ�����
			bool SetItemSlot(item::Item* item) { return m_itemSlot.SetItem(item); }

			/// @brief ���ݑI�����Ă���A�C�e���X���b�g�ԍ������
			/// @return ���ݑI�����Ă���A�C�e���X���b�g�ԍ�
			const int GetSelectSlotNum()const { return m_itemSlot.GetSelectSlotNum(); }

			/// @brief �X���b�g�ɃA�C�e���������Ă��邩���ׂ�
			/// @param slotNum ���ׂ�A�C�e���X���b�g�ԍ�
			/// @return �����Ă����true �����Ă��Ȃ����false
			const bool IsOwnedItem(const int slotNum) const { return m_itemSlot.IsOwnedItem(slotNum); }

			/// @brief �c�e�����擾
			/// @return �v���C���[�̎c�e��
			const int GetRemainingBullet() { return m_playerAttack.GetRemainingBullets(); }

			/// @brief �e�ۂ̃f�[�^�����
			/// @return �e�ۂ̔z��̃A�h���X
			std::vector <Bullet*>* GetBulletData() { return m_playerAttack.GetBullets(); }

			/// @brief �v���C���[�ɍU�����肪�o�Ă��邩���ׂ�
			/// @return true�ŏo�Ă��� false�ŏo�Ă��Ȃ�
			const bool IsAttackJudgement() const { return m_playerAttack.IsAttackJudgement(); }

			/// @brief �v���C���[���t���`���[�W��Ԃ����ׂ�
			/// @return true�Ńt���`���[�W��� false�Ńt���`���[�W��Ԃł͂Ȃ�
			const bool IsFollCharge() const { return m_playerAttack.IsFollCharge(); }

			/// @brief �U���\�ȕ�����v�����擾
			/// @return �U���\�ȕ�����v��
			const float GetAttackPossibleMatchRate() const { return m_playerAttack.GetAttackPossibleMatchRate(); }

			/// @brief ���G��Ԃ��H
			/// @return true�Ŗ��G false�Ŗ��G�łȂ�
			bool IsInvincible() const { return m_invincibleFlag; }

			/// @brief �A�C�e���X���b�g���̃A�C�e���̎�ނ��擾
			/// @param slotNum �X���b�g�ԍ�
			/// @return �A�C�e���̎��
			const item::EnItemType& GetSlotItemType(const int slotNum) { return m_itemSlot.GetItemType(slotNum); }

			/// @brief �v���C���[���U�����J�n�������H
			/// @return true�ŊJ�n���� false�ŊJ�n���Ă��Ȃ��E�����U�����Ă���
			const bool IsAttackStart() { return m_playerAttack.IsAttackStart(); }

			/// @brief ���s
			void Execution();

		private:
			
			void DamageExecution();

			void InvincibleExecution();

			void SetWeapons();

			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ��]
			Quaternion m_qRot = g_quatIdentity;
			/// @brief �v���C���[���f��
			render::model::SkinModelRender* m_playerModel = nullptr;
			/// @brief ���̃��f��
			render::model::SkinModelRender* m_swordModel = nullptr;
			/// @brief ���̃��f��
			render::model::SkinModelRender* m_shieldModel = nullptr;
			/// @brief �}�b�v��̃��f��
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

			EffectGenerator  m_playerEffect;

			Sound m_playerSound;

			ItemSlot m_itemSlot;

			float m_damageTimer = 0.0f;

			bool m_invincibleFlag = false;

			float m_invincibleTimer = 0.0f;

			Game* m_game = nullptr;
		};
	}
}
