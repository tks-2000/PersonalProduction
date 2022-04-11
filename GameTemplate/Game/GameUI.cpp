#include "stdafx.h"
#include "GameUI.h"

namespace mainGame {
	namespace ui {
		/// @brief ゲームクリアの画像のファイルパス
		const char* GAME_CLEAR_SPRITE_FILEPATH = "Assets/Image/GAMECLEAR.dds";
		/// @brief ゲームオーバーの画像のファイルパス
		const char* GAME_OVER_SPRITE_FILEPATH = "Assets/Image/GAMEOVER.dds";
		/// @brief ゲーム終了の画像の横幅
		const int GAME_END_SPRITE_WIDTH = 1000;
		/// @brief ゲーム終了の画像の縦幅
		const int GAME_END_SPRITE_HEIGHT = 200;

		GameUI::GameUI()
		{

		}

		GameUI::~GameUI()
		{
			//ゲーム終了時の画像を削除
			DeleteGO(m_gameEndSprite);
		}

		void GameUI::Init()
		{
			//全てのUIを初期化
			m_oenedItem.Init();
			m_baseEndurance.Init();
			m_timeLimit.Init();
			m_remainingBullets.Init();
			m_miniMap.Init();
			
			//終了時に表示する画像を作成
			m_gameEndSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			//使用する情報を持って来る
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void GameUI::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//全てのUIの処理を実行
			m_oenedItem.Execution();
			m_baseEndurance.Execution();
			m_timeLimit.Execution();
			m_remainingBullets.Execution();
			m_miniMap.Execution();
			
			//終了時の画像を出現させておらず、ゲームシーンのステートがクリアかオーバーになっていたら…
			if (m_gameEndSpriteFlag == false &&
				m_gameScene->GetGameSceneState() == enGameSceneClear ||
				m_gameScene->GetGameSceneState() == enGameSceneOver
				) 
			{
				//終了時の画像を表示
				DisplayGameEndSprite();
			}

			//終了時の画像を表示している場合…
			if (m_gameEndSpriteFlag == true) {
				//終了時の処理を行う
				GameEndExecution();
			}
		}

		

		void GameUI::DisplayGameEndSprite()
		{
			//ゲームシーンのステートがクリアの場合
			if (m_gameScene->GetGameSceneState() == enGameSceneClear) {
				//ゲームクリアの画像を表示
				m_gameEndSprite->Init(GAME_CLEAR_SPRITE_FILEPATH, GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}

			//ゲームシーンのステートがオーバーの場合
			if (m_gameScene->GetGameSceneState() == enGameSceneOver) {
				//ゲームオーバーの画像を表示
				m_gameEndSprite->Init(GAME_OVER_SPRITE_FILEPATH, GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}

			//ゲーム終了時の画像表示フラグを立てる
			m_gameEndSpriteFlag = true;
		}

		

		void GameUI::GameEndExecution()
		{
			//ゲーム終了時に出現する画像の処理を実行
			m_gameEndSprite->Execute();

			//全てのUIを非表示にする
			m_oenedItem.HideUI();
			m_baseEndurance.HIdeUI();
			m_remainingBullets.HideUI();
			m_timeLimit.HideUI();
			m_miniMap.HideUI();
		}
	}
}