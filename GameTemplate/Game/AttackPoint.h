#pragma once
namespace mainGame {
	namespace defensiveTarget {
		class AttackPoint
		{
		public:
			AttackPoint();
			~AttackPoint();
			void Init(DefensiveTarget* defensiveTarget);
			void Execution();
			const Vector3& GetPostion() const { return m_postion; }
			void SetPositon(const Vector3& pos) { m_postion = pos; }
			void SetTargeted() { m_targetedNum++; }
			void OutTargeted() { m_targetedNum--; }
			const int GetTargetedNum() const { return m_targetedNum; }

		private:

			bool m_isInitd = false;

			Vector3 m_postion = g_vec3Zero;

			int m_targetedNum = 0;

			DefensiveTarget* m_defensiveTarget = nullptr;

			render::model::SkinModelRender* m_model = nullptr;
		};
	}
}