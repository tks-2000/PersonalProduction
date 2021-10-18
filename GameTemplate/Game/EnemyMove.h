#pragma once
#include "Enemy.h"
#include "EnemyResource.h"

namespace mainGame{
	namespace enemy {

		class Enemy;

		


		/// @brief 敵の移動を制御するクラス
		class Move
		{
		public:
			Move();
			~Move();

			/// @brief 初期化
			/// @param enemy 処理を適用する敵のアドレス
			void Init(Enemy* enemy);

			/// @brief 移動を実行
			/// @param pos 移動する敵の座標
			/// @return 移動した結果の座標
			const Vector3& MoveExecute(Vector3& pos);

			/// @brief 待機中の処理を実行
			/// @param pos 待機中の座標
			/// @return 待機中の結果の座標
			const Vector3& IdleExecute(Vector3& pos);

			/// @brief 移動目標を設定
			/// @param target 移動する目標の座標
			void SetMoveTarget(const Vector3& target) { m_moveTarget = target; }

			/// @brief 移動速度を設定
			/// @param speed 設定する移動速度
			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

			/// @brief 移動速度を取得
			/// @return 移動速度のconst参照
			const Vector3& GetMoveSpeed() { return m_moveSpeed; }

			/// @brief 移動を停止
			/// @param pos 停止中の座標
			const Vector3& MoveStop(Vector3& pos);

		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 移動速度
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief 速度
			float m_moveVerocity = 0.0f;
			/// @brief 移動目標
			Vector3 m_moveTarget = g_vec3Zero;
			/// @brief 移動目標へのベクトル
			Vector3 m_toTarget = g_vec3Zero;
			/// @brief 移動方向
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief 移動目標との距離
			float m_targetDistance = 0.0f;
			/// @brief 移動開始するまでの時間
			float m_moveStartTimer = 0.0f;
			/// @brief キャラクターコントローラー
			CharacterController m_charaCon;
			/// @brief 敵クラス
			Enemy* m_enemy = nullptr;
		};
	}
}
