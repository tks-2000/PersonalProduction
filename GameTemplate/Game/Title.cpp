#include "stdafx.h"
#include "Title.h"
namespace mainGame {
	namespace title {
		/// @brief タイトルの画像の横幅
		const int TITLE_SPRITE_WIDTH = 1280;
		/// @brief タイトルの画像の縦幅
		const int TITLE_SPRITE_HEIGHT = 720;
		/// @brief タイトルのカメラ座標
		const Vector3 TITLE_CAMERA_POS = { 0.0f,100.0f,800.0f };
		/// @brief タイトルのカメラ注視点
		const Vector3 TITLE_CAMERA_TARGET_POS = { 0.0f,50.0f, 0.0f };
		/// @brief タイトルのカメラ遠平面
		const float TITLE_CAMERA_FAR = 10000.0f;
		/// @brief タイトルのサウンドファイルパス
		const wchar_t* TITLE_BGM_FILEPATH = L"Assets/sound/bgm/titleBgm.wav";
		/// @brief タイトルサウンドの大きさ
		const float TITLE_BGM_VOLUME = 0.1f;
		/// @brief スタート時のサウンドファイルパス
		const wchar_t* START_SE_FILEPATH = L"Assets/sound/se/decision.wav";
		/// @brief スタート時のサウンドの大きさ
		const float START_SE_VOLUME = 0.1f;
		/// @brief フェードインの速度
		const float FEADIN_RATE = 0.3f;
		/// @brief フェードアウトの速度
		const float FEADOUT_RATE = 1.0f;
		/// @brief フォントの座標
		const Vector2 FONT_POS = { -150.0f,-200.0f };
		

		Title::Title()
		{

		}

		Title::~Title()
		{
			//サウンドを止める
			m_soundPlayer->StopBGM(m_titleSoundID);
			//フォントを消す
			DeleteGO(m_font);
		}

		void Title::Init()
		{
			//フォントを作成
			m_font = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_font->Init(L"PUSH A BUTTON");
			m_font->SetColor(g_vec4White);
			m_font->SetPosition(FONT_POS);

			//モデルを作成
			m_models.Init(this);

			//カメラを設定
			g_camera3D->SetPosition(TITLE_CAMERA_POS);
			g_camera3D->SetTarget(TITLE_CAMERA_TARGET_POS);
			g_camera3D->SetFar(TITLE_CAMERA_FAR);

			//サウンドの初期化
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_titleSoundID =  m_soundPlayer->SetBGM(TITLE_BGM_FILEPATH);
			m_soundPlayer->SetBGMVolume(m_titleSoundID, TITLE_BGM_VOLUME);
			m_soundPlayer->PlayBGM(m_titleSoundID, true);
			m_startSoundID = m_soundPlayer->SetSE(START_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_startSoundID, START_SE_VOLUME);

			//使用する情報を取得
			m_game = FindGO<Game>(GAME_NAME);
			m_sceneTransition = FindGO<SceneTransition>(SCENE_TRANSITION_NAME);

			//フェードインを開始
			m_sceneTransition->SetFeadIn(FEADIN_RATE);

			//初期化完了
			m_isInitd = true;
		}

		void Title::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//Aボタンが押されたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonA) && m_endFlag == false) {
				//終了フラグを立てる
				m_endFlag = true;
				//スタート時のサウンドを鳴らす
				m_soundPlayer->PlaySE(m_startSoundID);
				//フェードアウトを開始する
				m_sceneTransition->SetFeadOut(FEADOUT_RATE);
			}
			
			//終了フラグが立っている場合…
			if (m_endFlag == true) {
				//フェードアウトが終わったら…
				if (m_sceneTransition->IsFeadOut() == false) {
					//ゲームシーンを開始してタイトルを終了する
					m_game->GameSceneStart();
					m_game->DeleteTitleScene();
				}
			}

			//フォントとモデルの処理を実行
			m_font->Execution();
			m_models.Execution();
		}
	}
}