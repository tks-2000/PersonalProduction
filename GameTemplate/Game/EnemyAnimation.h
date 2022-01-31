#pragma once
#include "EnemyResource.h"

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief �G�̃A�j���[�V�����̗񋓌^
		enum EnEnemyAnimations {
			/// @brief �ҋ@
			enEnemyAnimationIdle,
			/// @brief ����
			enEnemyAnimationWark,
			/// @brief �N���A(�U��)
			enEnemyAnimationClear,
			/// @brief �_���[�W
			enEnemyAnimationDamage,
			/// @brief �_�E��(���j)
			enEnemyAnimationKneelDown,
			/// @brief �A�j���[�V�����̍��v��
			enEnemyAnimationNum
		};

		/// @brief �G�̃A�j���[�V�����𐧌䂷��N���X
		class Animation
		{
		public:
			Animation();
			~Animation();

			/// @brief ������
			/// @param enemy ������K�p����G�̃A�h���X
			void Init(Enemy* enemy);

			/// @brief �A�j���[�V�����̍X�V
			void AnimationUpdate();

			/// @brief �A�j���[�V�����̃X�e�[�^�X�����
			/// @return �Đ�����A�j���[�V�����̃X�e�[�^�X
			const EnEnemyAnimations& GetAnimationState() { return m_state; }

			/// @brief �A�j���[�V�����N���b�v�����
			/// @return �A�j���[�V�����N���b�v�̃A�h���X
			AnimationClip* GetAnimationClip() { return m_animClip; }

			/// @brief �Đ�����A�j���[�V�����̍��v�������
			/// @return �Đ�����A�j���[�V�����̍��v��
			EnEnemyAnimations GetAnimationNum() { return enEnemyAnimationNum; }

		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �A�j���[�V�����̃X�e�[�^�X
			EnEnemyAnimations m_state = enEnemyAnimationIdle;
			/// @brief �A�j���[�V�����N���b�v
			AnimationClip m_animClip[enEnemyAnimationNum];
			/// @brief �G�N���X
			Enemy* m_enemy = nullptr;

			GameScene* m_gameScene = nullptr;
		};
	}
}
