#pragma once

class Game;
class Player;

namespace mainGame {

	enum EnCameraMode {
		enCameraModeTps,
		enCameraModeFps,
		enCameraModeNum
	};

	/// @brief ゲーム中のカメラを制御するクラス
	class GameCamera : public IGameObject
	{
	public:
		GameCamera();
		~GameCamera();

		void Init();
		bool Start();
		void Update();

		
		/// @brief ゲームカメラの追従目標を設定
		/// @param target ゲームカメラに設定する追従目標の座標
		void SetCameraTarget(const Vector3& target) { m_cameraTarget = target; }

		/// @brief ゲームカメラの上方向を入手
		/// @return ゲームカメラの上方向のconst参照
		const Vector3& GetCameraUp() { return g_camera3D->GetUp(); }

		/// @brief ゲームカメラの前方向を入手
		/// @return ゲームカメラの前方向のconst参照
		const Vector3& GetCameraForward() { return g_camera3D->GetForward(); }

		/// @brief ゲームカメラの右方向を入手
		/// @return ゲームカメラの右方向のconst参照
		const Vector3& GetCameraRight() { return g_camera3D->GetRight(); }

		/// @brief ゲームカメラの座標を入手
		/// @return ゲームカメラの座標のconst参照
		const Vector3& GetCameraPos() { return m_cameraPos; }

		const EnCameraMode& GetCameraMode() { return m_mode; }

		const float GetCameraYAngleAmount() { return m_cameraYAngeAmount; }

		const Vector3& GetCameraAxisX() { return m_AxisX; }

		const float GetCameraXAngleAmount() { return m_cameraXAngeAmount; }

		const Vector3& GetCameraToTargetPos() { return m_cameraToTargetPos; }

		/// @brief 実行
		void Execution();

	private:
		

		void FpsCameraRotation();
		/// @brief カメラの更新
		void TpsCameraUpdate();

		void FpsCameraUpdate();

		void TpsCameraMove();

		void FpsCameraMove();

		/// @brief カメラの回転
		void TpsCameraRotation();

		/// @brief カメラリセット
		void TpsCameraReset();

		void FpsCameraReset();

		bool m_isInitd = false;

		/// @brief カメラの座標
		Vector3 m_cameraPos = g_vec3Zero;
		/// @brief カメラの移動座標
		Vector3 m_cameraMovePos = g_vec3Zero;
		/// @brief カメラの座標と移動座標との距離
		Vector3 m_cameraMoveDistance = g_vec3Zero;
		/// @brief カメラの移動方向
		Vector3 m_cameraMoveDirection = g_vec3Zero;


		/// @brief カメラの注視点
		Vector3 m_cameraGazePoint = g_vec3Zero;
		/// @brief カメラの目標
		Vector3 m_cameraTarget = g_vec3Zero;
		/// @brief カメラの注視点と目標の距離
		Vector3 m_cameraTargetDistance = g_vec3Zero;
		/// @brief カメラの注視点の移動方向
		Vector3 m_cameraGazePointMoveDirection;

		/// @brief カメラの注視点からカメラの座標への距離
		Vector3 m_targetToCameraPos = g_vec3Zero;
		/// @brief カメラから注視点への距離
		Vector3 m_cameraToTargetPos = g_vec3Zero;
		/// @brief プレイヤーからカメラの座標への距離
		Vector3 m_playerToCameraPos = g_vec3Zero;
		
		/// @brief カメラのY軸回転
		Quaternion m_cameraYRot = g_quatIdentity;
		/// @brief カメラのY軸回転の角度
		float m_cameraYAngle = 0.0f;
		/// @brief カメラのY軸回転角度の量
		float m_cameraYAngeAmount = 0.0f;
		/// @brief 記憶するカメラのY軸回転角度の量
		float m_oldCameraYAngleAmount = 0.0f;

		/// @brief カメラのX軸回転
		Quaternion m_cameraXRot = g_quatIdentity;
		/// @brief カメラのX回転の軸
		Vector3 m_AxisX = g_vec3Zero;
		/// @brief カメラのX軸回転の角度
		float m_cameraXAngle = 0.0f;
		/// @brief カメラのX軸回転角度の量
		float m_cameraXAngeAmount = 0.0f;

		float m_oldPlayerAngle = 0.0f;

		EnCameraMode m_mode = enCameraModeTps;

		/// @brief プレイヤー
		player::Player* m_player = nullptr;

	};

}