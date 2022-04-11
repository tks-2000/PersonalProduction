#include "stdafx.h"
#include "RemainingBullets.h"

namespace mainGame {
	namespace ui {
		/// @brief 残弾数のフォントの位置
		const Vector2 BULLET_NUM_FONT_POS = { 350.0f,-115.0f };
		/// @brief 残弾を表す画像のファイルパス
		const char* REMAINING_BULLETS_SPRITE_FILEPATH = "Assets/Image/bullet.dds";
		/// @brief 残弾の画像の横幅
		const int REMAINING_BULLETS_SPRITE_WIDTH = 100;
		/// @brief 残弾の画像の縦幅
		const int REMAINING_BULLETS_SPRITE_HEIGHT = 100;
		/// @brief 残弾の画像の座標
		const Vector3 REMAINING_BULLETS_SPRITE_POS = { 300.0f,-140.0f,0.0f };

		RemainingBullets::RemainingBullets()
		{

		}

		RemainingBullets::~RemainingBullets()
		{
			//作成したものを削除
			DeleteGO(m_remainingBulletsNumFont);
			DeleteGO(m_remainingBulletsSprite);
		}

		void RemainingBullets::Init()
		{
			//使用する情報を持って来る
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//フォントを作成
			m_remainingBulletsNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			std::wstring text;
			text = std::to_wstring(m_player->GetRemainingBullet());
			m_remainingBulletsNumFont->Init(text.c_str());
			m_remainingBulletsNumFont->SetPosition(BULLET_NUM_FONT_POS);

			//画像を作成
			m_remainingBulletsSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_remainingBulletsSprite->Init(REMAINING_BULLETS_SPRITE_FILEPATH, REMAINING_BULLETS_SPRITE_WIDTH, REMAINING_BULLETS_SPRITE_HEIGHT);
			m_remainingBulletsSprite->SetPosition(REMAINING_BULLETS_SPRITE_POS);

			//初期化完了
			m_isInitd = true;
		}

		void RemainingBullets::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//プレイヤーの残弾が0個の場合…
			if (m_player->GetRemainingBullet() == 0) {
				//リロード中の表示を行う
				m_remainingBulletsNumFont->SetText(L"Reload...");
			}
			//プレイヤーの残弾が0でない場合…
			else {
				//プレイヤーの残弾数を表示する
				std::wstring text;
				text = std::to_wstring(m_player->GetRemainingBullet());
				m_remainingBulletsNumFont->SetText(text.c_str());
			}
			//画像とフォントの処理を実行
			m_remainingBulletsNumFont->Execution();
			m_remainingBulletsSprite->Execute();
		}

		void RemainingBullets::HideUI()
		{
			//UIのカラーを見えなくする
			m_remainingBulletsNumFont->SetColor(render::COLORLESS);
			m_remainingBulletsSprite->SetColor(render::COLORLESS);
		}
	}
}