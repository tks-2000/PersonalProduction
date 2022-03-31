#pragma once
#include "AttackPoint.h"
class SkinModelRender;

namespace mainGame {

	namespace defensiveTarget {
		static const int ATTACKPOINT_NUM = 8;

		/// @brief 防衛対象の機能をまとめたクラス
		class DefensiveTarget : public IGameObject
		{
		public:
			DefensiveTarget();
			~DefensiveTarget();

			/// @brief 初期化
			void Init();

			/// @brief 実行
			void Execution();

			/// @brief ダメージを受ける
			/// @param damage 受けるダメージ量
			void ReceiveDamage(const float damage);

			const Vector3& GetPosition() { return m_position; }

			/// @brief 防衛対象の耐久力を取得
			/// @return 防衛対象の残り耐久力
			const float GetDefensiveTargetHp() const { return m_defensiveTargetHp; }

			/// @brief 防衛対象の最大耐久力を取得
			/// @return 防衛対象の最大耐久力
			const float GetDefensiveTargetMaxHp() const { return m_defensiveTargetMaxHp; }

			/// @brief 防衛対象が破壊されたか？
			/// @return trueで破壊された falseで破壊されていない
			bool IsBreak() { return m_isBreak; }

			/// @brief 防衛対象がダメージを受けたか？
			/// @return trueで受けている falseで受けていない
			bool IsDamage() { return m_isDamage; }

			/// @brief 最も近い攻撃ポイントを取得
			/// @param pos 計算する座標
			/// @return 最も近い攻撃ポイントの参照
			AttackPoint* GetNearestAttackPoint(const Vector3& pos);
		private:
			/// @brief ダメージを受ける
			void ApplyDamage();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 拡大率
			Vector3 m_scale = g_vec3One;
			/// @brief 耐久力
			float m_defensiveTargetHp = 0.0f;
			/// @brief 拠点の最大耐久力
			float m_defensiveTargetMaxHp = 0.0f;
			/// @brief 耐久力低下量
			float m_hpDecreaseAmount = 0.0f;
			/// @brief ダメージ後の体力
			float m_afterDamageHp = 0.0f;
			/// @brief ダメージフラグ
			bool m_isDamage = false;
			/// @brief 破壊フラグ
			bool m_isBreak = false;
			/// @brief モデル
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;
			/// @brief ミニマップ上のモデル
			render::model::SkinModelRender* m_miniMapdefensiveTargetModel = nullptr;
			/// @brief 攻撃ポイント
			std::array<AttackPoint, ATTACKPOINT_NUM> m_attackPoints;
			/// @brief 静的物理オブジェクト
			PhysicsStaticObject m_staticDefensiveTargetObject;
		};
	}
}