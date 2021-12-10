#pragma once
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief ���_�̏C������
		class RepairTools : public Item
		{
		public:

			

			void Activation();

		private:

			void InitData();

			void Efficacy();

			/// @brief �h�q�Ώ�
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
