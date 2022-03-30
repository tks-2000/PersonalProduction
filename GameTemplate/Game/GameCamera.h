#pragma once

class Game;
class Player;
class MiniMap;

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

		/// @brief 初期化
		void Init();
		bool Start();
		void Update();

		/// @brief カメラの追従目標を取得
		/// @return カメラの追従目標のconst参照
		const Vector3& GetCameraTarget() const { return m_cameraTarget; }
		
		/// @brief ゲームカメラの追従目標を設定
		/// @param target ゲームカメラに設定する追従目標の座標
		void SetCameraTarget(const Vector3& target) { m_cameraTarget = target; }

		/// @brief ゲームカメラの上方向を入手
		/// @return ゲームカメラの上方向のconst参照
		const Vector3& GetCameraUp() const { return g_camera3D->GetUp(); }

		/// @brief ゲームカメラの前方向を入手
		/// @return ゲームカメラの前方向のconst参照
		const Vector3& GetCameraForward() const { return g_camera3D->GetForward(); }

		/// @brief ゲームカメラの右方向を入手
		/// @return ゲームカメラの右方向のconst参照
		const Vector3& GetCameraRight() const { return g_camera3D->GetRight(); }

		/// @brief ゲームカメラの座標を入手
		/// @return ゲームカメラの座標のconst参照
		const Vector3& GetCameraPos() const { return m_cameraPos; }

		/// @brief カメラのY軸回転クォータニオンを取得
		/// @return Y軸回転クォータニオンのconst参照
		const Quaternion& GetCameraYRot() const { return m_cameraYRot; }

		/// @brief カメラのモードを取得
		/// @return カメラモードのステート
		const EnCameraMode& GetCameraMode() { return m_mode; }

		/// @brief カメラのY軸回転角度を取得
		/// @return カメラのY軸回転角度
		const float GetCameraYAngleAmount() const { return m_cameraYAngeAmount; }

		/// @brief カメラのX軸を取得
		/// @return カメラのX軸ベクトル
		const Vector3& GetCameraAxisX() const { return m_AxisX; }

		/// @brief カメラのX軸回転角度を取得
		/// @return カメラのX軸回転角度
		const float GetCameraXAngleAmount() const { return m_cameraXAngeAmount; }

		/// @brief Fpsカメラの座標から注視点への座標を取得
		/// @return Fpsカメラの座標から注視点への座標のconst参照
		const Vector3& GetCameraToTargetPos() { return m_cameraToTargetPos; }

		/// @brief カメラの注視点の座標を取得
		/// @return カメラの注視点の座標のconst参照
		const Vector3& GetCameraGazePointPos() { return m_cameraGazePoint; }

		/// @brief カメラの摩擦力を取得
		/// @return カメラの摩擦力
		const float GetCameraFriction() const { return m_cameraFriction; }

		/// @brief カメラの移動停止距離を取得
		/// @return カメラの移動停止距離
		const float GetCameraMoveStopDistance() const { return m_cameraMoveStopDistance; }

		/// @brief 実行
		void Execution();

	private:
		

		/// @brief Tpsカメラの更新
		void TpsCameraUpdate();

		/// @brief Fpsカメラの更新
		void FpsCameraUpdate();

		/// @brief Tpsカメラの移動
		void TpsCameraMove();

		/// @brief Fpsカメラの移動
		void FpsCameraMove();

		/// @brief Tpsカメラの回転
		void TpsCameraRotation();

		/// @brief Fpsカメラの回転
		void FpsCameraRotation();

		/// @brief Tpsカメラリセット
		void TpsCameraReset();

		/// @brief Fpsカメラリセット
		void FpsCameraReset();

		/// @brief 初期化フラグ
		bool m_isInitd = false;
		/// @brief カメラの座標
		Vector3 m_cameraPos = g_vec3Zero;
		/// @brief カメラの移動座標
		Vector3 m_cameraMovePos = g_vec3Zero;
		/// @brief カメラの座標と移動座標との距離
		Vector3 m_cameraMoveDistance = g_vec3Zero;
		/// @brief カメラの移動方向
		Vector3 m_cameraMoveDirection = g_vec3Zero;
		/// @brief カメラの摩擦力
		float m_cameraFriction = 0.0f;
		/// @brief カメラの移動停止距離
		float m_cameraMoveStopDistance = 0.0f;

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
		/// @brief カメラの座標からカメラの注視点への距離
		Vector3 m_cameraToTargetPos = g_vec3Zero;
		/// @brief プレイヤーからカメラの座標への距離
		Vector3 m_playerToCameraPos = g_vec3Zero;
		
		/// @brief カメラのY軸回転
		Quaternion m_cameraYRot = g_quatIdentity;
		/// @brief カメラのY軸回転の角度
		float m_cameraYAngle = 0.0f;
		/// @brief カメラのY軸回転角度の量
		float m_cameraYAngeAmount = 0.0f;

		/// @brief カメラのX軸回転
		Quaternion m_cameraXRot = g_quatIdentity;
		/// @brief カメラのX回転の軸
		Vector3 m_AxisX = g_vec3Zero;
		/// @brief カメラのX軸回転の角度
		float m_cameraXAngle = 0.0f;
		/// @brief カメラのX軸回転角度の量
		float m_cameraXAngeAmount = 0.0f;

		/// @brief 記憶するのプレイヤーの角度
		float m_oldPlayerAngle = 0.0f;

		/// @brief カメラのステート
		EnCameraMode m_mode = enCameraModeTps;

		/// @brief プレイヤー
		player::Player* m_player = nullptr;

		/// @brief UI
		ui::GameUI* m_gameUI = nullptr;

		/// @brief 影
		render::shadow::Shadow* m_shadow = nullptr;
	};

}