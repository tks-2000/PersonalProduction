#pragma once


namespace Render {
	class Lighting;

	/// @brief �����_�����O�ɕK�v�ȋ@�\���܂Ƃ߂��N���X
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();

	private:
		Lighting* m_lig = nullptr;
	};
}
