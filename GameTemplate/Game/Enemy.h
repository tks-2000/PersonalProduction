#pragma once
#include "EnemyMove.h"
#include "EnemyAttack.h"
#include "EnemyAnimation.h"
#include "EnemyRotation.h"
#include "EnemyResource.h"
#include "EnemyRouteMove.h"
#include "EnemyEffect.h"
#include "EnemySound.h"

namespace mainGame {

	namespace player {

		class Player;
	}

	namespace defensiveTarget {
		class DefensiveTarget;
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
			/// @brief 様子を見る・その場で辺りを見回す
			enEnemySeeTheSituation,
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
			virtual ~Enemy();

			/// @brief 初期化
			/// @param initData 敵の初期化情報
			void Init(const EnemyInitData& initData);

			/// @brief 実行
			void Execution();

			/// @brief 座標を入手
			/// @return 敵の座標のconst参照
			const Vector3& GetPosition() { return m_position; }

			/// @brief 座標を設定
			/// @param pos 設定する座標
			void SetPosition(const Vector3& pos) { m_position = pos; }

			/// @brief 移動速度を設定
			/// @param speed 設定する移動速度
			virtual void SetMoveSpeed(const Vector3& speed);

			virtual const Vector3& GetMoveSpeed() const { return g_vec3Zero; }

			/// @brief 攻撃を行ったか？
			/// @return trueで行った falseで行っていない
			virtual const bool IsAttack() { return false; }

			/// @brief 攻撃が命中したか？
			/// @return trueで命中した falseで命中しなかった
			virtual const bool IsHitAttack() { return false; };

			const Vector3& GetDirection() { return m_enemyRotation.GetDirection(); }

			const Quaternion& GetRotation() { return m_enemyRotation.GetRotation(); }

			void SetRotation(const Quaternion qRot) { m_qRot = qRot; }

			/// @brief ダメージを受ける
			/// @param damage 受けるダメージ量
			void ReceiveDamage(const int damage);

			/// @brief 敵の状態を設定
			/// @param state 設定するステート
			void SetState(const EnEnemyState& state) { m_state = state; }

			/// @brief 敵の状態を入手
			/// @return 敵のステートのconst参照
			const EnEnemyState& GetState() { return m_state; }

			/// @brief 敵の番号を入手
			/// @return 敵に設定されている番号
			const int GetNumber() { return m_enemyNum; }

			/// @brief 敵の種類を入手
			/// @return 敵に設定されている種類
			const EnEnemyType& GetEnemyType() { return m_enemyType; }

			/// @brief ダウンから死亡までかかる時間を取得
			/// @return ダウンしてから死亡するまでの時間
			const float GetDeleteTime() const { return m_deleteTime; }

			/// @brief ダウンから死亡するまでの時間を計るタイマーを取得
			/// @return ダウンしてから死亡するまでの時間を計るタイマー
			const float GetDeleteTimer() const { return m_deleteTimer; }

			const bool IsDefeat() { return m_defeatFlag; }

			const bool IsDamage() { return m_isDamage; }

			const Vector3& GetMoveTarget() { return m_moveTarget; }

			/// @brief 削除
			void DeleteEnemy();

		protected:

			/// @brief 個別の情報を初期化
			/// @param initData 初期化情報
			virtual void InitData(const EnemyInitData& initData);

			/// @brief 個別の行動を実行
			virtual void ExecuteBehavior();

			/// @brief 倒された時の処理
			void DownExecution();

			/// @brief モデルを作成
			void CreateModel();

			/// @brief モデル表示を行うまでのカウントを行う
			void ModelDisplayCount();
			

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief モデル表示フラグ
			bool m_isModelDisplay = false;
			/// @brief モデルのファイルパス
			const char* m_tkmFilepath = nullptr;
			/// @brief スケルトンのファイルパス
			const char* m_tksFilepath = nullptr;
			/// @brief アニメーションクリップ
			AnimationClip* m_animation = nullptr;
			/// @brief アニメーションの数
			int m_animationNum = 0;
			/// @brief マップに表示するモデルのファイルパス
			const char* m_mapModelFilepath = nullptr;
			/// @brief モデル表示を行うまでの時間を計るタイマー
			float m_modelDisplayTimer = 0.0f;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 回転クォータニオン
			Quaternion m_qRot = g_quatIdentity;
			/// @brief 敵キャラクターモデル
			render::model::SkinModelRender* m_enemyModel = nullptr;

			render::model::SkinModelRender* m_enemyMapModel = nullptr;
			/// @brief 敵の移動
			//Move m_enemyMove;

			//RouteMove m_enemyRouteMove;
			/// @brief 敵の回転
			Rotation m_enemyRotation;

			EffectGenerator m_enemyEffect;

			SoundPlayer m_enemySound;
			/// @brief 敵の攻撃
			//Attack m_enemyAttack;
			/// @brief 敵のアニメーション
			//Animation m_enemyAnimation;
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

			float m_deleteTime = 0.0f;

			bool m_defeatFlag = false;

			bool m_isDamage = false;

			Vector3 m_moveTarget = g_vec3Zero;
			/// @brief 敵生成器の情報
			Generator* m_generator = nullptr;

			GameScene* m_gameScene = nullptr;

			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
