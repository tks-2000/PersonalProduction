#pragma once
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief ‹’“_‚ÌC—“¹‹ï
		class RepairTools : public Item
		{
		public:

			

			void Activation() override;

		private:

			void InitData() override;

			void Spawn() override;

			void Efficacy() override;

			/// @brief –h‰q‘ÎÛ
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
