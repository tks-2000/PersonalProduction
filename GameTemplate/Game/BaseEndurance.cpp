#include "stdafx.h"
#include "BaseEndurance.h"

namespace mainGame {
	namespace ui {
		/// @brief 耐久値の画像の横幅
		const int ENDURANCE_SPRITE_WIDTH = 1000.0f;
		/// @brief 耐久値の画像の縦幅
		const int ENDURANCE_SPRITE_HEIGHT = 25;
		/// @brief 耐久値の画像の位置
		const Vector3 ENDURANCE_SPRITE_POS = { -500.0f,280.0f,0.0f };
		/// @brief 耐久値の画像の最低値のカラー
		const Vector4 ENDURANCE_SPRITE_MIN_COLOR = { 0.0f,2.0f,0.0f,1.0f };
		/// @brief 耐久値の画像の最高値のカラー
		const Vector4 ENDURANCE_SPRITE_MAX_COLOR = { 2.0f,0.0f,0.0f,1.0f };
		/// @brief 耐久値の画像の中心位置
		const Vector2 ENDURANCE_SPRITE_PIVOT = { 0.0f,0.5f };

		BaseEndurance::BaseEndurance()
		{
			m_isInitd = false;
		}

		BaseEndurance::~BaseEndurance()
		{
			DeleteGO(m_enduranceSprite);
		}

		void BaseEndurance::Init()
		{
			//耐久力の画像を作成
			m_enduranceBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_enduranceBaseSprite->Init("Assets/Image/WB.dds", ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);
			m_enduranceSprite->Init("Assets/Image/WB.dds", ENDURANCE_SPRITE_WIDTH,ENDURANCE_SPRITE_HEIGHT);

			//画像の初期パラメーターを決定
			m_enduranceBaseSprite->SetColor(g_vec4Black);
			m_enduranceSpritePos = ENDURANCE_SPRITE_POS;
			m_enduranceSpriteColor = ENDURANCE_SPRITE_MIN_COLOR;
			m_enduranceBaseSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceSprite->SetPosition(m_enduranceSpritePos);
			m_enduranceBaseSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);
			m_enduranceSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);

			//防衛対象の情報を持って来る
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void BaseEndurance::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			//ダメージを適用する
			ApplyDamage();
			
			//画像の情報を更新する
			m_enduranceSprite->SetScale(m_enduranceSpriteScale);
			m_enduranceSprite->SetColor(m_enduranceSpriteColor);
			m_enduranceBaseSprite->Execute();
			m_enduranceSprite->Execute();
		}

		void BaseEndurance::ApplyDamage()
		{
			//防衛対象の現在耐久力を最大耐久力で除算して1〜0の間の体力の割合を取得する
			float hpRatio = m_defensiveTarget->GetDefensiveTargetHp() / m_defensiveTarget->GetDefensiveTargetMaxHp();

			//画像の横方向の拡大率に防衛対象の耐久力の割合を設定する
			m_enduranceSpriteScale.x = hpRatio;

			//耐久力の割合で残り耐久力のカラーを最大値のカラーと最小値のカラーを線形補完した値にする
			m_enduranceSpriteColor.Lerp(hpRatio,
				ENDURANCE_SPRITE_MAX_COLOR,
				ENDURANCE_SPRITE_MIN_COLOR);
		}
	}
}