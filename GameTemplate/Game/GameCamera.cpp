#include "stdafx.h"
#include "GameCamera.h"

namespace {
	/// @brief カメラの速度
	const float CAMERA_VELOCITY = 0.08f;
	/// @brief カメラの回転速度
	const float CAMERA_ROTATION_VELOCITY = 0.02f;
	/// @brief カメラの摩擦力
	const float TPS_CAMERA_FRICTION = 20.0f;

	const float FPS_CAMERA_FRICTION = 5.0f;
	/// @brief カメラの移動が止まる距離
	const float CAMERA_MOVE_STOP_DISTANCE = 0.01f;
}

namespace mainGame {
	GameCamera::GameCamera()
	{
		m_isInitd = false;

		//カメラの座標が注視点からどれだけ離れているか決める
		m_targetToCameraPos = { 0.0f,300.0f,-600.0f };

		m_playerToCameraPos = { 50.0f,70.0f,-100.0f };

		m_cameraToTargetPos = { 0.0f,0.0f,600.0f };
	}

	GameCamera::~GameCamera()
	{

	}

	void GameCamera::Init()
	{
		if (m_isInitd == true) {
			return;
		}
		m_player = FindGO<player::Player>(player::PLAYER_NAME);

		m_oldPlayerAngle = m_player->GetPlayerAngle();

		m_isInitd = true;
	}

	bool GameCamera::Start()
	{
		
		return true;
	}

	void GameCamera::Update()
	{
		
	}

	void GameCamera::Execution()
	{
		if (m_isInitd == false) {
			return;
		}
		
		switch (m_mode)
		{
		case enCameraModeTps: {
			TpsCameraUpdate();
		}break;
		case enCameraModeFps: {
			FpsCameraUpdate();
		}break;
		case enCameraModeNum: {

		}break;
		default:
			break;
		}

		//カメラの注視点と座標を渡す
		g_camera3D->SetTarget(m_cameraGazePoint);
		g_camera3D->SetPosition(m_cameraPos);
	}

	

	void GameCamera::TpsCameraUpdate()
	{
		//LB1でカメラリセット
		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			TpsCameraReset();
		}

		TpsCameraMove();
		TpsCameraRotation();

		if (g_pad[0]->IsTrigger(enButtonRB3)) {


			//X軸の記憶していた移動量で回転させる
			m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
			//ベクトルに回転を適用する
			m_cameraXRot.Apply(m_targetToCameraPos);
			//記憶していた移動量を0にする
			m_cameraXAngeAmount = 0.0f;

			//Y軸の記憶していた移動量で回転させる
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount);
			//ベクトルに回転を適用する
			m_cameraYRot.Apply(m_targetToCameraPos);

			m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngeAmount);

			////カメラの回転を適用する
			m_cameraYRot.Apply(m_cameraToTargetPos);
			m_cameraYRot.Apply(m_playerToCameraPos);

			//モードを切り替える
			m_mode = enCameraModeFps;
		}
	}

	void GameCamera::FpsCameraUpdate()
	{
		//LB1でカメラリセット
		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			
			FpsCameraReset();
		}

		FpsCameraMove();
		FpsCameraRotation();

		if (g_pad[0]->IsTrigger(enButtonRB3)) {

			FpsCameraReset();

			m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount);

			////カメラの回転を適用する
			m_cameraYRot.Apply(m_cameraToTargetPos);
			m_cameraYRot.Apply(m_playerToCameraPos);


			//Y軸の記憶していた移動量で回転させる
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngeAmount);
			//ベクトルに回転を適用する
			m_cameraYRot.Apply(m_targetToCameraPos);
			//モードを切り替える
			m_mode = enCameraModeTps;
		}
	}

	void GameCamera::TpsCameraMove()
	{
		//カメラの目標をプレイヤーの座標にする
		m_cameraTarget = m_player->GetPlayerPosition();

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
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / TPS_CAMERA_FRICTION;
		}

		//カメラ座標に目標の座標を渡す
		m_cameraMovePos = m_cameraTarget;

		//カメラの座標を目標から一定距離遠ざける
		m_cameraMovePos += m_targetToCameraPos;


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
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / TPS_CAMERA_FRICTION;
		}
	}

	void GameCamera::FpsCameraMove()
	{
		//カメラの移動目標をプレイヤーの少し後ろにする
		m_cameraMovePos = m_player->GetPlayerPosition() + m_playerToCameraPos;

		//カメラの目標をカメラの移動目標から前の座標にする
		m_cameraTarget = m_cameraMovePos + m_cameraToTargetPos;

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
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / FPS_CAMERA_FRICTION;
		}

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
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / FPS_CAMERA_FRICTION;
		}
	}

	void GameCamera::TpsCameraRotation()
	{
		//カメラの上方向とカメラの向きの外積でX方向の回転軸を決める
		m_AxisX.Cross(g_camera3D->GetUp(), m_targetToCameraPos * -1.0f);
		//正規化
		m_AxisX.Normalize();

		//Y軸回転
		//右スティック入力を受け取る
		m_cameraYAngle = g_pad[0]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

		//角度からカメラの回転を作成
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngle);

		//カメラの回転を適用する
		m_cameraYRot.Apply(m_targetToCameraPos);

		//回転角度を記憶しておく
		m_cameraYAngeAmount += m_cameraYAngle;

		//X軸回転
		//回転適用前のベクトルを記憶する
		Vector3 oldPos = m_targetToCameraPos;
		//右スティック入力を受け取る
		m_cameraXAngle = -g_pad[0]->GetRStickYF() * CAMERA_ROTATION_VELOCITY;
		//受け取った値で回転
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//回転をベクトルに適用
		m_cameraXRot.Apply(m_targetToCameraPos);

		//回転適用後のベクトルを受け取る
		Vector3 toCameraPos = m_targetToCameraPos;

		//正規化して大きさ1のベクトルにする
		toCameraPos.Normalize();

		//Y軸に大きく振れすぎていたら…
		if (toCameraPos.y > 0.9f || toCameraPos.y < 0.0f) {
			//回転適用前のベクトルに戻す
			m_targetToCameraPos = oldPos;
			//カメラアングルの移動量を0にする
			m_cameraXAngle = 0.0f;
		}

		//回転を記憶しておく
		m_cameraXAngeAmount += m_cameraXAngle;

	}

	void GameCamera::FpsCameraRotation()
	{

		//カメラの上方向とカメラX方向の回転軸を決める
		m_AxisX.Cross(g_camera3D->GetUp(), m_cameraToTargetPos);
		//正規化
		m_AxisX.Normalize();

		//Y軸回転
		//右スティック入力を受け取る
		m_cameraYAngle = g_pad[0]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

		//角度からカメラの回転を作成
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngle);

		//カメラの回転を適用する
		m_cameraYRot.Apply(m_playerToCameraPos);

		m_cameraYRot.Apply(m_cameraToTargetPos);

		//回転角度を記憶しておく
		m_cameraYAngeAmount += m_cameraYAngle;

		//X軸回転
		//回転適用前のベクトルを記憶する
		Vector3 oldPos = m_cameraToTargetPos;
		//右スティック入力を受け取る
		m_cameraXAngle = -g_pad[0]->GetRStickYF() * CAMERA_ROTATION_VELOCITY;
		//受け取った値で回転
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//回転をベクトルに適用
		m_cameraXRot.Apply(m_cameraToTargetPos);

		//回転適用後のベクトルを受け取る
		Vector3 toCameraPos = m_cameraToTargetPos;

		//正規化して大きさ1のベクトルにする
		toCameraPos.Normalize();

		//Y軸に大きく振れすぎていたら…
		if (toCameraPos.y > 0.5f || toCameraPos.y < -0.5f) {
			//回転適用前のベクトルに戻す
			m_cameraToTargetPos = oldPos;
			//カメラアングルの移動量を0にする
			m_cameraXAngle = 0.0f;
		}

		//回転を記憶しておく
		m_cameraXAngeAmount += m_cameraXAngle;
	}

	void GameCamera::TpsCameraReset()
	{
		//X軸の記憶していた移動量で回転させる
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//ベクトルに回転を適用する
		m_cameraXRot.Apply(m_targetToCameraPos);
		//記憶していた移動量を0にする
		m_cameraXAngeAmount = 0.0f;

		//プレイヤーの角度変化量と現在の角度変化量を使って必要な角度変化量を求める
		float angleAmount = m_player->GetAngleAmount() - m_cameraYAngeAmount;

		//計算した角度変化量で回転させる
		m_cameraYRot.SetRotation(g_camera3D->GetUp(),angleAmount);
		//ベクトルに回転を適用する
		m_cameraYRot.Apply(m_targetToCameraPos);
		//現在の角度変化量に計算した角度変化量を加算する
		m_cameraYAngeAmount += angleAmount;

		
		//現在のプレイヤーの角度を記憶しておく
		m_oldPlayerAngle = m_player->GetPlayerAngle();

	}

	void GameCamera::FpsCameraReset()
	{
		//X軸の記憶していた移動量で回転させる
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//ベクトルに回転を適用する
		m_cameraXRot.Apply(m_cameraToTargetPos);
		//記憶していた移動量を0にする
		m_cameraXAngeAmount = 0.0f;
	}
}