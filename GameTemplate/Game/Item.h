#pragma once

namespace mainGame {

	class Player;

	namespace item {

		class ItemGenerator;

		/// @brief �A�C�e���̊��N���X
		class Item : public IGameObject
		{
		public:

			Item();
			virtual ~Item();

			/// @brief ������
			/// @param itemGenerator �A�C�e��������̏��
			void Init(ItemGenerator* itemGenerator);

			/// @brief ���s
			virtual void Execution();

			/// @brief ����
			virtual void Activation();

			void SetPosition(const Vector3& pos) { m_position = pos; }

			void DeleteThis() { DeleteGO(this); }

		protected:

			/// @brief �������ς݁H
			bool m_isInitd = false;

			/// @brief �f�[�^��������
			virtual void InitData();

			/// @brief �v���C���[�Ƃ̐ڐG
			void PlayerCollision();

			/// @brief �������̌���
			virtual void Efficacy();

			/// @brief �v���C���[�ɓ��肳��Ă��邩�̃t���O
			bool m_isPlayerGet = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �A�C�e�����ʂ̔����t���O
			bool m_isActivate = false;

			/// @brief �A�C�e�����ʂ̔�������
			float m_activateTimer = 0.0f;

			/// @brief �A�C�e���̌��ʂ��I�����鎞��
			float m_endTime = 0.0f;

			render::model::SkinModelRender* m_itemModel = nullptr;

			/// @brief �v���C���[
			player::Player* m_player = nullptr;

			ItemGenerator* m_itemGenerator = nullptr;
		};
	}
}