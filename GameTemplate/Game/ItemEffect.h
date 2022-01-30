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

			bool m_isInitd = false;

			bool m_isSpawnEffectPlay = false;
			
			render::effect::EffectRender* m_spawnEffect = nullptr;

			Item* m_item = nullptr;
		};
	}
}
