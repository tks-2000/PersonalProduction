#pragma once
#include "Lighting.h"
class AnimationClip;
class RenderingEngine;
class Lighting;
class Shadow;

namespace mainGame {
	namespace map {
		class MiniMap;
	}
}
namespace render {
	namespace model {
		/// @brief ���f���̕`���
		enum EnModelDrawTarget {
			enExpandModelGroup1,
			enExpandModelGroup2,
			enExpandModelGroup3,
			enMainRenderTarget
		};
		
		/// @brief 3D���f���̕\�����s���N���X
		class SkinModelRender : public IGameObject
		{
		public:
			SkinModelRender();
			~SkinModelRender();

			bool Start();
			void Update();

			/// @brief ���f���̏�Ԃ����
			/// @return ���f����const�Q��
			Model& GetModel(){ return m_model; }



			/// @brief ���f���̍��W��ݒ�
			/// @param pos ���W
			void SetPosition(const Vector3& pos) { m_position = pos; m_updateWithMatrix = false; }

			/// @brief ���f���̑傫����ݒ�
			/// @param scale �g�嗦
			void SetScale(const Vector3& scale) { m_scale = scale; m_updateWithMatrix = false; }

			/// @brief ���f���̉�]��ݒ�
			/// @param rot �N�H�[�^�j�I��
			void SetRotation(const Quaternion& rot) { m_qRot = rot; m_updateWithMatrix = false; }

			/// @brief ���f���̃��[���h�s���ݒ�
			/// @param matrix ���[���h�s��
			void SetWorldMatrix(const Matrix& matrix) { m_world = matrix; m_updateWithMatrix = true; }

			/// @brief ���f���̍��W�����
			/// @return ���W
			Vector3 GetPosition() { return m_position; }

			/// @brief ���f���̏�����
			/// @param modelFilePath ���f���̃t�@�C���p�X
			//void Init(const char* modelFilePath);

			/// @brief ���f����������
			/// @param modelFilePath ���f���̃t�@�C���p�X
			/// @param skeletonPath �X�P���g���̃t�@�C���p�X
			/// @param animationClip �A�j���[�V�����N���b�v
			/// @param animationNum �A�j���[�V�����̐�
			/// @param enAxsis ���f���̏����
			void Init(
				const char* modelFilePath,
				const EnModelDrawTarget& drawTarget = enMainRenderTarget,
				const char* skeletonPath = nullptr,
				AnimationClip* animationClip = nullptr,
				int animationNum = 0,
				EnModelUpAxis enAxsis = enModelUpAxisZ
			);

			/// @brief �V�F�[�_�[�t�@�C���p�X���ʂɐݒ�
			/// @param fxFilePath �ݒ肷��V�F�[�_�[�t�@�C���p�X
			void SetFxFilePath(const char* fxFilePath) { m_fxFilePath = fxFilePath; }

			/// @brief �����_�����O�^�[�Q�b�g���ʂɐݒ�
			/// @param rt �ݒ肷�郌���_�����O�^�[�Q�b�g�̃A�h���X
			void SetRenderTarget(int groupNum, RenderTarget* rt);

			/// @brief �e�𐶐�����
			void CreateShadow();

			/// @brief �A�j���[�V�������Đ�����
			/// @param animNo �Đ�����A�j���[�V�����ԍ�
			/// @param interpolateTime �A�j���[�V�����⊮��
			void PlayAnimation(const int animNo, const float interpolateTime = 0.0f);

			/// @brief �X�L�����f�������_���[�̃��[���h�s����擾
			/// @return ���f���̃��[���h�s��
			const Matrix& GetModelWorldMatrix() { return m_model.GetWorldMatrix(); }

			/// @brief ���f���̃X�P���g�������
			/// @return �X�P���g���̃A�h���X
			Skeleton* GetSkeleton() { return &m_skeleton; }

			/// @brief ���s
			void Execution();

		private:
			/// @brief ���f���̃t�@�C���p�X
			const char* m_modelFilePath = nullptr;
			/// @brief �V�F�[�_�[�t�@�C���p�X
			const char* m_fxFilePath = nullptr;
			/// @brief �X�P���g���̃t�@�C���p�X
			const char* m_skeletonFilePath = nullptr;
			/// @brief ���f��
			Model m_model;
			/// @brief ���f���̏��������
			ModelInitData m_modelInitData;


			/// @brief ���f���ɐݒ肷��X�P���g��
			Skeleton m_skeleton;
			/// @brief �A�j���[�V����
			Animation m_animation;
			/// @brief �A�j���[�V�����N���b�v
			AnimationClip* m_animationClip;

			/// @brief �e�𐶐����邩�ǂ����̃t���O
			bool m_shadowFlag = false;
			/// @brief �e�`�ʗp�̃��f��
			Model m_shadowModel;
			/// @brief �e�`�ʗp�̃��f�����������
			ModelInitData m_shadowModelInitData;
			//�����_�����O�G���W��
			RenderingEngine* m_renderingEngine = nullptr;
			/// @brief ���C�e�B���O
			light::Lighting* m_lig = nullptr;
			/// @brief �V���h�E
			shadow::Shadow* m_shadow = nullptr;

			Vector3 m_position = Vector3::Zero;			//���W
			Vector3 m_scale = Vector3::One;				//�g�嗦
			Quaternion m_qRot = Quaternion::Identity;	//��]

			/// @brief �s��ōX�V���s���t���O
			bool m_updateWithMatrix = false;
			Matrix m_world;//�s��

			/// @brief �A�j���[�V�������Đ����邩�ǂ����̃t���O
			bool m_animFlag = false;

			/// @brief �����������t���O
			bool m_isInitd = false;

			mainGame::map::MiniMap* m_miniMap = nullptr;

			/// @brief ���g�̕`���
			EnModelDrawTarget m_target = enMainRenderTarget;

			/// @brief ���f���̕`���
			RenderTarget* m_rt = nullptr;
		};
	}
}