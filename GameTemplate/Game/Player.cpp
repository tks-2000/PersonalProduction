#include "stdafx.h"
#include "Player.h"

namespace {
	const char* PLAYER_TKM_FILEPATH = "Assets/modelData/unityChan/unityChan.tkm";

	const char* PLAYER_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";

	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;

	const Vector3 PLAYER_START_POS = { 0.0f,500.0f,0.0f };

}
namespace mainGame {
	namespace player {
		Player::Player()
		{
			
		}

		Player::~Player()
		{

		}

		bool Player::Start()
		{
			m_position = PLAYER_START_POS;
			//データメンバクラスを初期化
			m_playerMove.Init();
			m_playerAnimation.Init();

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