#pragma once


class SkinModelRender;

namespace mainGame {
	namespace player {

		class Player;

		/// @brief アニメーションの種類の列挙型
		enum EnPlayerAnimations {
			enPlayerAnimationIdle,	//待機
			enPlayerAnimationWark,	//歩き
			enPlayerAnimationRun,
			enPlayerAnimationClear,
			enPlayerAnimationDamage,
			enPlayerAnimationKneelDown,
			enPlayerAnimationNum	//合計数
		};

		/// @brief プレイヤーのアニメーションを制御するクラス
		class Animation
		{
		public:
			Animation();
			~Animation();

			/// @brief 初期化
			/// @param pl 処理を適用するプレイヤーのアドレス
			void Init(Player* pl);

			/// @brief アニメーションの更新
			void AnimationUpdate();

			/// @brief 再生するアニメーションのステートを入手
			/// @return アニメーションステート
			const EnPlayerAnimations& GetAnimationState() { return m_playerAnimState; }

			/// @brief アニメーションクリップを入手
			/// @return アニメーションクリップのポインタ
			AnimationClip* GetAnimatonClip() { return m_playerAnimationClip; }

			/// @brief アニメーションの合計数を入手
			/// @return アニメーションの合計数
			EnPlayerAnimations GetAnimationNum() { return enPlayerAnimationNum; }
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief アニメーションステート
			EnPlayerAnimations m_playerAnimState = enPlayerAnimationIdle;
			/// @brief アニメーションクリップ
			AnimationClip m_playerAnimationClip[enPlayerAnimationNum];
			/// @brief プレイヤー
			Player* m_player = nullptr;

			Game* m_game = nullptr;
		};
	}
}