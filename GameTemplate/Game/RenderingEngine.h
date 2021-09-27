#pragma once


namespace Render {
	class Lighting;
	class Shadow;

	/// @brief �����_�����O�ɕK�v�ȋ@�\���܂Ƃ߂��N���X
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();

	private:
		/// @brief ���C�e�B���O
		Lighting* m_lig = nullptr;
		/// @brief �V���h�E
		Shadow* m_shadow = nullptr;
	};
}
