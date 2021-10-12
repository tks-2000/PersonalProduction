#pragma once



namespace mainGame {
	namespace defensiveTarget{
		class DefensiveTarget;
	}
	namespace enemy {
		/// @brief “G‚ÌUŒ‚‚ğ§Œä‚·‚éƒNƒ‰ƒX
		class Attack
		{
		public:
			Attack();
			~Attack();
			void Init();
			void Execution();
		private:

			void ExecuteAttack();

			bool m_isInitd = false;
			int m_attackPower = 0;
			float m_attackTimer = 0.0f;
			
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
