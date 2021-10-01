#pragma once


namespace Render {
	class Lighting;
	class Shadow;
	class PostEffect;

	/// @brief �����_�����O�ɕK�v�ȋ@�\���܂Ƃ߂��N���X
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

		/// @brief �`�悷�郂�f����ǉ�
		/// @param model �ǉ����郂�f���̃A�h���X
		void SetDrawModel(Model* model);

		/// @brief �`�悵�Ă��郂�f�����폜
		/// @param model �폜���郂�f���̃A�h���X
		void DeleteModel(Model* model);

		

	private:


		/// @brief ���C�e�B���O
		Lighting* m_lig = nullptr;
		/// @brief �V���h�E
		Shadow* m_shadow = nullptr;
		/// @brief �|�X�g�G�t�F�N�g
		PostEffect* m_postEffect = nullptr;

		/// @brief ���C�������_�����O�^�[�Q�b�g
		RenderTarget m_mainRenderTarget;

		/// @brief �`�悷�郂�f���̔z��
		std::vector<Model*> m_drawModels;

		/// @brief �t���[���o�b�t�@�̃X�v���C�g�̏��������
		SpriteInitData m_frameBufferSpriteInitData;
		/// @brief �t���[���o�b�t�@�̃X�v���C�g
		Sprite m_frameBufferSprite;

		Vector3 m_ligColor = g_vec3One;
	};
}
