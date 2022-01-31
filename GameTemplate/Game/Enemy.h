#pragma once
#include "EnemyMove.h"
#include "EnemyAttack.h"
#include "EnemyAnimation.h"
#include "EnemyRotation.h"
#include "EnemyResource.h"
#include "EnemyRouteMove.h"
#include "EnemyEffect.h"
#include "EnemySound.h"

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

			/// @brief �U�����s�������H
			/// @return true�ōs���� false�ōs���Ă��Ȃ�
			virtual const bool IsAttack() { return false; }

			/// @brief �U���������������H
			/// @return true�Ŗ������� false�Ŗ������Ȃ�����
			virtual const bool IsHitAttack() { return false; };

			const Vector3& GetDirection() { return m_enemyRotation.GetDirection(); }

			const Quaternion& GetRotation() { return m_enemyRotation.GetRotation(); }

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

			/// @brief �_�E�����玀�S�܂ł����鎞�Ԃ��擾
			/// @return �_�E�����Ă��玀�S����܂ł̎���
			const float GetDeleteTime() const { return m_deleteTime; }

			/// @brief �_�E�����玀�S����܂ł̎��Ԃ��v��^�C�}�[���擾
			/// @return �_�E�����Ă��玀�S����܂ł̎��Ԃ��v��^�C�}�[
			const float GetDeleteTimer() const { return m_deleteTimer; }

			const bool IsDefeat() { return m_defeatFlag; }

			const bool IsDamage() { return m_isDamage; }

			const Vector3& GetMoveTarget() { return m_moveTarget; }

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

			/// @brief ���f�����쐬
			void CreateModel();

			/// @brief ���f���\�����s���܂ł̃J�E���g���s��
			void ModelDisplayCount();
			

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���f���\���t���O
			bool m_isModelDisplay = false;
			/// @brief ���f���̃t�@�C���p�X
			const char* m_tkmFilepath = nullptr;
			/// @brief �X�P���g���̃t�@�C���p�X
			const char* m_tksFilepath = nullptr;
			/// @brief �A�j���[�V�����N���b�v
			AnimationClip* m_animation = nullptr;
			/// @brief �A�j���[�V�����̐�
			int m_animationNum = 0;
			/// @brief �}�b�v�ɕ\�����郂�f���̃t�@�C���p�X
			const char* m_mapModelFilepath = nullptr;
			/// @brief ���f���\�����s���܂ł̎��Ԃ��v��^�C�}�[
			float m_modelDisplayTimer = 0.0f;
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

			EffectGenerator m_enemyEffect;

			SoundPlayer m_enemySound;
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

			bool m_isDamage = false;

			Vector3 m_moveTarget = g_vec3Zero;
			/// @brief �G������̏��
			Generator* m_generator = nullptr;

			GameScene* m_gameScene = nullptr;

			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
