#include "stdafx.h"
#include "Player.h"

namespace {
	const char* UNITYCHAN_TKM_FILEPATH = "Assets/modelData/unityChan.tkm";

	const char* UNITYCHAN_TKS_FILEPATH = "Assets/modelData/unityChan.tks";

	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
}
namespace MainGame {
	namespace Player {
		Player::Player()
		{
			
		}

		Player::~Player()
		{

		}

		bool Player::Start()
		{
			m_playerMove.Init();
			m_playerAnimation.Init();

			m_playerModel = NewGO<Render::SkinModelRender>(PRIORITY_VERYLOW);
			m_playerModel->Init(
				UNITYCHAN_TKM_FILEPATH,
				UNITYCHAN_TKS_FILEPATH,
				m_playerAnimation.GetAnimatonClip(),
				m_playerAnimation.GetAnimationNum(),
				enModelUpAxisY
			);
			m_playerModel->CreateShadow();
			return true;
		}

		void Player::Update()
		{
			m_position = m_playerMove.MoveExecute();
			m_playerModel->SetPosition(m_position);
			m_qRot = m_playerRot.RotationUpdate(m_playerMove.GetMoveSpssd());
			m_playerModel->SetRotation(m_qRot);
			m_playerAnimation.AnimationUpdate();
			m_playerModel->PlayAnimation(m_playerAnimation.GetAnimationState(),ANIMATION_COMPLEMENTARY_RATE);
		}
	}
}