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
			//使用する情報を設定
			m_defensiveTarget = defensiveTarget;

			//初期化完了
			m_isInitd = true;
		}

		void AttackPoint::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}
		}
	}
}