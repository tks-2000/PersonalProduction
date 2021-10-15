#pragma once
#include "EnemyMove.h"
#include "EnemyAttack.h"
#include "EnemyAnimation.h"
#include "EnemyRotation.h"
#include "EnemyResource.h"

namespace mainGame {

	namespace player {

		class Player;
	}

	namespace enemy {

		class Generator;

		/// @brief 敵の状態を表すステート
		enum EnEnemyState {
			/// @brief 待機・しばらくすると動き出す
			enEnemyIdle,
			/// @brief 移動・標的に向かって移動する
			enEnemyMove,
			/// @brief 攻撃・標的に向かって攻撃を行う
			enEnemyAttack,
			/// @brief ダメージ中・しばらく動けない
			enEnemyDamage,
			/// @brief 倒された・変更がない限り動かない
			enEnemyDown,
			/// @brief ステータスの合計数
			enEnemyStateNum
		};

		/// @brief 敵の処理をまとめたクラス
		class Enemy : public IGameObject
		{
		public:
			Enemy();
			~Enemy();

			/// @brief 初期化
			void Init(const int num, const EnEnemyType& type,const Vector3& pos = g_vec3Zero);

			/// @brief 実行
			void Execution();

			/// @brief 座標を入手
			/// @return 敵の座標のconst参照
			const Vector3& GetPosition() { return m_position; }

			/// @brief 移動速度を設定
			/// @param speed 設定する移動速度
			void SetMoveSpeed(const Vector3& speed) { m_enemyMove.SetMoveSpeed(speed); }

			/// @brief ダメージを受ける
			/// @param damage 受けるダメージ量
			void ReceiveDamage(const int damage);

			/// @brief 敵の状態を設定
			/// @param state 設定するステート
			void SetState(const EnEnemyState& state) { m_state = state; }

			/// @brief 敵の状態を入手
			/// @return 敵のステートのconst参照
			const EnEnemyState& GetState() { return m_state; }

		private:

			void DownExecution();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 回転クォータニオン
			Quaternion m_qRot = g_quatIdentity;
			/// @brief 敵キャラクターモデル
			render::model::SkinModelRender* m_enemyModel = nullptr;
			/// @brief 敵の移動
			Move m_enemyMove;
			/// @brief 敵の回転
			Rotation m_enemyRotation;
			/// @brief 敵の攻撃
			Attack m_enemyAttack;
			/// @brief 敵のアニメーション
			Animation m_enemyAnimation;
			/// @brief 自分の種類を表す列挙型
			EnEnemyType m_enemyType = enEnemyTypeNum;
			/// @brief 状態を表すステート
			EnEnemyState m_state = enEnemyIdle;
			/// @brief 体力
			int m_hp = 0;
			/// @brief プレイヤークラス
			player::Player* m_player = nullptr;
			/// @brief 自分の番号
			int m_enemyNum = 0;
			/// @brief ダウンしてから自身が削除されるまでの時間
			float m_deleteTimer = 0.0;

			Generator* m_generator = nullptr;
		};
	}
}
