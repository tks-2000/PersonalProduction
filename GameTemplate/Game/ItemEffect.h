#pragma once

namespace mainGame {
	namespace item {
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();
			void Init(Item* item);
			void Execution();

		private:

			void PlaySpawnEffect();

			void PlayGetEffect();

			bool m_isInitd = false;

			bool m_isSpawnEffectPlay = false;
			
			render::effect::EffectRender* m_spawnEffect = nullptr;

			bool m_isGetEffectPlay = false;

			render::effect::EffectRender* m_getEffect = nullptr;

			Vector3 m_getEffectScale = g_vec3Zero;

			Item* m_item = nullptr;
		};
	}
}
