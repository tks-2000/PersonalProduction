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

			/// @brief ������
			void Init();

			/// @brief ���s
			void Execution();

			/// @brief �_���[�W���󂯂�
			/// @param damage �󂯂�_���[�W��
			void ReceiveDamage(const int damage) { m_defensiveTargetHp -= damage; }

			const Vector3& GetPosition() { return m_position; }

			/// @brief �h�q�Ώۂ̑ϋv�͂��擾
			/// @return �h�q�Ώۂ̎c��ϋv��
			int GetDefensiveTargetHp() { return m_defensiveTargetHp; }

			/// @brief �h�q�Ώۂ��j�󂳂ꂽ���H
			/// @return true�Ŕj�󂳂ꂽ false�Ŕj�󂳂�Ă��Ȃ�
			bool IsBreak() { return m_isBreak; }
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �g�嗦
			Vector3 m_scale = g_vec3One;
			/// @brief �ϋv��
			int m_defensiveTargetHp = 0;
			/// @brief �j��t���O
			bool m_isBreak = false;

			/// @brief ���f��
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;

			render::model::SkinModelRender* m_miniMapdefensiveTargetModel = nullptr;

			/// @brief �ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_staticDefensiveTargetObject;
		};
	}
}