#pragma once
#include "AttackPoint.h"
class SkinModelRender;

namespace mainGame {

	namespace defensiveTarget {
		static const int ATTACKPOINT_NUM = 8;

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

			/// @brief �h�q�Ώۂ̍ő�ϋv�͂��擾
			/// @return �h�q�Ώۂ̍ő�ϋv��
			const float GetDefensiveTargetMaxHp() const { return m_defensiveTargetMaxHp; }

			/// @brief �h�q�Ώۂ��j�󂳂ꂽ���H
			/// @return true�Ŕj�󂳂ꂽ false�Ŕj�󂳂�Ă��Ȃ�
			bool IsBreak() { return m_isBreak; }

			/// @brief �h�q�Ώۂ��_���[�W���󂯂����H
			/// @return true�Ŏ󂯂Ă��� false�Ŏ󂯂Ă��Ȃ�
			bool IsDamage() { return m_isDamage; }

			/// @brief �ł��߂��U���|�C���g���擾
			/// @param pos �v�Z������W
			/// @return �ł��߂��U���|�C���g�̎Q��
			AttackPoint* GetNearestAttackPoint(const Vector3& pos);
		private:
			/// @brief �_���[�W���󂯂�
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
			/// @brief �_���[�W��̗̑�
			float m_afterDamageHp = 0.0f;
			/// @brief �_���[�W�t���O
			bool m_isDamage = false;
			/// @brief �j��t���O
			bool m_isBreak = false;
			/// @brief ���f��
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;
			/// @brief �~�j�}�b�v��̃��f��
			render::model::SkinModelRender* m_miniMapdefensiveTargetModel = nullptr;
			/// @brief �U���|�C���g
			std::array<AttackPoint, ATTACKPOINT_NUM> m_attackPoints;
			/// @brief �ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_staticDefensiveTargetObject;
		};
	}
}