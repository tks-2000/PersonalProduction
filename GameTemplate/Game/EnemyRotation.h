#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief 敵の回転を制御するクラス
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
			const Quaternion& RotationExecute(const Vector3& speed);
		private:
			
			/// @brief 初期化フラグ
			bool m_isInitd = false;
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
