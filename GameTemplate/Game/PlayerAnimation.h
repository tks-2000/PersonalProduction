#pragma once


class SkinModelRender;

namespace MainGame {
	namespace Player {

		class Player;

		/// @brief アニメーションの種類の列挙型
		enum PlayerAnimations {
			enPlayerAnimationIdle,	//待機
			enPlayerAnimationWark,	//歩き
			enPlayerAnimationNum	//合計数
		};

		/// @brief プレイヤーのアニメーションを制御するクラス
		class Animation
		{
		public:
			Animation();
			~Animation();

			/// @brief 初期化
			void Init();

			/// @brief アニメーションの更新
			void AnimationUpdate();

			/// @brief 再生するアニメーションのステートを入手
			/// @return アニメーションステート
			const PlayerAnimations& GetAnimationState() { return m_playerAnimState; }

			/// @brief アニメーションクリップを入手
			/// @return アニメーションクリップのポインタ
			AnimationClip* GetAnimatonClip() { return m_playerAnimationClip; }

			/// @brief アニメーションの合計数を入手
			/// @return アニメーションの合計数
			PlayerAnimations GetAnimationNum() { return enPlayerAnimationNum; }
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief アニメーションステート
			PlayerAnimations m_playerAnimState = enPlayerAnimationIdle;
			/// @brief アニメーションクリップ
			AnimationClip m_playerAnimationClip[enPlayerAnimationNum];
			/// @brief プレイヤー
			Player* m_player = nullptr;
		};
	}
}