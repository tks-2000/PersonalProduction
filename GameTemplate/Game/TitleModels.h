#pragma once

namespace mainGame {
	namespace title {
		/// @brief �^�C�g����ʂ̃v���C���[�̃A�j���[�V����
		enum EnTitlePlAnim {
			enTitlePlIdle,
			enTitlePlClear,
			enTitlePlAnimNum
		};

		/// @brief �^�C�g����ʂɏo�����f���𐧌䂷��N���X
		class Models
		{
		public:
			Models();
			~Models();
			/// @brief ������
			/// @param title �^�C�g���̃A�h���X
			void Init(Title* title);
			/// @brief ���s
			void Execution();
			/// @brief �v���C���[�̃A�j���[�V������ݒ�
			/// @param state �A�j���[�V�����̃X�e�[�g
			void SetTitlePlayerAnimState(const EnTitlePlAnim& state) { m_plAnimState = state; }
		private:
			/// @brief ����̃��f����ݒ�
			void SetWeapons();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �v���C���[�̃��f��
			render::model::SkinModelRender* m_plModel = nullptr;
			/// @brief �v���C���[���f���̍��W
			Vector3 m_plModelPos = g_vec3Zero;
			/// @brief �v���C���[�̃A�j���[�V�����N���b�v
			AnimationClip m_plAnim[enTitlePlAnimNum];
			/// @brief �v���C���[�̃A�j���[�V�����X�e�[�g
			EnTitlePlAnim m_plAnimState = enTitlePlIdle;
			/// @brief ���̃��f��
			render::model::SkinModelRender* m_swordModel = nullptr;
			/// @brief ���̃��f��
			render::model::SkinModelRender* m_shieldModel = nullptr;
			/// @brief ���f���̐�
			enum {MODEL_NUM = 2};
			/// @brief �G�l�~�[�̃��f��
			render::model::SkinModelRender* m_enemyModel[MODEL_NUM] = { nullptr };
			/// @brief �G�l�~�[�̃��f���̍��W
			Vector3 m_enemyModelPos[MODEL_NUM] = { g_vec3Zero,g_vec3Zero };
			/// @brief �^�C�g����ʂ̃G�l�~�[�̃A�j���[�V����
			enum EnTitleEnemyAnim {
				enTitleEnemyIdle,
				enTitleEnemyAnimNum,
			};
			/// @brief �G�l�~�[�̃A�j���[�V�����N���b�v
			AnimationClip m_enemyAnim[enTitleEnemyAnimNum];
			/// @brief �X�e�[�W�̃��f��
			render::model::SkinModelRender* m_stageModel = nullptr;
			/// @brief �w�i�̃��f��
			render::model::SkinModelRender* m_backgroundModel = nullptr;
			/// @brief �h�q�Ώۂ̃��f��
			render::model::SkinModelRender* m_houseModel = nullptr;
			/// @brief �^�C�g��
			Title* m_title = nullptr;
		};
	}
}
