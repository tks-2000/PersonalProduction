#pragma once
namespace mainGame {
	namespace defensiveTarget {
		/// @brief �G�l�~�[�̍U���ڕW�Ƃ��ċ@�\����N���X
		class AttackPoint
		{
		public:
			AttackPoint();
			~AttackPoint();
			/// @brief ������
			/// @param defensiveTarget �h�q�Ώۂ̃A�h���X
			void Init(DefensiveTarget* defensiveTarget);
			/// @brief ���s
			void Execution();
			/// @brief ���W�����
			/// @return ���W��const�Q��
			const Vector3& GetPostion() const { return m_postion; }
			/// @brief ���W��ݒ�
			/// @param pos �ݒ肷����W
			void SetPositon(const Vector3& pos) { m_postion = pos; }
			/// @brief �^�[�Q�b�g���ꂽ�l���𑝂₷
			void SetTargeted() { m_targetedNum++; }
			/// @brief �^�[�Q�b�g���ꂽ�l�������炷
			void OutTargeted() { m_targetedNum--; }
			/// @brief �^�[�Q�b�g���ꂽ�l�������
			/// @return ���݃^�[�Q�b�g����Ă���l��
			const int GetTargetedNum() const { return m_targetedNum; }

		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_postion = g_vec3Zero;
			/// @brief �^�[�Q�b�g����Ă���l��
			int m_targetedNum = 0;
			/// @brief �h�q�Ώ�
			DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}