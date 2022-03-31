#pragma once
namespace mainGame {
	namespace defensiveTarget {
		/// @brief エネミーの攻撃目標として機能するクラス
		class AttackPoint
		{
		public:
			AttackPoint();
			~AttackPoint();
			/// @brief 初期化
			/// @param defensiveTarget 防衛対象のアドレス
			void Init(DefensiveTarget* defensiveTarget);
			/// @brief 実行
			void Execution();
			/// @brief 座標を入手
			/// @return 座標のconst参照
			const Vector3& GetPostion() const { return m_postion; }
			/// @brief 座標を設定
			/// @param pos 設定する座標
			void SetPositon(const Vector3& pos) { m_postion = pos; }
			/// @brief ターゲットされた人数を増やす
			void SetTargeted() { m_targetedNum++; }
			/// @brief ターゲットされた人数を減らす
			void OutTargeted() { m_targetedNum--; }
			/// @brief ターゲットされた人数を入手
			/// @return 現在ターゲットされている人数
			const int GetTargetedNum() const { return m_targetedNum; }

		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 座標
			Vector3 m_postion = g_vec3Zero;
			/// @brief ターゲットされている人数
			int m_targetedNum = 0;
			/// @brief 防衛対象
			DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}