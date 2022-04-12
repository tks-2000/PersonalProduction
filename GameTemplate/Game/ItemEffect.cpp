#include "stdafx.h"
#include "ItemEffect.h"

namespace mainGame {
	namespace item {
		/// @brief 出現エフェクトのファイルパス
		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/boxopen.efk";
		/// @brief 出現エフェクトの拡大率
		const Vector3 SPAWN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief 入手エフェクトのファイルパス
		const char16_t* GET_EFFECT_FILEPATH = u"Assets/effect/itemaura.efk";
		/// @brief 入手エフェクトの開始時の拡大率
		const Vector3 GET_EFFECT_START_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief 入手エフェクトの拡大率低下量
		const Vector3 GET_EFFECT_DOWN_SCALE_RATE = { 0.1f,0.1f,0.1f };



		EffectGenerator::EffectGenerator()
		{

		}

		EffectGenerator::~EffectGenerator()
		{
			//作成したエフェクトを削除
			DeleteGO(m_spawnEffect);
			DeleteGO(m_getEffect);
		}

		void EffectGenerator::Init(Item* item)
		{
			//出現させるエフェクトを初期化
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_spawnEffect->Init(SPAWN_EFFECT_FILEPATH);
			m_spawnEffect->SetScale(SPAWN_EFFECT_SCALE);

			m_getEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_getEffect->Init(GET_EFFECT_FILEPATH);
			m_getEffectScale = GET_EFFECT_START_SCALE;

			//使用する情報を取得
			m_item = item;

			//初期化完了
			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//エフェクトの処理を実行
			PlaySpawnEffect();
			PlayGetEffect();

		}

		void EffectGenerator::PlaySpawnEffect()
		{
			//アイテムが出現していて、出現エフェクト再生フラグが立っていない場合…
			if (m_item->IsSpawn() == true && m_isSpawnEffectPlay == false) {
				//出現エフェクトを再生
				m_spawnEffect->SetPosition(m_item->GetPosition());
				m_spawnEffect->Play(false);
				m_isSpawnEffectPlay = true;
			}

			//出現エフェクトの処理を実行
			m_spawnEffect->Execution();
		}

		void EffectGenerator::PlayGetEffect()
		{
			//アイテムがプレイヤーに入手されていて、入手エフェクト再生フラグが立っていない場合…
			if (m_item->IsPlayerGet() == true && m_isGetEffectPlay == false) {
				//入手エフェクトを再生
				m_getEffect->SetPosition(m_item->GetPosition());
				m_getEffect->Play(false);
				m_isGetEffectPlay = true;
			}

			//入手エフェクトの再生フラグが立っている場合
			if (m_isGetEffectPlay == true) {
				//入手エフェクトの拡大率を下げる
				m_getEffectScale -= GET_EFFECT_DOWN_SCALE_RATE;
			}

			//入手エフェクトの処理を実行
			m_getEffect->SetScale(m_getEffectScale);
			m_getEffect->Execution();
		}
	}
}