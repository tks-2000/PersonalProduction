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

			const Vector3& GetPosition() { return m_position; }

			void SetPosition(const Vector3& pos) { m_position = pos; }

			void DeleteThis() { DeleteGO(this); }

			const EnItemType& GetItemType() const { return m_itemType; }

			const bool IsSpawn() { return m_isSpawn; }

			const bool IsPlayerGet() { return m_isPlayerGet; }

			const bool IsActivate() { return m_isActivate; }

			const bool IsCantGet() { return m_isCantGet; }

			

		protected:

			/// @brief データを初期化
			virtual void InitData();

			/// @brief 出現時の処理
			virtual void Spawn();

			/// @brief プレイヤーとの接触
			void PlayerCollision();

			/// @brief 入手不可の時に少し動く
			void CantGetMove();

			/// @brief 発動時の効果
			virtual void Efficacy();

			/// @brief 削除時の効果
			virtual void DeleteEfficacy();

			/// @brief 初期化済み？
			bool m_isInitd = false;

			/// @brief プレイヤーに入手されているかのフラグ
			bool m_isPlayerGet = false;

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

			float m_cantGetTimer = 0.0f;

			Vector3 m_cantGetMovePos = g_vec3Zero;

			bool m_isSpawn = false;

			float m_spawnTimer = 0.0f;

			render::model::SkinModelRender* m_itemModel = nullptr;

			/// @brief プレイヤー
			player::Player* m_player = nullptr;

			ItemGenerator* m_itemGenerator = nullptr;

			EffectGenerator m_itemEffect;

			Sound m_itemSound;

			EnItemType m_itemType = enItemTypeNum;
		};
	}
}