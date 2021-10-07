#pragma once

class Game;
class Player;

namespace MainGame {

	/// @brief ゲーム中のカメラを制御するクラス
	class GameCamera : public IGameObject
	{
	public:
		GameCamera();
		~GameCamera();
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
	private:
		/// @brief カメラの回転
		void CameraRotation();
		/// @brief カメラの更新
		void CameraUpdate();
		/// @brief カメラリセット
		void CameraReset();

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

		/// @brief カメラの注視点からの距離
		Vector3 m_toCameraPos = g_vec3Zero;
		/// @brief 保存するカメラの注視点からの距離
		Vector3 m_oldToCameraPos = g_vec3Zero;
		
		/// @brief カメラのY軸回転
		Quaternion m_cameraYRot = g_quatIdentity;
		/// @brief カメラのY軸回転の角度
		float m_cameraYAngle = 0.0f;
		/// @brief カメラのY軸回転角度の量
		float m_cameraYAngeAmount = 0.0f;

		/// @brief カメラのX軸回転
		Quaternion m_cameraXRot = g_quatIdentity;

		Vector3 m_AxisX = g_vec3Zero;
		/// @brief カメラのX軸回転の角度
		float m_cameraXAngle = 0.0f;
		/// @brief カメラのX軸回転角度の量
		float m_cameraXAngeAmount = 0.0f;

		/// @brief カメラの速度
		float m_cameraVerocity = 0.0f;


		Player::Player* m_player = nullptr;
	};

}