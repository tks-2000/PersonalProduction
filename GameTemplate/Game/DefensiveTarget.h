#pragma once
class SkinModelRender;

namespace mainGame {
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
			void ReceiveDamage(const int damage) { m_defensiveTargetHp -= damage; }

			const Vector3& GetPosition() { return m_position; }

			/// @brief 防衛対象の耐久力を取得
			/// @return 防衛対象の残り耐久力
			int GetDefensiveTargetHp() { return m_defensiveTargetHp; }

			/// @brief 防衛対象が破壊されたか？
			/// @return trueで破壊された falseで破壊されていない
			bool IsBreak() { return m_isBreak; }
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 拡大率
			Vector3 m_scale = g_vec3One;
			/// @brief 耐久力
			int m_defensiveTargetHp = 0;
			/// @brief 破壊フラグ
			bool m_isBreak = false;

			/// @brief モデル
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;

			render::model::SkinModelRender* m_miniMapdefensiveTargetModel = nullptr;

			/// @brief 静的物理オブジェクト
			PhysicsStaticObject m_staticDefensiveTargetObject;
		};
	}
}