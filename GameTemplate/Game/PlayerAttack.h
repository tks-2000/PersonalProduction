#pragma once
#include "PlayerBullet.h"

namespace mainGame {

	class GameCamera;

	namespace enemy {
		class Enemy;
	}

	namespace player {
		class Player;

		/// @brief プレイヤーの攻撃を制御するクラス
		class Attack
		{
		public:
			Attack();
			~Attack();

			/// @brief 初期化
			/// @param pl 処理を適用するプレイヤーのアドレス
			void Init(Player* pl);

			/// @brief 実行
			void Execute();

			/// @brief 敵の情報を入手
			/// @param enemy 敵クラスのアドレス
			void AddEnemyData(enemy::Enemy* enemy) { m_enemys.push_back(enemy); }

			/// @brief 敵の情報を削除
			/// @param enemy 敵クラスのアドレス
			void DeleteEnemyData(enemy::Enemy* enemy);

			void DeleteBullet(Bullet* bullet);

			/// @brief 弾丸の情報を入手
			/// @return 弾丸の配列のアドレス
			std::vector<Bullet*>* GetBullets() { return &m_bullets; }


			const int GetRemainingBullets()const { return m_remainingBullets; }
			
			const bool IsAttackJudgement() const { return m_isAttackJudgement; }

			const bool IsFollCharge() const{ return m_isFollCharge; }

			const float GetAttackPossibleMatchRate() const{ return m_attackPossibleMatchRate; }

		private:
			/// @brief 近接攻撃を実行
			void MeleeAttack();
			/// @brief チャージ近接攻撃を実行
			void ChargeMeleeAttack();
			/// @brief 
			void BulletFiring();

			void BulletExecution();

			

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 近接攻撃ボタンが押されているか？
			bool m_isMeleeAttackButtonHold = false;
			/// @brief 近接攻撃のチャージ時間
			float m_chargeMeleeAttackTimer = 0.0f;
			/// @brief 近接攻撃のチャージが完了する時間
			float m_chargeMeleeAttackTime = 0.0f;
			/// @brief チャージ完了フラグ
			bool m_isFollCharge = false;
			/// @brief 攻撃の衝撃力
			float m_attackPower = 0.0f;
			/// @brief 攻撃可能な範囲
			float m_attackRange = 0.0f;
			/// @brief 攻撃可能な方向一致率
			float m_attackPossibleMatchRate = 0.0f;
			/// @brief 攻撃判定が出てる？
			bool m_isAttackJudgement = false;
			/// @brief 攻撃判定の時間を計るタイマー
			float m_attackJudgementTimer = 0.0f;

			/// @brief プレイヤークラス
			Player* m_player = nullptr;
			/// @brief 敵クラスの情報をまとめた配列
			std::vector<enemy::Enemy*> m_enemys;
			/// @brief 残弾数
			int m_remainingBullets = 0;
			/// @brief 弾丸の最大所持数
			int m_maxBulletNum = 0;
			/// @brief 弾丸の再装填までの時間を計るタイマー
			float m_bulletReloadTimer = 0.0f;
			/// @brief 弾丸の再装填が完了する時間
			float m_bulletReloadTime = 0.0f;
			/// @brief 弾丸をまとめた配列
			std::vector<Bullet*> m_bullets;
			/// @brief ゲームカメラ
			GameCamera* m_gameCamera = nullptr;
		};
	}
}
