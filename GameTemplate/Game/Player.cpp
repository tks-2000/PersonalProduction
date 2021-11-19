#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief プレイヤーのモデルファイルパス
	const char* PLAYER_TKM_FILEPATH = "Assets/modelData/unityChan/unityChan.tkm";
	/// @brief プレイヤーのスケルトンファイルパス
	const char* PLAYER_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";

	const char* PLAYER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/plMapModel.tkm";
	/// @brief アニメーション補完率
	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
	/// @brief プレイヤーの初期座標
	const Vector3 PLAYER_START_POS = { 0.0f,500.0f,0.0f };

}
namespace mainGame {
	namespace player {
		Player::Player()
		{
			m_isInitd = false;
		}

		Player::~Player()
		{
			DeleteGO(m_playerModel);
			DeleteGO(m_plMapModel);
		}

		void Player::Init()
		{
			if (m_isInitd == true) {
				return;
			}

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
				render::model::enMainRenderTarget,
				PLAYER_TKS_FILEPATH,
				m_playerAnimation.GetAnimatonClip(),
				m_playerAnimation.GetAnimationNum(),
				enModelUpAxisY
			);

			m_plMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_plMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_plMapModel->Init(PLAYER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);

			//プレイヤーモデルの影を生成
			m_playerModel->CreateShadow();

			m_game = FindGO<Game>(GAME_NAME);

			m_isInitd = true;
		}

		bool Player::Start()
		{
			

			return true;
		}

		void Player::Update()
		{
			
		}

		void Player::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			switch (m_game->GetGameState())
			{
			case enGameStart: {
				GameStartExecution();
			}break;
			case enGameInProgress: {
				GameInProgressExecution();
			}break;
			case enGameClear: {
				GameClearExecution();
			}break;
			case enGameOver: {
				GameOverExecution();
			}break;
			default:
				break;
			}

			m_playerAnimation.AnimationUpdate();

			m_playerModel->SetPosition(m_position);

			m_plMapModel->SetPosition(m_position);

			m_playerModel->SetRotation(m_qRot);

			m_plMapModel->SetRotation(m_qRot);

			m_playerModel->PlayAnimation(m_playerAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_playerModel->Execution();

			m_plMapModel->Execution();
		}

		void Player::GameStartExecution()
		{

		}

		void Player::GameInProgressExecution()
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

		
				
			

			//データメンバのクラスを更新する
			m_playerAttack.Execute();

			m_qRot = m_playerRot.RotationExecution(m_playerMove.GetMoveSpssd());

		}

		void Player::GameClearExecution()
		{
			
		}

		void Player::GameOverExecution()
		{
			
		}
	}
}