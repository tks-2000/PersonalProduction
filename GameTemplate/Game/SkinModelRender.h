#pragma once
#include "Lighting.h"
class AnimationClip;
class Lighting;
class Shadow;

namespace Render {
	/// @brief 3D���f���̕\�����s���N���X
	class SkinModelRender : public IGameObject
	{
	public:
		SkinModelRender();
		~SkinModelRender();

		bool Start();
		void Update();
		void Render(RenderContext& rc);

		/// @brief ���f���̏�Ԃ����
		/// @return ���f����const�Q��
		const Model& GetModel() const { return m_model; }

		

		/// @brief ���f���̍��W��ݒ�
		/// @param pos ���W
		void SetPosition(const Vector3& pos) { m_position = pos; }

		/// @brief ���f���̑傫����ݒ�
		/// @param scale �g�嗦
		void SetScale(const Vector3& scale) { m_scale = scale; }

		/// @brief ���f���̉�]��ݒ�
		/// @param rot �N�H�[�^�j�I��
		void SetRotation(const Quaternion& rot) { m_qRot = rot; }


		void SetNewModel() { m_model.Init(m_modelInitData); }

		/// @brief ���f���̍��W�����
		/// @return ���W
		Vector3 GetPosition() { return m_position; }

		/// @brief ���f���̏�����
		/// @param modelFilePath ���f���̃t�@�C���p�X
		void Init(const char* modelFilePath);

		/// @brief ���f���̃V�F�[�_�[�t�@�C���p�X��ύX
		/// @param fxFilePath �V�F�[�_�[�t�@�C���p�X
		void ChangeFxFilePath(const char* fxFilePath) { m_modelInitData.m_fxFilePath = fxFilePath; m_model.Init(m_modelInitData); }

		/// @brief �e�𐶐�����
		void CreateShadow();

		void InitA(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis enAxis, AnimationClip* animation, int animationNum, bool cullMode);

		void PlayAnimation(int animNo, float interpolateTime);

		/// @brief �X�L�����f�������_���[�̃��[���h�s����擾
		/// @return ���f���̃��[���h�s��
		Matrix GetModelWorldMatrix() { return m_model.GetWorldMatrix(); }

	private:
		/// @brief ���f���̃t�@�C���p�X
		const char* m_modelFilePath = nullptr;
		/// @brief ���f��
		Model m_model;
		/// @brief ���f���̏��������
		ModelInitData m_modelInitData;
		/// @brief �e�𐶐����邩�ǂ����̃t���O
		bool m_shadowFlag = false;
		/// @brief �e�`�ʗp�̃��f��
		Model m_shadowModel;
		/// @brief �e�`�ʗp�̃��f�����������
		ModelInitData m_shadowModelInitData;
		/// @brief ���C�e�B���O
		Lighting* m_lig = nullptr;
		/// @brief �V���h�E
		Shadow* m_shadow = nullptr;

		Vector3 m_position = Vector3::Zero;			//���W
		Vector3 m_scale = Vector3::One;				//�g�嗦
		Quaternion m_qRot = Quaternion::Identity;	//��]

		Skeleton m_skeleton;
		Animation m_animation;
		AnimationClip* m_animationClip;
	};

}