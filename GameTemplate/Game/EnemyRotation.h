#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief エネミーのの回転を制御するクラス
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			/// @brief 初期化
			/// @param enemy 処理を適用する敵のアドレス
			void Init(Enemy* enemy);

			/// @brief 移動速度から回転を設定
			/// @param speed 回転させたい敵の移動速度
			/// @return 移動速度から作り出した回転クォータニオン
			void RotationExecute();

			/// @brief 向いている方向を入手
			/// @return 方向ベクトルのconst参照
			const Vector3& GetDirection() const { return m_direction; }

			/// @brief 様子を見始める
			void StartSeeTheSituation();

			/// @brief 様子を見終わる
			void EndSeeTheSituation();

			/// @brief 回転クォータニオンを入手
			/// @return 回転クォータニオンのconst参照
			const Quaternion& GetRotation() const { return m_qRot; }

		private:
			/// @brief 様子を見る処理の実行
			void ExecuteSeeTheSituation();
			
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 方向
			Vector3 m_direction = g_vec3Zero;
			/// @brief 以前の方向
			Vector3 m_oldDirection = g_vec3Zero;
			/// @brief 様子を見る方向
			Vector3 m_seeTheSituationDir = g_vec3Zero;
			/// @brief 反対の様子を見る方向
			Vector3 m_reverseSeeTheSituationDir = g_vec3Zero;
			/// @brief 様子を見る時間のタイマー
			float m_seeTheSituationTimer = 0.0f;
			/// @brief 回転クォータニオン
			Quaternion m_qRot = g_quatIdentity;
			/// @brief 角度
			float m_angle = 0.0f;
			/// @brief 変化する前の角度
			float m_oldAngle = 0.0f;
			/// @brief 角度の変化量
			float m_angleAmount = 0.0f;
			/// @brief 敵クラス
			Enemy* m_enemy = nullptr;
		};
	}
}
