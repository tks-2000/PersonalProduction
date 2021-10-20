#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief プレイヤーのモデルファイルパス
	const char* PLAYER_TKM_FILEPATH = "Assets/modelData/unityChan/unityChan.tkm";
	/// @brief プレイヤーのスケルトンファイルパス
	const char* PLAYER_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
	/// @brief アニメーション補完率
	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
	/// @brief プレイヤーの初期座標
	const Vector3 PLAYER_START_POS = { 0.0f,500.0f,0.0f };

}
namespace mainGame {
	namespace player {
		Player::Player()
		{
			
		}

		Player::~Player()
		{
			DeleteGO(m_playerModel);
		}

		bool Player::Start()
		{
			//初期位置を設定
			m_position = PLAYER_START_POS;

			//データメンバクラスを初期化
			m_playerMove.Init(this);
			m_playerRot.Init(this);
			m_playerAnimation.Init(this);
			m_playerAttack.Init(this);

			//プレイヤーのモデルを初期化
			m_playerModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_playerModel->Init(
				PLAYER_TKM_FILEPATH,
				PLAYER_TKS_FILEPATH,
				m_playerAnimation.GetAnimatonClip(),
				m_playerAnimation.GetAnimationNum(),
				enModelUpAxisY
			);

			//プレイヤーモデルの影を生成
			m_playerModel->CreateShadow();

			return true;
		}

		void Player::Update()
		{
			
		}

		void Player::Execution()
		{
			//プレイヤーの状態によって処理を分ける
			switch (m_playerState) {
			case enPlayerIdle: {
				m_position = m_playerMove.IdleExecute(m_position);
			}break;
			case enPlayerWark: {
				m_position = m_playerMove.MoveExecute(m_position);
			}break;
			case enPlayerRun: {

			}break;
			case enPlayerDamage: {

			}break;
			}

			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_playerAttack.Execute();
			}

			//データメンバのクラスを更新する
			m_qRot = m_playerRot.RotationUpdate(m_playerMove.GetMoveSpssd());

			m_playerAnimation.AnimationUpdate();

			//プレイヤーモデルに更新した情報を適用
			m_playerModel->SetPosition(m_position);

			m_playerModel->SetRotation(m_qRot);

			m_playerModel->PlayAnimation(m_playerAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_playerModel->Execution();
		}
	}
}