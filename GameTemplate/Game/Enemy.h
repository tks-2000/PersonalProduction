#pragma once
#include "EnemyMove.h"
#include "EnemyAttack.h"
#include "EnemyAnimation.h"
#include "EnemyRotation.h"
#include "EnemyResource.h"
#include "EnemyRouteMove.h";

namespace mainGame {

	namespace player {

		class Player;
	}

	namespace defensiveTarget {
		class DefensiveTarget;
	}

	namespace enemy {

		class Generator;

		/// @brief �G�̏�Ԃ�\���X�e�[�g
		enum EnEnemyState {
			/// @brief �ҋ@�E���΂炭����Ɠ����o��
			enEnemyIdle,
			/// @brief �ړ��E�W�I�Ɍ������Ĉړ�����
			enEnemyMove,
			/// @brief �U���E�W�I�Ɍ������čU�����s��
			enEnemyAttack,
			/// @brief �_���[�W���E���΂炭�����Ȃ�
			enEnemyDamage,
			/// @brief �l�q������E���̏�ŕӂ������
			enEnemySeeTheSituation,
			/// @brief �|���ꂽ�E�ύX���Ȃ����蓮���Ȃ�
			enEnemyDown,
			/// @brief �X�e�[�^�X�̍��v��
			enEnemyStateNum
		};

		/// @brief �G�̏������܂Ƃ߂��N���X
		class Enemy : public IGameObject
		{
		public:
			Enemy();
			virtual ~Enemy();

			/// @brief ������
			/// @param initData �G�̏��������
			void Init(const EnemyInitData& initData);

			/// @brief ���s
			void Execution();

			/// @brief ���W�����
			/// @return �G�̍��W��const�Q��
			const Vector3& GetPosition() { return m_position; }

			/// @brief ���W��ݒ�
			/// @param pos �ݒ肷����W
			void SetPosition(const Vector3& pos) { m_position = pos; }

			/// @brief �ړ����x��ݒ�
			/// @param speed �ݒ肷��ړ����x
			virtual void SetMoveSpeed(const Vector3& speed);

			virtual const Vector3& GetMoveSpeed() const { return g_vec3Zero; }

			const Vector3& GetDirection() { return m_enemyRotation.GetDirection(); };

			void SetRotation(const Quaternion qRot) { m_qRot = qRot; }

			/// @brief �_���[�W���󂯂�
			/// @param damage �󂯂�_���[�W��
			void ReceiveDamage(const int damage);

			/// @brief �G�̏�Ԃ�ݒ�
			/// @param state �ݒ肷��X�e�[�g
			void SetState(const EnEnemyState& state) { m_state = state; }

			/// @brief �G�̏�Ԃ����
			/// @return �G�̃X�e�[�g��const�Q��
			const EnEnemyState& GetState() { return m_state; }

			/// @brief �G�̔ԍ������
			/// @return �G�ɐݒ肳��Ă���ԍ�
			const int GetNumber() { return m_enemyNum; }

			/// @brief �G�̎�ނ����
			/// @return �G�ɐݒ肳��Ă�����
			const EnEnemyType& GetEnemyType() { return m_enemyType; }

			const float GetDeleteTime() const { return m_deleteTime; }

			const bool IsDefeat() { return m_defeatFlag; }

			/// @brief �폜
			void DeleteEnemy();

		protected:

			/// @brief �ʂ̏���������
			/// @param initData ���������
			virtual void InitData(const EnemyInitData& initData);

			/// @brief �ʂ̍s�������s
			virtual void ExecuteBehavior();

			/// @brief �|���ꂽ���̏���
			void DownExecution();

			

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ��]�N�H�[�^�j�I��
			Quaternion m_qRot = g_quatIdentity;
			/// @brief �G�L�����N�^�[���f��
			render::model::SkinModelRender* m_enemyModel = nullptr;

			render::model::SkinModelRender* m_enemyMapModel = nullptr;
			/// @brief �G�̈ړ�
			//Move m_enemyMove;

			//RouteMove m_enemyRouteMove;
			/// @brief �G�̉�]
			Rotation m_enemyRotation;
			/// @brief �G�̍U��
			//Attack m_enemyAttack;
			/// @brief �G�̃A�j���[�V����
			//Animation m_enemyAnimation;
			/// @brief �����̎�ނ�\���񋓌^
			EnEnemyType m_enemyType = enEnemyTypeNum;
			/// @brief ��Ԃ�\���X�e�[�g
			EnEnemyState m_state = enEnemyIdle;
			/// @brief �̗�
			int m_hp = 0;
			/// @brief �v���C���[�N���X
			player::Player* m_player = nullptr;
			/// @brief �����̔ԍ�
			int m_enemyNum = 0;
			/// @brief �_�E�����Ă��玩�g���폜�����܂ł̎���
			float m_deleteTimer = 0.0;

			float m_deleteTime = 0.0f;

			bool m_defeatFlag = false;
			/// @brief �G������̏��
			Generator* m_generator = nullptr;

			Game* m_game = nullptr;

			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
