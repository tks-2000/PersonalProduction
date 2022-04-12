#pragma once
#include "ItemResource.h"
#include "ItemEffect.h"
#include "ItemSound.h"

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
			void Init(ItemGenerator* itemGenerator,const Vector3& spawnPos = g_vec3Zero);

			/// @brief ���s
			virtual void Execution();

			/// @brief ����
			virtual void Activation();

			/// @brief ���W�����
			/// @return ���W��const�Q��
			const Vector3& GetPosition() const { return m_position; }

			/// @brief ���W��ݒ�
			/// @param pos �ݒ肵�������W
			void SetPosition(const Vector3& pos) { m_position = pos; }

			/// @brief ���g���폜
			void DeleteThis() { DeleteGO(this); }

			/// @brief �A�C�e���̎�ނ����
			/// @return �A�C�e���̎�ނ�const�Q��
			const EnItemType& GetItemType() const { return m_itemType; }

			/// @brief �o�����Ă��邩�H
			/// @return true�ŏo�����Ă��� false�ŏo�����Ă��Ȃ�
			const bool IsSpawn() { return m_isSpawn; }

			/// @brief �v���C���[�ɓ��肳��Ă��邩�H
			/// @return true�œ��肳��Ă��� false�œ��肳��Ă��Ȃ�
			const bool IsPlayerGet() { return m_isPlayerGet; }

			/// @brief ���ʂ𔭓����������H
			/// @return true�Ŕ��������� false�Ŕ��������Ă��Ȃ�
			const bool IsActivate() { return m_isActivate; }

			/// @brief ����s��Ԃ��H
			/// @return true�œ���s��� false�œ���s��Ԃł͂Ȃ�
			const bool IsCantGet() { return m_isCantGet; }

			

		protected:

			/// @brief �f�[�^��������
			virtual void InitData();

			/// @brief �o�����̏���
			virtual void Spawn();

			/// @brief �v���C���[�Ƃ̐ڐG
			void PlayerCollision();

			/// @brief ����s�̎��̏�����������
			void CantGetMove();

			/// @brief �������̌���
			virtual void Efficacy();

			/// @brief �폜���̌���
			virtual void DeleteEfficacy();

			/// @brief �������ς݁H
			bool m_isInitd = false;
			/// @brief �v���C���[�ɓ��肳��Ă��邩�̃t���O
			bool m_isPlayerGet = false;
			/// @brief �o���ʒu
			Vector3 m_spawnPos = g_vec3Zero;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �A�C�e�����ʂ̔����t���O
			bool m_isActivate = false;
			/// @brief �A�C�e�����ʂ̔�������
			float m_activateTimer = 0.0f;
			/// @brief �A�C�e���̌��ʂ��I�����鎞��
			float m_endTime = 0.0f;
			/// @brief �v���C���[�̓���͈͓���������o���Ȃ��t���O
			bool m_isCantGet = false;
			/// @brief ����s�̊Ԑi�ރ^�C�}�[
			float m_cantGetTimer = 0.0f;
			/// @brief ����s�̎��ɓ������W
			Vector3 m_cantGetMovePos = g_vec3Zero;
			/// @brief �o���t���O
			bool m_isSpawn = false;
			/// @brief �o���܂ł̎��Ԃ��v��^�C�}�[
			float m_spawnTimer = 0.0f;
			/// @brief �A�C�e���̃��f��
			render::model::SkinModelRender* m_itemModel = nullptr;
			/// @brief �v���C���[
			player::Player* m_player = nullptr;
			/// @brief �A�C�e��������
			ItemGenerator* m_itemGenerator = nullptr;
			/// @brief �G�t�F�N�g������
			EffectGenerator m_itemEffect;
			/// @brief �T�E���h
			Sound m_itemSound;
			/// @brief �A�C�e���̎��
			EnItemType m_itemType = enItemTypeNum;
		};
	}
}