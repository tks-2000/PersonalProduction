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
			//�g�p�������ݒ�
			m_defensiveTarget = defensiveTarget;

			//����������
			m_isInitd = true;
		}

		void AttackPoint::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}
		}
	}
}