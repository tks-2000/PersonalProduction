#include "stdafx.h"
#include "Player.h"

namespace {
	const char* PLAYER_TKM_FILEPATH = "Assets/modelData/unityChan.tkm";

	const char* PLAYER_TKS_FILEPATH = "Assets/modelData/unityChan.tks";

	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
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
			//データメンバのクラスを更新する
			m_position = m_playerMove.MoveExecute();

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