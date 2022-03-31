#pragma once
#include "TitleModels.h"

namespace mainGame {

	class Game;

	namespace title {
		/// @brief タイトル画面での処理を行うクラス
		class Title : public IGameObject
		{
		public:
			Title();
			~Title();
			/// @brief 初期化
			void Init();
			/// @brief 実行
			void Execution();

		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 画像
			render::sprite::SpriteRender* m_titleSprite = nullptr;
			/// @brief フォント
			render::font::FontRender* m_font = nullptr;
			/// @brief ゲーム
			Game* m_game = nullptr;
			/// @brief タイトルモデル
			Models m_models;
			/// @brief タイトルサウンドID
			int m_titleSoundID = 0;
			/// @brief スタートサウンドID
			int m_startSoundID = 0;
			/// @brief サウンドプレイヤー
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief 終了フラグ
			bool m_endFlag = false;
			/// @brief シーン遷移
			SceneTransition* m_sceneTransition = nullptr;
		};
	}
}
