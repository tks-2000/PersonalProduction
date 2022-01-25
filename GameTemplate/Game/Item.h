#pragma once
#include "ItemResource.h"
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
			void Init(ItemGenerator* itemGenerator);

			/// @brief 実行
			virtual void Execution();

			/// @brief 発動
			virtual void Activation();

			void SetPosition(const Vector3& pos) { m_position = pos; }

			void DeleteThis() { DeleteGO(this); }

			const EnItemType& GetItemType() const { return m_itemType; }

			const bool IsPlayerGet() { return m_isPlayerGet; }

			const bool IsActivate() { return m_isActivate; }

		protected:

			/// @brief 初期化済み？
			bool m_isInitd = false;

			/// @brief データを初期化
			virtual void InitData();

			/// @brief プレイヤーとの接触
			void PlayerCollision();

			/// @brief 発動時の効果
			virtual void Efficacy();

			/// @brief プレイヤーに入手されているかのフラグ
			bool m_isPlayerGet = false;
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

			render::model::SkinModelRender* m_itemModel = nullptr;

			/// @brief プレイヤー
			player::Player* m_player = nullptr;

			ItemGenerator* m_itemGenerator = nullptr;

			Sound m_itemSound;

			EnItemType m_itemType = enItemTypeNum;
		};
	}
}