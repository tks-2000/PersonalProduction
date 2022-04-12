#pragma once
#include "ItemResource.h"
#include "ItemEffect.h"
#include "ItemSound.h"

namespace mainGame {

	class Player;

	namespace item {

		class ItemGenerator;

		/// @brief アイテムの基底クラス
		class Item : public IGameObject
		{
		public:

			Item();
			virtual ~Item();

			/// @brief 初期化
			/// @param itemGenerator アイテム生成器の情報
			void Init(ItemGenerator* itemGenerator,const Vector3& spawnPos = g_vec3Zero);

			/// @brief 実行
			virtual void Execution();

			/// @brief 発動
			virtual void Activation();

			/// @brief 座標を入手
			/// @return 座標のconst参照
			const Vector3& GetPosition() const { return m_position; }

			/// @brief 座標を設定
			/// @param pos 設定したい座標
			void SetPosition(const Vector3& pos) { m_position = pos; }

			/// @brief 自身を削除
			void DeleteThis() { DeleteGO(this); }

			/// @brief アイテムの種類を入手
			/// @return アイテムの種類のconst参照
			const EnItemType& GetItemType() const { return m_itemType; }

			/// @brief 出現しているか？
			/// @return trueで出現している falseで出現していない
			const bool IsSpawn() { return m_isSpawn; }

			/// @brief プレイヤーに入手されているか？
			/// @return trueで入手されている falseで入手されていない
			const bool IsPlayerGet() { return m_isPlayerGet; }

			/// @brief 効果を発動させたか？
			/// @return trueで発動させた falseで発動させていない
			const bool IsActivate() { return m_isActivate; }

			/// @brief 入手不可状態か？
			/// @return trueで入手不可状態 falseで入手不可状態ではない
			const bool IsCantGet() { return m_isCantGet; }

			

		protected:

			/// @brief データを初期化
			virtual void InitData();

			/// @brief 出現時の処理
			virtual void Spawn();

			/// @brief プレイヤーとの接触
			void PlayerCollision();

			/// @brief 入手不可の時の少し動く処理
			void CantGetMove();

			/// @brief 発動時の効果
			virtual void Efficacy();

			/// @brief 削除時の効果
			virtual void DeleteEfficacy();

			/// @brief 初期化済み？
			bool m_isInitd = false;
			/// @brief プレイヤーに入手されているかのフラグ
			bool m_isPlayerGet = false;
			/// @brief 出現位置
			Vector3 m_spawnPos = g_vec3Zero;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief アイテム効果の発動フラグ
			bool m_isActivate = false;
			/// @brief アイテム効果の発動時間
			float m_activateTimer = 0.0f;
			/// @brief アイテムの効果が終了する時間
			float m_endTime = 0.0f;
			/// @brief プレイヤーの入手範囲内だが入手出来ないフラグ
			bool m_isCantGet = false;
			/// @brief 入手不可の間進むタイマー
			float m_cantGetTimer = 0.0f;
			/// @brief 入手不可の時に動く座標
			Vector3 m_cantGetMovePos = g_vec3Zero;
			/// @brief 出現フラグ
			bool m_isSpawn = false;
			/// @brief 出現までの時間を計るタイマー
			float m_spawnTimer = 0.0f;
			/// @brief アイテムのモデル
			render::model::SkinModelRender* m_itemModel = nullptr;
			/// @brief プレイヤー
			player::Player* m_player = nullptr;
			/// @brief アイテム生成器
			ItemGenerator* m_itemGenerator = nullptr;
			/// @brief エフェクト生成器
			EffectGenerator m_itemEffect;
			/// @brief サウンド
			Sound m_itemSound;
			/// @brief アイテムの種類
			EnItemType m_itemType = enItemTypeNum;
		};
	}
}