#pragma once


class SkinModelRender;

namespace mainGame {
	namespace player {

		class Player;

		/// @brief �A�j���[�V�����̎�ނ̗񋓌^
		enum EnPlayerAnimations {
			enPlayerAnimationIdle,	//�ҋ@
			enPlayerAnimationWark,	//����
			enPlayerAnimationRun,
			enPlayerAnimationClear,
			enPlayerAnimationDamage,
			enPlayerAnimationKneelDown,
			enPlayerAnimationNum	//���v��
		};

		/// @brief �v���C���[�̃A�j���[�V�����𐧌䂷��N���X
		class Animation
		{
		public:
			Animation();
			~Animation();

			/// @brief ������
			/// @param pl ������K�p����v���C���[�̃A�h���X
			void Init(Player* pl);

			/// @brief �A�j���[�V�����̍X�V
			void AnimationUpdate();

			/// @brief �Đ�����A�j���[�V�����̃X�e�[�g�����
			/// @return �A�j���[�V�����X�e�[�g
			const EnPlayerAnimations& GetAnimationState() { return m_playerAnimState; }

			/// @brief �A�j���[�V�����N���b�v�����
			/// @return �A�j���[�V�����N���b�v�̃|�C���^
			AnimationClip* GetAnimatonClip() { return m_playerAnimationClip; }

			/// @brief �A�j���[�V�����̍��v�������
			/// @return �A�j���[�V�����̍��v��
			EnPlayerAnimations GetAnimationNum() { return enPlayerAnimationNum; }
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �A�j���[�V�����X�e�[�g
			EnPlayerAnimations m_playerAnimState = enPlayerAnimationIdle;
			/// @brief �A�j���[�V�����N���b�v
			AnimationClip m_playerAnimationClip[enPlayerAnimationNum];
			/// @brief �v���C���[
			Player* m_player = nullptr;

			Game* m_game = nullptr;
		};
	}
}