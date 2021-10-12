#pragma once
class SkinModelRender;

namespace mainGame {
	namespace defensiveTarget {
		/// @brief �h�q�Ώۂ̋@�\���܂Ƃ߂��N���X
		class DefensiveTarget : public IGameObject
		{
		public:
			DefensiveTarget();
			~DefensiveTarget();
			void Init();
			void Execution();

			/// @brief �_���[�W���󂯂�
			/// @param damage �󂯂�_���[�W��
			void ReceiveDamage(const int damage) { m_defensiveTargetHp -= damage; }

			/// @brief �h�q�Ώۂ̑ϋv�͂��擾
			/// @return �h�q�Ώۂ̎c��ϋv��
			int GetDefensiveTargetHp() { return m_defensiveTargetHp; }

			/// @brief �h�q�Ώۂ��j�󂳂ꂽ���H
			/// @return true�Ŕj�󂳂ꂽ false�Ŕj�󂳂�Ă��Ȃ�
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