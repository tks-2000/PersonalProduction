#pragma once

class SkinModelRender;

namespace mainGame {
	namespace player {

		class Attack;

		/// @brief �v���C���[�̒e�ۂ𐧌䂷��N���X
		class Bullet : public IGameObject
		{
		public:
			Bullet();
			~Bullet();

			/// @brief ������
			/// @param plAttack �������̃v���C���[�̍U���𐧌䂷��N���X�̃A�h���X
			/// @param enemys �e�ۂƓ����蔻������G�N���X�̔z��
			/// @param pos �e�ۂ̏����ʒu
			/// @param target �e�ۂ̐i�ވʒu
			void Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos,const Vector3& target);

			/// @brief ���s
			void Execution();

			/// @brief ���W�����
			/// @return ���W��const�Q��
			const Vector3& GetPosition()const { return m_position; }
		private:
			/// @brief �ړ�����
			void MoveExecution();
			/// @brief �G�ƐڐG����
			void EnemyCollision();
			/// @brief ���g���폜
			void DeleteThis();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �����ʒu
			Vector3 m_startPos = g_vec3Zero;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �ڕW�̍��W
			Vector3 m_target = g_vec3Zero;
			/// @brief �ړ�����
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief �ړ����x
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief �e�ۂ̃��f��
			render::model::SkinModelRender* m_bulletModel = nullptr;
			/// @brief �G�̃A�h���X�̔z��
			std::vector<enemy::Enemy*>* m_enemys = nullptr;
			/// @brief �v���C���[�̍U���𐧌䂷��N���X
			Attack* m_playerAttack = nullptr;

			render::effect::EffectRender* m_shotEffect = nullptr;
		};
	}
}
