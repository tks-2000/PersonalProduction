#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"
#include "PlayerAttack.h"

class SkinModelRender;


namespace mainGame {

	class Game;

	namespace player {
		
		/// @brief プレイヤーの状態を決める列挙型
		enum EnPlayerStates {
			/// @brief 待機
			enPlayerIdle,
			/// @brief 歩く
			enPlayerWark,
			/// @brief 走る
			enPlayerRun,
			/// @brief ダメージ
			enPlayerDamage,
			/// @brief プレイヤーのステータスの合計数
			enPlayerStateNum
		};

		/// @brief 操作するプレイヤーの機能をまとめたクラス
		class Player : public IGameObject
		{
		public:
			Player();
			~Player();

			void Init();
			bool Start();
			void Update();

			/// @brief プレイヤーの状態を設定
			/// @param plState 設定するプレイヤーの状態
			void SetPlayerState(const EnPlayerStates& plState) { m_playerState = plState; }

			/// @brief プレイヤーの状態を入手
			/// @return プレイヤーのステータス
			const EnPlayerStates& GetPlayerStatus() { return m_playerState; }

			/// @brief プレイヤーの座標を入手
			/// @return プレイヤーの座標のconst参照
			const Vector3& GetPlayerPosition() { return m_position; }

			/// @brief プレイヤーの座標を設定
			/// @param pos 設定するプレイヤーの座標 
			void SetPlayerPosition(const Vector3& pos) { m_position = pos; }

			float GetPlayerAngle() { return m_playerRot.GetAngle(); }

			/// @brief プレイヤーの方向を入手
			/// @return プレイヤーの向いている方向のconst参照
			const Vector3& GetPlayerDirection() { return m_playerRot.GetDirection(); }

			/// @brief プレイヤーの回転角度の変化量を入手
			/// @return プレイヤーの回転角度の変化量
			float GetAngleAmount() { return m_playerRot.GetAngleAmount(); }

			/// @brief プレイヤーの回転角度変化量を元に戻す
			void ResetAngle(){ m_playerRot.AngleReset(); }

			/// @brief 敵の情報をセット
			/// @param enemy セットする敵クラスのアドレス
			void SetEnemyData(enemy::Enemy* enemy) { m_playerAttack.AddEnemyData(enemy); }

			/// @brief 敵の情報を削除
			/// @param enemy 削除する敵クラスのアドレス
			void DeleteEnemyData(enemy::Enemy* enemy) { m_playerAttack.DeleteEnemyData(enemy); }

			/// @brief 実行
			void Execution();

		private:
			void GameStartExecution();
			void GameInProgressExecution();
			void GameClearExecution();
			void GameOverExecution();

			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 回転
			Quaternion m_qRot = g_quatIdentity;
			/// @brief モデル
			render::model::SkinModelRender* m_playerModel = nullptr;

			render::model::SkinModelRender* m_plMapModel = nullptr;
			/// @brief ステート
			EnPlayerStates m_playerState = enPlayerIdle;
			/// @brief アニメーション
			Animation m_playerAnimation;
			/// @brief 移動
			Move m_playerMove;
			/// @brief 回転
			Rotation m_playerRot;
			/// @brief 攻撃
			Attack m_playerAttack;

			Game* m_game = nullptr;
		};
	}
}
