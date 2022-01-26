#pragma once
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief ���_�̏C������
		class RepairTools : public Item
		{
		public:

			

			void Activation() override;

		private:

			void InitData() override;

			void Spawn() override;

			void Efficacy() override;

			/// @brief �h�q�Ώ�
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
