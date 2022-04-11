#include "stdafx.h"
#include "TimeLimit.h"

namespace mainGame {
	namespace ui {
		/// @brief タイマーの下地画像のファイルパス
		const char* TIMER_BASE_SPRITE_FILEPATH = "Assets/Image/base_sprite_5.dds";
		/// @brief タイマーの下地の枠の画像のファイルパス
		const char* TIMER_BASE_FRAME_FILEPATH = "Assets/Image/base_sprite_6.dds";
		/// @brief タイマーの下地画像の座標
		const Vector3 TIMER_BASE_SPRITE_POS = { -450.0f,190.0f,0.0f };
		/// @brief タイマーの下地画像のカラー
		const Vector4 TIMER_BASE_SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief タイマーの下地画像の横幅
		const int TIMER_BASE_SPRITE_WIDTH = 300;
		/// @brief タイマーの下地画像の縦幅
		const int TIMER_BASE_SPRITE_HEIGHT = 500;
		/// @brief タイム表示のフォントの座標
		const Vector2 TIME_FONT_POS = { -560.0f,215.0f };
		/// @brief タイムの数値表示のフォントの座標
		const Vector2 TIMER_NUM_FONT_POS = { -415.0f,215.0f };
		/// @brief カウントを行う画像のファイルパス配列
		const char* NUM_SPRITE_FILEPATH[NUM_SPRITE_NUM] = {
			"Assets/Image/1.DDS",
			"Assets/Image/2.DDS",
			"Assets/Image/3.DDS"
		};
		/// @brief 開始の画像ファイルパス
		const char* GO_SPRITE_FILEPATH = "Assets/Image/GO.DDS";
		/// @brief UI画像の開始カラー
		const Vector4 UI_SPRITE_START_COLOR = { 1.0f,1.0f,1.0f,0.0f };
		/// @brief UIフォントの開始カラー
		const Vector4 UI_FONT_START_COLOR = { 0.0f,0.0f,0.0f,0.0f };
		/// @brief カウントを行う画像の横幅
		const float NUM_SPRITE_WIDTH = 200.0f;
		/// @brief カウントを行う画像の縦幅
		const float NUM_SPRITE_HEIGHT = 200.0f;
		/// @brief 速いフェードの速度
		const float FAST_FADE_RATE = 2.5f;
		/// @brief 遅いフェードの速度
		const float SLOW_FADE_RATE = 0.5f;
		/// @brief カウントのサウンドファイルパス
		const wchar_t* COUNT_SE_FILEPATH = L"Assets/sound/se/count.wav";
		/// @brief 開始のサウンドファイルパス
		const wchar_t* GO_SE_FILEPATH = L"Assets/sound/se/go.wav";
		/// @brief SEの大きさ
		const float SE_VOLUME = 0.1f;

		TimeLimit::TimeLimit()
		{

		}

		TimeLimit::~TimeLimit()
		{
			//作成した画像やフォントを削除
			DeleteGO(m_timerBaseSprite);
			DeleteGO(m_timerBaseFrame);
			DeleteGO(m_timeFont);
			DeleteGO(m_timerNumFont);
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				DeleteGO(m_count[spriteNum]);
			}

			DeleteGO(m_go);
		}

		void TimeLimit::Init()
		{
			//使用する情報を持って来る
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//表示する画像を作成
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				m_count[spriteNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
				m_count[spriteNum]->Init(NUM_SPRITE_FILEPATH[spriteNum], NUM_SPRITE_WIDTH, NUM_SPRITE_HEIGHT);
				m_count[spriteNum]->SetColor(UI_SPRITE_START_COLOR);
			}

			m_go = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_go->Init(GO_SPRITE_FILEPATH, NUM_SPRITE_WIDTH, NUM_SPRITE_HEIGHT);
			m_go->SetColor(UI_SPRITE_START_COLOR);

			m_timerBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_timerBaseSprite->Init(TIMER_BASE_SPRITE_FILEPATH, TIMER_BASE_SPRITE_WIDTH, TIMER_BASE_SPRITE_HEIGHT);
			m_timerBaseSprite->SetPosition(TIMER_BASE_SPRITE_POS);
			m_timerBaseSprite->SetColor(TIMER_BASE_SPRITE_COLOR);
			m_timerBaseFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_timerBaseFrame->Init(TIMER_BASE_FRAME_FILEPATH, TIMER_BASE_SPRITE_WIDTH, TIMER_BASE_SPRITE_HEIGHT);
			m_timerBaseFrame->SetPosition(TIMER_BASE_SPRITE_POS);

			//表示するフォントを作成
			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timeFont->Init(L"TIME :");
			m_timeFont->SetPosition(TIME_FONT_POS);
			m_timeFont->SetColor(UI_FONT_START_COLOR);

			m_timerNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timerNumFont->Init(L"test");
			m_timerNumFont->SetPosition(TIMER_NUM_FONT_POS);
			m_timerNumFont->SetColor(UI_FONT_START_COLOR);

			//サウンドを初期化
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_countSoundID = m_soundPlayer->SetSE(COUNT_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_countSoundID, SE_VOLUME);
			m_goSoundID = m_soundPlayer->SetSE(GO_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_goSoundID, SE_VOLUME);

			//変数を初期化
			m_isCountDown = true;

			//初期化完了
			m_isInitd = true;
		}

		void TimeLimit::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//タイマーの値をフォントに適用
			std::wstring conversion;
			conversion = std::to_wstring(m_timer->GetTimer());
			m_timerNumFont->SetText(conversion.c_str());

			//ゲームシーンが進行中の場合
			if (m_gameScene->GetGameSceneState() == enGameSceneInProgress) {
				//フォントの色を見えるようにする
				m_timerNumFont->SetColor(g_vec4White);
				m_timeFont->SetColor(g_vec4White);
			}

			//カウント中の場合
			if (m_isCountDown == true) {
				//カウントの処理を行う
				CountDown();
			}

			//画像の数だけ実行
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				m_count[spriteNum]->Execute();
			}

			//開始画像が不透明になったらフェードアウトする
			if (m_go->IsOpacity() == true) {
				m_go->FadeOut(SLOW_FADE_RATE);
			}

			//処理を実行
			m_go->Execute();
			m_timerBaseSprite->Execute();
			m_timerBaseFrame->Execute();
			m_timeFont->Execution();
			m_timerNumFont->Execution();
		}

		void TimeLimit::HideUI()
		{
			//UIの色を見えなくする
			m_timerBaseSprite->SetColor(render::COLORLESS);
			m_timerBaseFrame->SetColor(render::COLORLESS);
			m_timeFont->SetColor(render::COLORLESS);
			m_timerNumFont->SetColor(render::COLORLESS);
		}

		void TimeLimit::CountDown()
		{
			
			//画像の数だけ繰り返す
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				//番号が開始タイマーより１小さい値と同じだった場合…
				if (spriteNum == m_timer->GetStartTimer() - 1) {
					//その番号の画像をフェードインする
					m_count[spriteNum]->FadeIn(FAST_FADE_RATE);
					//カウントサウンドが鳴っていない場合…
					if (m_isPlayCountSE[spriteNum] == false) {
						//カウントサウンドを鳴らす
						m_soundPlayer->PlaySE(m_countSoundID);
						m_isPlayCountSE[spriteNum] = true;
					}
				}
				//番号が開始タイマーより１小さい値では無かった場合…
				else {
					//その番号の画像はフェードアウトする
					m_count[spriteNum]->FadeOut(FAST_FADE_RATE);
				}
			}

			//開始タイマーが0になった場合…
			if (m_timer->GetStartTimer() == 0) {
				//開始画像をフェードインする
				m_go->FadeIn(FAST_FADE_RATE);
				//開始のサウンドを鳴らす
				m_soundPlayer->PlaySE(m_goSoundID);
				//カウントダウン中のフラグを降ろす
				m_isCountDown = false;
			}
		}
	}
}