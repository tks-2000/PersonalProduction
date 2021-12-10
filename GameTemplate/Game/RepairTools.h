#pragma once
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief ‹’“_‚ÌC—“¹‹ï
		class RepairTools : public Item
		{
		public:

			

			void Activation();

		private:

			void InitData();

			void Efficacy();

			/// @brief –h‰q‘ÎÛ
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
