#pragma once

class Player;

namespace mainGame {
	class GameCamera;
	namespace player {
		/// @brief プレイヤーの移動を制御するクラス
		class Move
		{
		public:
			Move();
			~Move();

			/// @brief 初期化
			/// @param pl 処理を適用するプレイヤーのアドレス
			void Init(Player* pl);

			/// @brief 待機中の処理を実行
			const Vector3& IdleExecute(Vector3& pos);

			/// @brief 移動処理を実行
			/// @param pos 移動前の座標
			/// @return 移動後の座標
			const Vector3& MoveExecute(Vector3& pos);

			/// @brief 移動方向を取得
			/// @return 移動方向のconst参照
			const Vector3& GetMoveDirection() { return m_moveDirection; }

			/// @brief 移動速度を取得
			/// @return 移動速度のconst参照
			const Vector3& GetMoveSpssd() { return m_moveSpeed; }
		private:

			const Vector3& ApplyFriction(Vector3& speed);

			/// @brief 初期化しているかどうかのフラグ
			bool m_isInitd = false;

			/// @brief 左スティックの横入力
			float m_LStickX = 0.0f;
			/// @brief 左スティックの縦入力
			float m_LStickY = 0.0f;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 移動速度
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief 移動方向
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief 摩擦力
			Vector3 m_friction = g_vec3Zero;
			/// @brief 重力
			float m_gravity = 0.0f;
			/// @brief キャラクターコントローラー
			CharacterController m_charaCon;
			/// @brief ゲームカメラ
			GameCamera* m_gameCamera = nullptr;
			/// @brief プレイヤー
			Player* m_player = nullptr;
		};
	}
}