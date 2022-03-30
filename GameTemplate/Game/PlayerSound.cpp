#include "stdafx.h"
#include "PlayerSound.h"

namespace mainGame {
	namespace player {
		/// @brief 歩行サウンドのファイルパス
		const wchar_t* WALK_SE_FILEPATH = L"Assets/sound/se/ArmorWalk.wav";
		/// @brief 歩行サウンドの大きさ
		const float WALK_SE_VOLUME = 0.1f;
		/// @brief 歩行サウンドの再生間隔
		const float WALK_SE_INTERVAL = 0.6f;
		/// @brief 走行サウンドのファイルパス
		const wchar_t* RUN_SE_FILEPATH = L"Assets/sound/se/ArmorWalk.wav";
		/// @brief 走行サウンドの大きさ
		const float RUN_SE_VOLUME = 0.2f;
		/// @brief 走行サウンドの再生間隔
		const float RUN_SE_INTERVAL = 0.3f;
		/// @brief 攻撃サウンドのファイルパス
		const wchar_t* ATTACK_SE_FILEPATH = L"Assets/sound/se/PlayerAttack.wav";
		/// @brief 攻撃サウンドの大きさ
		const float ATTACK_SE_VOLUME = 0.1f;
		/// @brief 攻撃サウンドの再生開始時間
		const float ATTACK_SE_PLAY_TIME = 0.4f;
		/// @brief ダメージサウンドのファイルパス
		const wchar_t* DAMAGE_SE_FILEPATH = L"Assets/sound/se/WeakCollide.wav";
		/// @brief ダメージサウンドの大きさ
		const float DAMAGE_SE_VOLUME = 0.1f;
		/// @brief 膝をつくサウンドのファイルパス
		const wchar_t* KNEE_SE_FILEPATH = L"Assets/sound/se/Knee.wav";
		/// @brief 膝をつくサウンドの大きさ
		const float KNEE_SE_VOLUME = 1.0f;
		/// @brief 膝をつくサウンドの再生開始時間
		const float KNEE_SE_PLAY_TIME = 1.0f;
		/// @brief 倒れるサウンドのファイルパス
		const wchar_t* DOWN_SE_FILEPATH = L"Assets/sound/se/Down.wav";
		/// @brief 倒れるサウンドの大きさ
		const float DOWN_SE_VOLUME = 0.5f;
		/// @brief 倒れるサウンドの再生開始時間
		const float DOWN_SE_PLAY_TIME = 2.0f;

		Sound::Sound()
		{

		}

		Sound::~Sound()
		{

		}

		void Sound::Init(Player* player)
		{
			//使用する情報を取得
			m_player = player;
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			//音声を初期化
			m_walkSoundID = m_soundPlayer->SetSE(WALK_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_walkSoundID, WALK_SE_VOLUME);
			m_runSoundID = m_soundPlayer->SetSE(RUN_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_runSoundID, RUN_SE_VOLUME);
			m_attackSoundID = m_soundPlayer->SetSE(ATTACK_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_attackSoundID, ATTACK_SE_VOLUME);
			m_damageSoundID = m_soundPlayer->SetSE(DAMAGE_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_damageSoundID, DAMAGE_SE_VOLUME);
			m_kneeSoundID = m_soundPlayer->SetSE(KNEE_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_kneeSoundID, KNEE_SE_VOLUME);
			m_downSoundID = m_soundPlayer->SetSE(DOWN_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_downSoundID, DOWN_SE_VOLUME);

			//初期化完了
			m_isInitd = true;
		}

		void Sound::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//各種サウンドを再生
			PlayWalkSound();
			PlayRunSound();
			PlayAttackSound();
			PlayDamageSound();
			PlayDownSound();
		}

		void Sound::PlayWalkSound()
		{
			//プレイヤーが歩行中なら…
			if (m_player->GetPlayerStatus() == enPlayerWark) {
				//タイマーを進める
				m_walkSoundTimer += g_gameTime->GetFrameDeltaTime();
				//タイマーが再生間隔を超えたら…
				if (m_walkSoundTimer > WALK_SE_INTERVAL) {
					//サウンドを再生
					m_soundPlayer->PlaySE(m_walkSoundID);
					//タイマーを0にする
					m_walkSoundTimer = 0.0f;
				}
			}
			//そうでないなら…
			else {
				//タイマーを0にする
				m_walkSoundTimer = 0.0f;
			}
		}

		void Sound::PlayRunSound()
		{
			//プレイヤーが走行中なら…
			if (m_player->GetPlayerStatus() == enPlayerRun) {
				//タイマーを進める
				m_runSoundTimer += g_gameTime->GetFrameDeltaTime();
				//タイマーが再生間隔を超えたら…
				if (m_runSoundTimer > RUN_SE_INTERVAL) {
					//サウンドを再生
					m_soundPlayer->PlaySE(m_runSoundID);
					//タイマーを0にする
					m_runSoundTimer = 0.0f;
				}
			}
			//そうでないなら…
			else {
				//タイマーを0にする
				m_runSoundTimer = 0.0f;
			}
		}

		void Sound::PlayAttackSound()
		{
			//プレイヤーが攻撃中なら…
			if (m_player->GetPlayerStatus() == enPlayerAttack) {
				//タイマーを進める
				m_attackSoundPlayTimer += g_gameTime->GetFrameDeltaTime();
				//タイマーが再生時間を超えて再生フラグが立っていないなら…
				if (m_attackSoundPlayTimer > ATTACK_SE_PLAY_TIME && m_isAttackSoundPlay == false) {
					//サウンドを再生
					m_soundPlayer->PlaySE(m_attackSoundID);
					m_attackSoundPlayTimer = 0.0f;
					//再生フラグを立てる
					m_isAttackSoundPlay = true;
				}
			}
			//そうでないなら…
			else {
				//タイマーと再生フラグを戻す
				m_attackSoundPlayTimer = 0.0f;
				m_isAttackSoundPlay = false;
			}
		}

		void Sound::PlayDamageSound()
		{
			//プレイヤーがダメージ中の場合…
			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				//再生フラグが立っていない場合…
				if (m_isDamageSoundPlay == false) {
					//サウンドを再生
					m_soundPlayer->PlaySE(m_damageSoundID);
					//再生フラグを立てる
					m_isDamageSoundPlay = true;
				}
			}
			//そうでない場合…
			else {
				//再生フラグを降ろす
				m_isDamageSoundPlay = false;
			}
		}

		void Sound::PlayDownSound()
		{
			//プレイヤーがダウン状態の場合
			if (m_player->GetPlayerAnimation() == enPlayerAnimationKneelDown) {
				//タイマーを進める
				m_kneeSoundTimer += g_gameTime->GetFrameDeltaTime();
				m_downSoundTimer += g_gameTime->GetFrameDeltaTime();

				//タイマーが再生時間を過ぎて再生フラグが立っていない場合…
				if (m_kneeSoundTimer > KNEE_SE_PLAY_TIME && m_isKneeSoundPlay == false) {
					//サウンドを再生する
					m_soundPlayer->PlaySE(m_kneeSoundID);
					//再生フラグを立てる
					m_isKneeSoundPlay = true;
				}

				//タイマーが再生時間を過ぎて再生フラグが立っていない場合…
				if (m_downSoundTimer > DOWN_SE_PLAY_TIME && m_isDownSoundPlay == false) {
					//サウンドを再生する
					m_soundPlayer->PlaySE(m_downSoundID);
					//再生フラグを立てる
					m_isDownSoundPlay = true;
				}
			}
			//そうでない場合…
			else {
				//再生フラグとタイマーを戻す
				m_isKneeSoundPlay = false;
				m_isDownSoundPlay = false;
				m_kneeSoundTimer = 0.0f;
				m_downSoundTimer = 0.0f;
			}
		}
	}
}