#include "stdafx.h"
#include "Player.h"

namespace {
	/// @brief プレイヤーのモデルファイルパス
	const char* PLAYER_TKM_FILEPATH = "Assets/modelData/character/HeroPBR.tkm";
	/// @brief プレイヤーのスケルトンファイルパス
	const char* PLAYER_TKS_FILEPATH = "Assets/modelData/character/HeroPBR.tks";
	/// @brief プレイヤーのミニマップ上のモデルファイルパス
	const char* PLAYER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/plMapModel.tkm";
	/// @brief プレイヤーのミニマップモデルのシェーダーファイルパス
	const char* PLAYER_MINIMAP_SHADER_FILEPATH = "Assets/shader/mapModel.fx";
	/// @brief 剣のモデルファイルパス
	const char* SWORD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Sword.tkm";
	/// @brief 盾のモデルファイルパス
	const char* SHIELD_MODEL_FILEPATH = "Assets/modelData/character/Hero_Shield.tkm";
	/// @brief 剣の位置を決めるボーンの名前
	const wchar_t* SWORD_POS_BONE_NAME = L"hand_l";
	/// @brief 盾の位置を決めるボーンの名前
	const wchar_t* SHIELD_POS_BONE_NAME = L"hand_r";
	/// @brief アニメーション補完率
	const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
	/// @brief プレイヤーの初期座標
	const Vector3 PLAYER_START_POS = { 0.0f,0.0f,500.0f };
	/// @brief ダメージから復帰するまでの時間
	const float PLAYER_DAMAGE_RETURN_TIME = 1.0f;
	/// @brief プレイヤーが無敵から元に戻るまでの時間
	const float PLAYER_INVINCIBLE_RETURN_TIME = 3.0f;
	/// @brief プレイヤーモデルの拡大率
	const Vector3 PLAYER_MODEL_SCALE = { 2.0f,2.0f,2.0f };
	/// @brief プレイヤーが落下したと判定する高度
	const float PLAYER_FALL_HEIGHT = -1000.0f;
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
			DeleteGO(m_swordModel);
			DeleteGO(m_shieldModel);
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
			m_playerEffect.Init(this);
			m_playerSound.Init(this);
			m_itemSlot.Init(this);

			//プレイヤーのモデルを初期化
			m_playerModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_playerModel->InitDeferrd(
				PLAYER_TKM_FILEPATH,
				true,
				PLAYER_TKS_FILEPATH,
				m_playerAnimation.GetAnimatonClip(),
				m_playerAnimation.GetAnimationNum()
			);
			m_playerModel->SetScale(PLAYER_MODEL_SCALE);

			//プレイヤーモデルの影を生成
			m_playerModel->CreateShadow();

			//装備モデルを生成
			m_swordModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_swordModel->InitDeferrd(SWORD_MODEL_FILEPATH,true);
			m_swordModel->CreateShadow();

			m_shieldModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_shieldModel->InitDeferrd(SHIELD_MODEL_FILEPATH,true);
			m_shieldModel->CreateShadow();

			//ミニマップ上のモデルを生成
			m_plMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_plMapModel->SetFxFilePath(PLAYER_MINIMAP_SHADER_FILEPATH);
			m_plMapModel->Init(PLAYER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);

			//ゲームシーンの情報を取得
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Player::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//ゲームシーンの状態に応じて処理を変える
			switch (m_gameScene->GetGameSceneState())
			{
				//ゲーム開始の処理中
			case enGameSceneStart: {
				//待機状態にする
				m_playerState = enPlayerIdle;
			}break;
				//ゲームプレイの処理中
			case enGameSceneInProgress: {
				//メンバクラスの処理を実行
				m_playerMove.Execution();
				m_playerAttack.Execute();
				m_qRot = m_playerRot.RotationExecution(m_playerMove.GetMoveSpssd());
				m_playerEffect.Execution();
				m_itemSlot.Execution();

				//ダメージ中の場合
				if (m_playerState == enPlayerDamage) {
					//ダメージの処理を実行
					DamageExecution();
				}
				//無敵中の場合
				if (m_invincibleFlag == true) {
					//無敵の処理を実行
					InvincibleExecution();
				}
			}break;
				//ゲームクリアの処理中
			case enGameSceneClear: {
				//待機状態にする
				m_playerState = enPlayerIdle;
			}break;
				//ゲームオーバーの処理中
			case enGameSceneOver: {
				//待機状態にする
				m_playerState = enPlayerIdle;
			}break;
			default:
				break;
			}

			//各種モデルの情報を更新
			m_playerAnimation.AnimationUpdate();
			m_playerModel->SetPosition(m_position);
			m_plMapModel->SetPosition(m_position);
			m_playerModel->SetRotation(m_qRot);
			m_plMapModel->SetRotation(m_qRot);
			m_playerModel->PlayAnimation(m_playerAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);
			m_playerModel->Execution();
			m_plMapModel->Execution();
			//装備モデルの更新
			SetWeapons();

			//音声の更新
			m_playerSound.Execution();
			
			//プレイヤーが落下したら…
			if (m_position.y < PLAYER_FALL_HEIGHT) {
				//初期位置に戻す
				m_position = PLAYER_START_POS;
				m_playerMove.SetPosition(m_position);
			}
		}

		void Player::DamageExecution()
		{
			//ダメージ中のタイマーを進める
			m_damageTimer += g_gameTime->GetFrameDeltaTime();
			m_invincibleFlag = true;

			//ダメージからの復帰時間を過ぎたら…
			if (m_damageTimer > PLAYER_DAMAGE_RETURN_TIME) {
				//プレイヤーを待機状態に戻す
				m_playerState = enPlayerIdle;
				m_damageTimer = 0.0f;
			}
		}

		void Player::InvincibleExecution()
		{
			//無敵状態のタイマーを進める
			m_invincibleTimer += g_gameTime->GetFrameDeltaTime();

			//無敵状態の終了時間を過ぎたら…
			if (m_invincibleTimer > PLAYER_INVINCIBLE_RETURN_TIME) {
				//プレイヤーを無敵状態から戻す
				m_invincibleFlag = false;
				m_invincibleTimer = 0.0f;
			}
		}

		void Player::SetWeapons()
		{
			//プレイヤーのスケルトン情報を取得
			Skeleton* heroSkeleton = m_playerModel->GetSkeleton();
			//剣のモデルの座標を設定するボーンの番号を入手
			int boneId = heroSkeleton->FindBoneID(SWORD_POS_BONE_NAME);
			//ボーンの番号から設定するボーンを入手
			Bone* hand = heroSkeleton->GetBone(boneId);
			//ボーンのワールド行列を入手
			Matrix boneMatrix = hand->GetWorldMatrix();
			//剣のモデルのワールド行列を設定
			m_swordModel->SetWorldMatrix(boneMatrix);
			m_swordModel->Execution();

			//盾のモデルの座標を設定するボーンの番号を入手
			boneId = heroSkeleton->FindBoneID(SHIELD_POS_BONE_NAME);
			//ボーンの番号から設定するボーンを入手
			hand = heroSkeleton->GetBone(boneId);
			//ボーンのワールド行列を入手
			boneMatrix = hand->GetWorldMatrix();
			//盾のモデルのワールド行列を設定
			m_shieldModel->SetWorldMatrix(boneMatrix);
			m_shieldModel->Execution();
		}
		
	}
}