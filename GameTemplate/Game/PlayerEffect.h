#pragma once

namespace mainGame {
	namespace player {

		

		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();
			void Init(Player* player);
			void Execution();
		private:

			

			bool m_isInitd = false;

			

			Player* m_player = nullptr;
		};
	}
}
