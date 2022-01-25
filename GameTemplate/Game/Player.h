#pragma once
#include "PlayerMove.h"
#include "PlayerAnimation.h"
#include "PlayerRotation.h"
#include "PlayerAttack.h"
#include "PlayerEffect.h"
#include "PlayerSound.h"
#include "ItemSlot.h"
#include "ItemResource.h"

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
			/// @brief 攻撃している
			enPlayerAttack,
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

			/// @brief プレイヤーの再生中のアニメーションを入手
			/// @return プレイヤーのアニメーションのステータス
			const EnPlayerAnimations& GetPlayerAnimation() { return m_playerAnimation.GetAnimationState(); }

			/// @brief プレイヤーの座標を入手
			/// @return プレイヤーの座標のconst参照
			const Vector3& GetPlayerPosition() { return m_position; }

			/// @brief プレイヤーの座標を設定
			/// @param pos 設定するプレイヤーの座標 
			void SetPlayerPosition(const Vector3& pos) { m_position = pos; }

			const Vector3& GetMoveSpeed() { return m_playerMove.GetMoveSpssd(); }

			void SetMoveSpeed(const Vector3& speed) { m_playerMove.SetMoveSpeed(speed); }

			void SetAddVerocity(const float addVerocity) { m_playerMove.SetAddVerocity(addVerocity); }

			float GetPlayerAngle() { return m_playerRot.GetAngle(); }

			const Quaternion& GetPlayerRotation() {return m_playerRot.GetRotation(); }

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

			/// @brief アイテムスロットにアイテムを追加
			/// @param item 追加するアイテム
			/// @return trueで追加できた falseで追加出来なかった
			bool SetItemSlot(item::Item* item) { return m_itemSlot.SetItem(item); }

			/// @brief 現在選択しているアイテムスロット番号を入手
			/// @return 現在選択しているアイテムスロット番号
			const int GetSelectSlotNum()const { return m_itemSlot.GetSelectSlotNum(); }

			/// @brief スロットにアイテムを持っているか調べる
			/// @param slotNum 調べるアイテムスロット番号
			/// @return 持っていればtrue 持っていなければfalse
			const bool IsOwnedItem(const int slotNum) const { return m_itemSlot.IsOwnedItem(slotNum); }

			/// @brief 残弾数を取得
			/// @return プレイヤーの残弾数
			const int GetRemainingBullet() { return m_playerAttack.GetRemainingBullets(); }

			/// @brief 弾丸のデータを入手
			/// @return 弾丸の配列のアドレス
			std::vector <Bullet*>* GetBulletData() { return m_playerAttack.GetBullets(); }

			/// @brief プレイヤーに攻撃判定が出ているか調べる
			/// @return trueで出ている falseで出ていない
			const bool IsAttackJudgement() const { return m_playerAttack.IsAttackJudgement(); }

			/// @brief プレイヤーがフルチャージ状態か調べる
			/// @return trueでフルチャージ状態 falseでフルチャージ状態ではない
			const bool IsFollCharge() const { return m_playerAttack.IsFollCharge(); }

			/// @brief 攻撃可能な方向一致率を取得
			/// @return 攻撃可能な方向一致率
			const float GetAttackPossibleMatchRate() const { return m_playerAttack.GetAttackPossibleMatchRate(); }

			/// @brief 無敵状態か？
			/// @return trueで無敵 falseで無敵でない
			bool IsInvincible() const { return m_invincibleFlag; }

			/// @brief アイテムスロット内のアイテムの種類を取得
			/// @param slotNum スロット番号
			/// @return アイテムの種類
			const item::EnItemType& GetSlotItemType(const int slotNum) { return m_itemSlot.GetItemType(slotNum); }

			/// @brief プレイヤーが攻撃を開始したか？
			/// @return trueで開始した falseで開始していない・もう攻撃している
			const bool IsAttackStart() { return m_playerAttack.IsAttackStart(); }

			/// @brief 実行
			void Execution();

		private:
			
			void DamageExecution();

			void InvincibleExecution();

			void SetWeapons();

			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 回転
			Quaternion m_qRot = g_quatIdentity;
			/// @brief プレイヤーモデル
			render::model::SkinModelRender* m_playerModel = nullptr;
			/// @brief 剣のモデル
			render::model::SkinModelRender* m_swordModel = nullptr;
			/// @brief 盾のモデル
			render::model::SkinModelRender* m_shieldModel = nullptr;
			/// @brief マップ上のモデル
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

			EffectGenerator  m_playerEffect;

			Sound m_playerSound;

			ItemSlot m_itemSlot;

			float m_damageTimer = 0.0f;

			bool m_invincibleFlag = false;

			float m_invincibleTimer = 0.0f;

			Game* m_game = nullptr;
		};
	}
}
