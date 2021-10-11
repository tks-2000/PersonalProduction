#include "stdafx.h"
#include "GameCamera.h"

namespace {
	/// @brief カメラの速度
	const float CAMERA_VELOCITY = 0.04f;
	/// @brief カメラの回転速度
	const float CAMERA_ROTATION_VELOCITY = 0.02f;
	/// @brief カメラの摩擦力
	const float CAMERA_FRICTION = 20.0f;
	/// @brief カメラの移動が止まる距離
	const float CAMERA_MOVE_STOP_DISTANCE = 0.01f;
}

namespace MainGame {
	GameCamera::GameCamera()
	{
		//カメラの座標が注視点からどれだけ離れているか決める
		m_toCameraPos = { 0.0f,300.0f,-500.0f };
	}

	GameCamera::~GameCamera()
	{

	}

	bool GameCamera::Start()
	{
		m_player = FindGO<Player::Player>(Player::PLAYER_NAME);
		return true;
	}

	void GameCamera::Update()
	{
		
	}

	void GameCamera::Execution()
	{
		//カメラの上方向とカメラの向きの外積でX方向の回転軸を決める
		m_AxisX.Cross(g_camera3D->GetUp(), m_toCameraPos * -1.0f);
		//正規化
		m_AxisX.Normalize();

		//LB1でカメラリセット
		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			CameraReset();
		}

		CameraUpdate();
	}

	void GameCamera::CameraRotation()
	{
		//Y軸回転
		//右スティック入力を受け取る
		m_cameraYAngle = g_pad[0]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

		//角度からカメラの回転を作成
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngle);

		//カメラの回転を適用する
		m_cameraYRot.Apply(m_toCameraPos);

		//回転角度を記憶しておく
		m_cameraYAngeAmount += m_cameraYAngle;
		
		//X軸回転
		//回転適用前のベクトルを記憶する
		m_oldToCameraPos = m_toCameraPos;
		//右スティック入力を受け取る
		m_cameraXAngle = -g_pad[0]->GetRStickYF() * CAMERA_VELOCITY;
		//受け取った値で回転
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//回転をベクトルに適用
		m_cameraXRot.Apply(m_toCameraPos);

		//回転適用後のベクトルを受け取る
		Vector3 toCameraPos = m_toCameraPos;

		//正規化して大きさ1のベクトルにする
		toCameraPos.Normalize();

		//Y軸に大きく振れすぎていたら…
		if (toCameraPos.y > 0.9f || toCameraPos.y < 0.0f) {
			//回転適用前のベクトルに戻す
			m_toCameraPos = m_oldToCameraPos;
			//カメラアングルの移動量を0にする
			m_cameraXAngle = 0.0f;
		}
		
		//回転を記憶しておく
		m_cameraXAngeAmount += m_cameraXAngle;
		
	}

	void GameCamera::CameraUpdate()
	{
		//カメラの注視点と目標の距離を計算する
		m_cameraTargetDistance = m_cameraTarget - m_cameraGazePoint;

		//距離が停止距離以下なら…
		if (m_cameraTargetDistance.Length() < CAMERA_MOVE_STOP_DISTANCE) {
			//注視点を目標の座標に設定
			m_cameraGazePoint = m_cameraTarget;
		}
		//そうでないなら…
		else {
			//カメラの注視点からカメラの目標へのベクトルを移動方向に設定
			m_cameraGazePointMoveDirection = m_cameraTargetDistance;
			//正規化して方向ベクトルにする
			m_cameraGazePointMoveDirection.Normalize();
			//注視点に計算した移動量を加算する
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / CAMERA_FRICTION;
		}

		//カメラ座標に目標の座標を渡す
		m_cameraMovePos = m_cameraTarget;

		//カメラの座標を目標から一定距離遠ざける
		m_cameraMovePos += m_toCameraPos;


		//カメラの座標とカメラの移動地点の距離を計算する
		m_cameraMoveDistance = m_cameraMovePos - m_cameraPos;

		//距離が停止距離以下なら…
		if (m_cameraMoveDistance.Length() < CAMERA_MOVE_STOP_DISTANCE) {
			//カメラの座標にカメラの移動地点の座標を渡す
			m_cameraPos = m_cameraMovePos;
		}
		else {
			//カメラの座標からカメラの移動地点へのベクトルをカメラの移動方向にする
			m_cameraMoveDirection = m_cameraMoveDistance;
			//正規化して方向ベクトルにする
			m_cameraMoveDirection.Normalize();
			//カメラの座標に計算した移動量を加算する
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / CAMERA_FRICTION;
		}

		//カメラを回転させる
		CameraRotation();

		//カメラの注視点と座標を渡す
		g_camera3D->SetTarget(m_cameraGazePoint);
		g_camera3D->SetPosition(m_cameraPos);

		/*g_camera3D->SetTarget(m_cameraPos);
		g_camera3D->SetPosition(m_cameraGazePoint);*/
	}

	void GameCamera::CameraReset()
	{
		//X軸の記憶していた移動量で回転させる
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//ベクトルに回転を適用する
		m_cameraXRot.Apply(m_toCameraPos);
		//記憶していた移動量を0にする
		m_cameraXAngeAmount = 0.0f;

		
		//Y軸の記憶していた移動量で回転させる
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount + m_player->GetAngleAmount());
		//ベクトルに回転を適用する
		m_cameraYRot.Apply(m_toCameraPos);
		//記憶していた移動量を0にする
		m_cameraYAngeAmount = 0.0f;

		m_player->ResetAngle();
	}
}