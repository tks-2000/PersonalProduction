#include "stdafx.h"
#include "AttackPoint.h"

namespace mainGame {
	namespace defensiveTarget {
		AttackPoint::AttackPoint()
		{

		}

		AttackPoint::~AttackPoint()
		{
			
		}

		void AttackPoint::Init(DefensiveTarget* defensiveTarget)
		{
			//g—p‚·‚éî•ñ‚ğİ’è
			m_defensiveTarget = defensiveTarget;

			//‰Šú‰»Š®—¹
			m_isInitd = true;
		}

		void AttackPoint::Execution()
		{
			//–¢‰Šú‰»‚È‚çÀs‚µ‚È‚¢
			if (m_isInitd == false) {
				return;
			}
		}
	}
}