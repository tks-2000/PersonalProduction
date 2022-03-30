#include "stdafx.h"
#include "PlayerAnimation.h"

namespace mainGame {
	namespace player {

		Animation::Animation()
		{
			//未初期化で開始
			m_isInitd = false;

			//アニメーションクリップをロード
			m_playerAnimationClip[enPlayerAnimationIdle].Load("Assets/animData/hero/Hero_Idle.tka");
			m_playerAnimationClip[enPlayerAnimationIdle].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationWark].Load("Assets/animData/hero/Hero_Walk.tka");
			m_playerAnimationClip[enPlayerAnimationWark].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationRun].Load("Assets/animData/hero/Hero_Run.tka");
			m_playerAnimationClip[enPlayerAnimationRun].SetLoopFlag(true);
			m_playerAnimationClip[enPlayerAnimationAttack].Load("Assets/animData/hero/Hero_Attack.tka");
			m_playerAnimationClip[enPlayerAnimationAttack].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationClear].Load("Assets/animData/hero/Hero_Clear.tka");
			m_playerAnimationClip[enPlayerAnimationClear].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationDamage].Load("Assets/animData/hero/Hero_Damage.tka");
			m_playerAnimationClip[enPlayerAnimationDamage].SetLoopFlag(false);
			m_playerAnimationClip[enPlayerAnimationKneelDown].Load("Assets/animData/hero/Hero_Down.tka");
			m_playerAnimationClip[enPlayerAnimationKneelDown].SetLoopFlag(false);
		}

		Animation::~Animation()
		{

		}

		void Animation::Init(Player* pl)
		{
			//データを取得
			m_player = pl;
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Animation::AnimationUpdate()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//ゲームシーンの状態によって再生するアニメーションを変える
			switch (m_gameScene->GetGameSceneState())
			{
				//ゲーム開始時
			case enGameSceneStart: {
				//待機アニメーションを再生
				m_playerAnimState = enPlayerAnimationIdle;
			}break;
				//ゲーム実行中
			case enGameSceneInProgress: {
				
				//プレイヤーの状態によって再生するアニメーションを変える
				switch (m_player->GetPlayerStatus())
				{
					//待機中
				case enPlayerIdle: {
					//待機アニメーションを再生
					m_playerAnimState = enPlayerAnimationIdle;
				}break;
					//歩行中
				case enPlayerWark: {
					//歩行アニメーションを再生
					m_playerAnimState = enPlayerAnimationWark;
				}break;
					//走行中
				case enPlayerRun: {
					//走行アニメーションを再生
					m_playerAnimState = enPlayerAnimationRun;
				}break;
					//攻撃中
				case enPlayerAttack: {
					//攻撃アニメーションを再生
					m_playerAnimState = enPlayerAnimationAttack;
				}break;
					//ダメージ中
				case enPlayerDamage: {
					//ダメージアニメーションを再生
					m_playerAnimState = enPlayerAnimationDamage;
				}break;
				default:
					break;
				}
			}break;
				//ゲームクリア時
			case enGameSceneClear: {
				//クリアのアニメーションを再生
				m_playerAnimState = enPlayerAnimationClear;
			}break;
				//ゲームオーバー時
			case enGameSceneOver: {
				//ゲームオーバーのアニメーションを再生
				m_playerAnimState = enPlayerAnimationKneelDown;
			}
			default:
				break;
			}
		}
		
	}
}