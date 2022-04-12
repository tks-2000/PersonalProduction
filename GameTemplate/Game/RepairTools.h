#pragma once
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief ���_�̏C������
		class RepairTools : public Item
		{
		public:
			/// @brief ���ʔ���
			void Activation() override;

		private:
			/// @brief �f�[�^��������
			void InitData() override;
			/// @brief �o��
			void Spawn() override;
			/// @brief ���ʔ������̏���
			void Efficacy() override;

			/// @brief �h�q�Ώ�
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
