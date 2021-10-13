#pragma once
#include "EnemyMove.h"
#include "EnemyAttack.h"

namespace mainGame {
	namespace enemy {

		/// @brief 敵の状態を表すステート
		enum EnEnemyState {
			/// @brief 待機
			enEnemyIdle,
			/// @brief 移動
			enEnemyMove,
			/// @brief 攻撃
			enEnemyAttack,
			/// @brief 停止
			enEnemyStop,
			/// @brief ステータスの合計数
			enEnemyStateNum
		};

		/// @brief 敵の処理をまとめたクラス
		class Enemy : public IGameObject
		{
		public:
			Enemy();
			~Enemy();

			/// @brief 初期化
			void Init();

			/// @brief 実行
			void Execution();

			/// @brief 敵の状態を設定
			/// @param state 設定するステート
			void SetState(const EnEnemyState& state) { m_state = state; }

		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 敵キャラクターモデル
			render::model::SkinModelRender* m_enemyModel = nullptr;
			/// @brief 敵の移動
			Move m_enemyMove;
			/// @brief 敵の攻撃
			Attack m_enemyAttack;
			/// @brief ステート
			EnEnemyState m_state = enEnemyIdle;
		};
	}
}
