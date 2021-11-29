#pragma once

namespace mainGame {
	namespace item {

		class Item : public IGameObject
		{
		public:

			Item();
			virtual ~Item();

			virtual void Init();

			virtual void Execution();
		protected:

			Vector3 m_position = g_vec3Zero;

			render::model::SkinModelRender* m_itemModel = nullptr;


		};
	}
}