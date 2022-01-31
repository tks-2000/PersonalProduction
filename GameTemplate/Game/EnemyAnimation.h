#pragma once
#include "EnemyResource.h"

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief 敵のアニメーションの列挙型
		enum EnEnemyAnimations {
			/// @brief 待機
			enEnemyAnimationIdle,
			/// @brief 歩き
			enEnemyAnimationWark,
			/// @brief クリア(攻撃)
			enEnemyAnimationClear,
			/// @brief ダメージ
			enEnemyAnimationDamage,
			/// @brief ダウン(撃破)
			enEnemyAnimationKneelDown,
			/// @brief アニメーションの合計数
			enEnemyAnimationNum
		};

		/// @brief 敵のアニメーションを制御するクラス
		class Animation
		{
		public:
			Animation();
			~Animation();

			/// @brief 初期化
			/// @param enemy 処理を適用する敵のアドレス
			void Init(Enemy* enemy);

			/// @brief アニメーションの更新
			void AnimationUpdate();

			/// @brief アニメーションのステータスを入手
			/// @return 再生するアニメーションのステータス
			const EnEnemyAnimations& GetAnimationState() { return m_state; }

			/// @brief アニメーションクリップを入手
			/// @return アニメーションクリップのアドレス
			AnimationClip* GetAnimationClip() { return m_animClip; }

			/// @brief 再生するアニメーションの合計数を入手
			/// @return 再生するアニメーションの合計数
			EnEnemyAnimations GetAnimationNum() { return enEnemyAnimationNum; }

		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief アニメーションのステータス
			EnEnemyAnimations m_state = enEnemyAnimationIdle;
			/// @brief アニメーションクリップ
			AnimationClip m_animClip[enEnemyAnimationNum];
			/// @brief 敵クラス
			Enemy* m_enemy = nullptr;

			GameScene* m_gameScene = nullptr;
		};
	}
}
