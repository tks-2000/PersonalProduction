#include "stdafx.h"
#include "ItemSound.h"

namespace mainGame {
	namespace item {
		/// @brief 出現SEのファイルパス
		const wchar_t* SPAWN_SE_FILEPATH = L"Assets/sound/se/GuardEnd.wav";
		/// @brief 出現SEの大きさ
		const float SPAWN_SE_VOLUME = 0.1f;
		/// @brief 入手SEのファイルパス
		const wchar_t* GET_SE_FILEPATH = L"Assets/sound/se/Ranking.wav";
		/// @brief 入手SEの大きさ
		const float GET_SE_VOLUME = 0.1f;
		/// @brief 入手不可SEのファイルパス
		const wchar_t* CANTGET_SE_FILEPATH = L"Assets/sound/se/NoDamageCollide.wav";
		/// @brief 入手不可SEの大きさ
		const float CANTGET_SE_VOLUME = 0.1f;
		/// @brief 入手不可SEの再生タイマーのループ時間
		const float CANTGET_SE_PLAY_TIMER_LOOP_TIME = 1.0f;
		/// @brief 発動SEのファイルパス
		const wchar_t* ACTIVATE_SE_FILEPATH = L"Assets/sound/se/ItemGet.wav";
		/// @brief 発動SEの大きさ
		const float ACTIVATE_SE_VOLUME = 0.1f;

		Sound::Sound()
		{

		}

		Sound::~Sound()
		{

		}

		void Sound::Init(Item* item)
		{
			//使用する情報を入手
			m_item = item;
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			//サウンドを初期化
			m_spawnSoundID = m_soundPlayer->SetSE(SPAWN_SE_FILEPATH);
			m_getSoundID = m_soundPlayer->SetSE(GET_SE_FILEPATH);
			m_cantGetSoundID = m_soundPlayer->SetSE(CANTGET_SE_FILEPATH);
			m_activateSoundID = m_soundPlayer->SetSE(ACTIVATE_SE_FILEPATH);

			//初期化完了
			m_isInitd = true;
		}

		void Sound::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//全てのサウンドの処理を実行
			PlaySpawnSound();
			PlayGetSound();
			PlayCantGetSound();
			PlayActivateSound();
		}

		void Sound::PlaySpawnSound()
		{
			//アイテムが出現していて、出現サウンドが再生されていない場合…
			if (m_item->IsSpawn() == true && m_isSpawnSoundPlay == false) {
				//出現サウンドを再生する
				m_soundPlayer->SetSEVolume(m_spawnSoundID, SPAWN_SE_VOLUME);
				m_soundPlayer->PlaySE(m_spawnSoundID);
				m_isSpawnSoundPlay = true;
			}
		}

		void Sound::PlayGetSound()
		{
			//アイテムが入手されていて、入手サウンドが再生されていない場合…
			if (m_item->IsPlayerGet() == true && m_isGetSoundPlay == false) {
				//入手サウンドを再生する
				m_soundPlayer->SetSEVolume(m_getSoundID, GET_SE_VOLUME);
				m_soundPlayer->PlaySE(m_getSoundID);
				m_isGetSoundPlay = true;
			}
			
		}

		void Sound::PlayCantGetSound()
		{
			//アイテムが入手不可状態のとき…
			if (m_item->IsCantGet() == true) {
				
				//入手不可タイマーが0のとき…
				if (m_cantGetSoundPlayTimer == 0.0f) {
					//入手不可のサウンドを再生する
					m_soundPlayer->SetSEVolume(m_cantGetSoundID, CANTGET_SE_VOLUME);
					m_soundPlayer->PlaySE(m_cantGetSoundID);
				}

				//入手不可サウンドのタイマーを進める
				m_cantGetSoundPlayTimer += g_gameTime->GetFrameDeltaTime();

				//入手不可サウンドのタイマーがループ時間を超えたら…
				if (m_cantGetSoundPlayTimer > CANTGET_SE_PLAY_TIMER_LOOP_TIME) {
					//入手不可サウンドのタイマーを0に戻す
					m_cantGetSoundPlayTimer = 0.0f;
				}
			}
			//アイテムが入手不可状態ではないとき…
			else {
				//入手不可タイマーを0に戻す
				m_cantGetSoundPlayTimer = 0.0f;
			}

			
		}

		void Sound::PlayActivateSound()
		{
			//アイテムの効果が発動していて、発動時のサウンドが再生されていない場合…
			if (m_item->IsActivate() == true && m_isActivateSoundPlay == false) {
				//発動時のサウンドを再生
				m_soundPlayer->SetSEVolume(m_activateSoundID, ACTIVATE_SE_VOLUME);
				m_soundPlayer->PlaySE(m_activateSoundID);
				m_isActivateSoundPlay = true;
			}
		}
	}
}