#pragma once

namespace Render {
	class PostEffect : public IGameObject
	{
	public:
		PostEffect();
		~PostEffect();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	private:

	};
}