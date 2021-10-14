#include "stdafx.h"
#include "EnemyAnimation.h"

namespace mainGame {
	namespace enemy {
		Animation::Animation()
		{
			//未初期化で開始
			m_isInitd = false;

			//アニメーションクリップをロード
			m_animClip[enEnemyAnimationIdle].Load("Assets/animData/idle.tka");
			m_animClip[enEnemyAnimationIdle].SetLoopFlag(true);
			m_animClip[enEnemyAnimationWark].Load("Assets/animData/walk.tka");
			m_animClip[enEnemyAnimationWark].SetLoopFlag(true);
			m_animClip[enEnemyAnimationClear].Load("Assets/animData/unityChan/clear.tka");
			m_animClip[enEnemyAnimationClear].SetLoopFlag(true);
			m_animClip[enEnemyAnimationDamage].Load("Assets/animData/unityChan/damage.tka");
			m_animClip[enEnemyAnimationDamage].SetLoopFlag(false);
			m_animClip[enEnemyAnimationKneelDown].Load("Assets/animData/unityChan/KneelDown.tka");
			m_animClip[enEnemyAnimationKneelDown].SetLoopFlag(false);
		}

		Animation::~Animation()
		{

		}

		void Animation::Init()
		{
			//敵の情報を入手
			m_enemy = FindGO<Enemy>(ENEMY_NAME);

			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//初期化が終わっていなければ実行しない
			if (m_isInitd == false) {
				return;
			}

			//敵のステータスの状態によって再生するアニメーションを変える
			switch (m_enemy->GetState()) {
			case enEnemyIdle: {
				m_state = enEnemyAnimationIdle;
			}break;
			case enEnemyMove: {
				m_state = enEnemyAnimationWark;
			}break;
			case enEnemyAttack: {
				m_state = enEnemyAnimationClear;
			}break;
			case enEnemyDamage: {
				m_state = enEnemyAnimationDamage;
			}break;
			case enEnemyDown: {
				m_state = enEnemyAnimationKneelDown;
			}break;
			}
		}
	}
}