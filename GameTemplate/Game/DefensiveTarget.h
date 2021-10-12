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
			void Init();
			void Execution();

			/// @brief ダメージを受ける
			/// @param damage 受けるダメージ量
			void ReceiveDamage(const int damage) { m_defensiveTargetHp -= damage; }

			/// @brief 防衛対象の耐久力を取得
			/// @return 防衛対象の残り耐久力
			int GetDefensiveTargetHp() { return m_defensiveTargetHp; }

			/// @brief 防衛対象が破壊されたか？
			/// @return trueで破壊された falseで破壊されていない
			bool IsBreak() { return m_isBreak; }
		private:

			bool m_isInitd = false;

			Vector3 m_position = g_vec3Zero;

			Vector3 m_scale = g_vec3One;

			int m_defensiveTargetHp = 0;

			bool m_isBreak = false;

			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;


		};
	}
}