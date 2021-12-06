#pragma once
class SkinModelRender;

namespace mainGame {

	namespace ui {
		class GameUI;
	}

	namespace defensiveTarget {
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

			const float GetDefensiveTargetMaxHp() const { return m_defensiveTargetMaxHp; }

			/// @brief 防衛対象が破壊されたか？
			/// @return trueで破壊された falseで破壊されていない
			bool IsBreak() { return m_isBreak; }
		private:

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
			/// @brief 実際に受けたダメージ量
			float m_damageAmount = 0.0f;

			/// @brief ダメージフラグ
			bool m_isDamage = false;
			/// @brief 破壊フラグ
			bool m_isBreak = false;

			/// @brief モデル
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;

			render::model::SkinModelRender* m_miniMapdefensiveTargetModel = nullptr;

			/// @brief 静的物理オブジェクト
			PhysicsStaticObject m_staticDefensiveTargetObject;

			ui::GameUI* m_gameUI = nullptr;
		};
	}
}