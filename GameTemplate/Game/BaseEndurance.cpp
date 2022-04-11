#include "stdafx.h"
#include "BaseEndurance.h"

namespace mainGame {
	namespace ui {
		
		/// @brief 耐久値の下地画像のファイルパス
		const char* ENDURANCE_BASE_SPRITE_FILEPATH = "Assets/Image/base_sprite_5.dds";
		/// @brief 耐久値の下地画像の横幅
		const int ENDURANCE_BASE_SPRITE_WIDTH = 1100;
		/// @brief 耐久値の下地画像の縦幅
		const int ENDURANCE_BASE_SPRITE_HEIGHT = 700;
		/// @brief 耐久値の下地画像の座標
		const Vector3 ENDURANCE_BASE_SPRITE_POS = { 0.0f,300.0f,0.0f };
		/// @brief 耐久値の下地画像のカラー
		const Vector4 ENDURANCE_BASE_SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief 耐久値の枠画像のファイルパス
		const char* ENDURANCE_FRAME_SPRITE_FILEPATH = "Assets/Image/base_sprite_6.dds";
		/// @brief 耐久値の画像のファイルパス
		const char* ENDURANCE_SPRITE_FILEPATH = "Assets/Image/WB.dds";
		/// @brief 耐久値の画像の横幅
		const int ENDURANCE_SPRITE_WIDTH = 1000;
		/// @brief 耐久値の画像の縦幅
		const int ENDURANCE_SPRITE_HEIGHT = 30;
		/// @brief 耐久値の画像の位置
		const Vector3 ENDURANCE_SPRITE_POS = { -500.0f,300.0f,0.0f };
		/// @brief 耐久値の画像の最低値のカラー
		const Vector4 ENDURANCE_SPRITE_MIN_COLOR = { 0.0f,2.0f,0.0f,0.5f };
		/// @brief 耐久値の画像の最高値のカラー
		const Vector4 ENDURANCE_SPRITE_MAX_COLOR = { 2.0f,0.0f,0.0f,0.5f };
		/// @brief 耐久値の下の画像のカラー
		const Vector4 ENDURANCE_UNDER_SPRITE_COLOR = { 0.1f,0.1f,0.1f,0.5f };
		/// @brief 耐久値の画像の中心位置
		const Vector2 ENDURANCE_SPRITE_PIVOT = { 0.0f,0.5f };

		BaseEndurance::BaseEndurance()
		{
			m_isInitd = false;
		}

		BaseEndurance::~BaseEndurance()
		{
			//作成した画像を削除
			DeleteGO(m_enduranceBaseSprite);
			DeleteGO(m_enduranceBaseFrame);
			DeleteGO(m_enduranceUnderSprite);
			DeleteGO(m_enduranceSprite);
		}

		void BaseEndurance::Init()
		{
			//耐久力の画像を作成
			m_enduranceBaseSprite = NewGO <render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceBaseFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceUnderSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			
			
			//画像の初期パラメーターを決定
			m_enduranceBaseSprite->Init(ENDURANCE_BASE_SPRITE_FILEPATH, ENDURANCE_BASE_SPRITE_WIDTH, ENDURANCE_BASE_SPRITE_HEIGHT);
			m_enduranceBaseFrame->Init(ENDURANCE_FRAME_SPRITE_FILEPATH, ENDURANCE_BASE_SPRITE_WIDTH, ENDURANCE_BASE_SPRITE_HEIGHT);
			m_enduranceBaseSprite->SetColor(ENDURANCE_BASE_SPRITE_COLOR);
			m_enduranceUnderSprite->Init(ENDURANCE_SPRITE_FILEPATH, ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);
			m_enduranceSprite->Init(ENDURANCE_SPRITE_FILEPATH, ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);
			m_enduranceUnderSprite->SetColor(ENDURANCE_UNDER_SPRITE_COLOR);
			m_enduranceSpritePos = ENDURANCE_SPRITE_POS;
			m_enduranceSpriteColor = ENDURANCE_SPRITE_MIN_COLOR;
			m_enduranceBaseFrame->SetPosition(ENDURANCE_BASE_SPRITE_POS);
			m_enduranceBaseSprite->SetPosition(ENDURANCE_BASE_SPRITE_POS);
			m_enduranceUnderSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceUnderSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);
			m_enduranceSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);

			//使用する情報を持って来る
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void BaseEndurance::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//ダメージを適用する
			ApplyDamage();
			
			//ゲームシーンのステートがゲームクリアでもゲームオーバーでもない場合…
			if (m_gameScene->GetGameSceneState() != enGameSceneClear && m_gameScene->GetGameSceneState() != enGameSceneOver) {
				//耐久値の画像の情報を更新する
				m_enduranceSprite->SetScale(m_enduranceSpriteScale);
				m_enduranceSprite->SetColor(m_enduranceSpriteColor);
			}

			//画像の処理を実行
			m_enduranceBaseFrame->Execute();
			m_enduranceBaseSprite->Execute();
			m_enduranceUnderSprite->Execute();
			m_enduranceSprite->Execute();
		}

		void BaseEndurance::ApplyDamage()
		{
			//防衛対象の現在耐久力を最大耐久力で除算して1～0の間の体力の割合を取得する
			float hpRatio = m_defensiveTarget->GetDefensiveTargetHp() / m_defensiveTarget->GetDefensiveTargetMaxHp();

			//画像の横方向の拡大率に防衛対象の耐久力の割合を設定する
			m_enduranceSpriteScale.x = hpRatio;

			//耐久力の割合で残り耐久力のカラーを最大値のカラーと最小値のカラーを線形補完した値にする
			m_enduranceSpriteColor.Lerp(hpRatio,
				ENDURANCE_SPRITE_MAX_COLOR,
				ENDURANCE_SPRITE_MIN_COLOR);
		}

		void BaseEndurance::HIdeUI()
		{
			//表示しているUIを透明にする
			m_enduranceBaseSprite->SetColor(render::COLORLESS);
			m_enduranceBaseFrame->SetColor(render::COLORLESS);
			m_enduranceSprite->SetColor(render::COLORLESS);
			m_enduranceUnderSprite->SetColor(render::COLORLESS);
		}
	}
}