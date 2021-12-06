#pragma once
class SkinModelRender;

namespace mainGame {

	namespace ui {
		class GameUI;
	}

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
			void ReceiveDamage(const float damage);

			const Vector3& GetPosition() { return m_position; }

			/// @brief �h�q�Ώۂ̑ϋv�͂��擾
			/// @return �h�q�Ώۂ̎c��ϋv��
			const float GetDefensiveTargetHp() const { return m_defensiveTargetHp; }

			const float GetDefensiveTargetMaxHp() const { return m_defensiveTargetMaxHp; }

			/// @brief �h�q�Ώۂ��j�󂳂ꂽ���H
			/// @return true�Ŕj�󂳂ꂽ false�Ŕj�󂳂�Ă��Ȃ�
			bool IsBreak() { return m_isBreak; }
		private:

			void ApplyDamage();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �g�嗦
			Vector3 m_scale = g_vec3One;
			/// @brief �ϋv��
			float m_defensiveTargetHp = 0.0f;
			/// @brief ���_�̍ő�ϋv��
			float m_defensiveTargetMaxHp = 0.0f;
			/// @brief �ϋv�͒ቺ��
			float m_hpDecreaseAmount = 0.0f;
			/// @brief ���ۂɎ󂯂��_���[�W��
			float m_damageAmount = 0.0f;

			/// @brief �_���[�W�t���O
			bool m_isDamage = false;
			/// @brief �j��t���O
			bool m_isBreak = false;

			/// @brief ���f��
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;

			render::model::SkinModelRender* m_miniMapdefensiveTargetModel = nullptr;

			/// @brief �ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_staticDefensiveTargetObject;

			ui::GameUI* m_gameUI = nullptr;
		};
	}
}