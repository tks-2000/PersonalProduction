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

			/// @brief 実行
			void Execution();

			/// @brief 待機中の処理を実行
			void IdleExecute();

			/// @brief 移動を実行
			/// @param velocity 移動する速度
			void MoveExecute(const float velocity);

			/// @brief 移動方向を取得
			/// @return 移動方向のconst参照
			const Vector3& GetMoveDirection() { return m_moveDirection; }

			/// @brief 移動速度を取得
			/// @return 移動速度のconst参照
			const Vector3& GetMoveSpssd() { return m_moveSpeed; }

			/// @brief 移動速度を設定
			/// @param speed 設定する移動速度
			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

			/// @brief 加算する速度を設定
			/// @param addVerocity 設定する加算速度
			void SetAddVerocity(const float addVerocity) { m_addVerocity = addVerocity; }

			/// @brief 座標を設定
			/// @param pos 設定する座標
			void SetPosition(const Vector3& pos) { m_position = pos; m_charaCon.SetPosition(m_position); }
		private:

			/// @brief 摩擦力を適用
			/// @param speed 移動速度
			/// @return 摩擦力を加えた速度
			const Vector3& ApplyFriction(Vector3& speed);

			/// @brief 初期化しているかどうかのフラグ
			bool m_isInitd = false;
			/// @brief 左スティックの横入力
			float m_LStickX = 0.0f;
			/// @brief 左スティックの縦入力
			float m_LStickY = 0.0f;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 加算速度
			float m_addVerocity = 0.0f;
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