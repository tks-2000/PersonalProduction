#include "stdafx.h"
#include "PlayerAttack.h"

namespace {

	const float CHARGE_MELEE_ATTACK_TIME = 1.0f;
	/// @brief �G�ɗ^����_���[�W
	const int NORMAL_ATTACK_DAMAGE = 3;
	/// @brief �G�ɗ^����Ռ���
	const float NORMAL_IMPACT_FORCE = 3000.0f;
	/// @brief �G�ɗ^���鋭�͂ȏՌ���
	const float STRONG_IMPACT_FORCE = 6000.0f;
	/// @brief �U���͈�
	const float ATTACK_RANGE = 200.0f;
	/// @brief �U���\�ȕ�����v��
	const float ATTACK_POSSIBLE_MATCH_RATE = 0.0f;
	/// @brief �ʏ�̒e�ۂ̍ő及����
	const int NORMAL_MAX_BULLET_NUM = 10;
	/// @brief �ʏ�̒e�ۂ̍đ��U����
	const float NORMAL_BULLET_RELOAD_TIME = 3.0f;
	/// @brief �U�����肪�n�܂�܂ł̎���
	const float ATTACK_JUDGEMENT_START_TIME = 0.5f;
	/// @brief �U�����肪�I���܂ł̎���
	const float ATTACK_JUDGEMENT_END_TIME = 1.0f;
}

namespace mainGame {
	namespace player {
		Attack::Attack()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Attack::~Attack()
		{
			m_enemys.clear();

			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				DeleteGO(m_bullets[bulletNum]);
			}

			m_bullets.clear();
		}

		void Attack::Init(Player* pl)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}
			

			//�������
			m_player = pl;
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_attackPower = NORMAL_IMPACT_FORCE;
			m_attackRange = ATTACK_RANGE;
			m_chargeMeleeAttackTime = CHARGE_MELEE_ATTACK_TIME;

			m_bulletReloadTimer = 0.0f;
			m_bulletReloadTime = NORMAL_BULLET_RELOAD_TIME;
			m_maxBulletNum = NORMAL_MAX_BULLET_NUM;
			m_remainingBullets = m_maxBulletNum;
			m_attackPossibleMatchRate = ATTACK_POSSIBLE_MATCH_RATE;

			m_attackEffect.Init(u"Assets/effect/kick.efk");


			//����������
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			m_isAttackStart = false;

			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				m_isAttackJudgement = false;
				m_attackJudgementTimer = 0.0f;
				m_isFollCharge = false;
				return;
			}

			//�v���C���[���U����Ԃ̏ꍇ�c
			if (m_player->GetPlayerStatus() == enPlayerAttack) {
				if (m_attackJudgementTimer == 0.0f) {
					m_isAttackStart = true;
				}
				//�����蔻��̎��Ԃ��v��^�C�}�[��i�߂�
				m_attackJudgementTimer += g_gameTime->GetFrameDeltaTime();

				//�����蔻��̃^�C�}�[�������蔻��̏o�n�߂̎��Ԃ܂Ői�񂾂�c
				if (m_attackJudgementTimer >= ATTACK_JUDGEMENT_START_TIME) {
					//�t���`���[�W��ԂȂ�c
					if (m_isFollCharge == true) {
						//�t���`���[�W�ߐڍU�����s��
						ChargeMeleeAttack();
					}
					//�t���`���[�W��ԂłȂ��Ȃ�c
					else {
						//�ߐڍU�����s��
						MeleeAttack();

					}
					//�����蔻�肪�o�Ă��邱�Ƃɂ���
					m_isAttackJudgement = true;
				}
				//�����蔻��̃^�C�}�[�������蔻��̏o�n�߂̎��Ԃ܂Ői��ł��Ȃ��Ȃ�c
				else {
					//�����蔻�肪�o�Ă��Ȃ����Ƃɂ���
					m_isAttackJudgement = false;
				}

				//�����蔻��̃^�C�}�[�������蔻��̏I�����Ԃ܂Ői�񂾂�c
				if (m_attackJudgementTimer >= ATTACK_JUDGEMENT_END_TIME) {
					//�v���C���[��ҋ@��Ԃɖ߂�
					m_player->SetPlayerState(enPlayerIdle);
					//�����蔻��̃^�C�}�[�����ɖ߂�
					m_attackJudgementTimer = 0.0f;
					//�����蔻�肪�o�Ă��Ȃ����Ƃɂ���
					m_isAttackJudgement = false;

					m_isFollCharge = false;
				}
			}
			else {
				//�����蔻��̃^�C�}�[�����ɖ߂�
				m_attackJudgementTimer = 0.0f;
				//�����蔻�肪�o�Ă��Ȃ����Ƃɂ���
				m_isAttackJudgement = false;

				m_isFollCharge = false;
			}

			//A�{�^����������Ă�����c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA)) {
				

				//�U����ԂłȂ��U���{�^����������ĂȂ�������c
				if (m_player->GetPlayerStatus() != enPlayerAttack && m_isMeleeAttackButtonHold == false) {
					//�U�������s
					m_player->SetPlayerState(enPlayerAttack);
				}

				//�ߐڍU���{�^����������Ă��邱�Ƃɂ���
				m_isMeleeAttackButtonHold = true;
			}

			//�ߐڍU���{�^����������Ă�����c
			if (m_isMeleeAttackButtonHold == true) {
				//�`���[�W���Ԃ�i�߂�
				m_chargeMeleeAttackTimer += g_gameTime->GetFrameDeltaTime();

				//�`���[�W���Ԃ��`���[�W�������Ԃ܂Ői��ōU�����Ŗ���������c
				if (m_chargeMeleeAttackTimer >= m_chargeMeleeAttackTime && m_player->GetPlayerStatus() != enPlayerAttack) {
					//�t���`���[�W��Ԃɂ���
					m_isFollCharge = true;
				}
				//�ߐڍU���{�^���������ꂽ��c
				if (g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA) == false) {
					//�t���`���[�W��Ԃ̏ꍇ�c
					if (m_isFollCharge == true) {
						//�v���C���[���U�����ɕύX
						m_player->SetPlayerState(enPlayerAttack);
					}
					//�ߐڍU���{�^���������ꂽ���Ƃɂ���
					m_isMeleeAttackButtonHold = false;

					m_chargeMeleeAttackTimer = 0.0f;
				}
			}


			//RB1�{�^���Œe�ۂ𔭎�
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB1))
			{
				//�c�e������Δ���
				if (m_remainingBullets > 0) {
					BulletFiring();
				}
			}
			//�c�e���Ȃ��ꍇ�c
			if (m_remainingBullets <= 0) {
				//�����[�h���Ԃ�i�߂�
				m_bulletReloadTimer += g_gameTime->GetFrameDeltaTime();
				//�����[�h�������ԂɒB������c
				if (m_bulletReloadTimer >= m_bulletReloadTime) {
					//�c�e���ő�l�܂ŉ�
					m_remainingBullets = m_maxBulletNum;
					m_bulletReloadTimer = 0.0f;
				}
			}

			BulletExecution();
			m_effectPos = m_player->GetPlayerPosition();
			m_effectRotation.SetRotationY(m_player->GetPlayerAngle());
			m_attackEffect.SetPosition(m_effectPos);
			m_attackEffect.SetRotation(m_effectRotation);
			m_attackEffect.SetScale({ 2.0f,2.0f,2.0f });
			m_attackEffect.Update();
		}

		void Attack::DeleteEnemyData(enemy::Enemy* enemy)
		{
			std::vector<enemy::Enemy*>::iterator it;
			it = std::find(
				m_enemys.begin(),
				m_enemys.end(),
				enemy
			);
			if (it != m_enemys.end()) {
				m_enemys.erase(it);
			}
		}

		void Attack::DeleteBullet(Bullet* bullet)
		{
			std::vector<Bullet*>::iterator it;
			it = std::find(
				m_bullets.begin(),
				m_bullets.end(),
				bullet
			);
			if (it != m_bullets.end()) {
				m_bullets.erase(it);
			}
		}

		void Attack::MeleeAttack()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//�U���\�ȋ����������ꍇ�c
				if (toEnemyPos.Length() < m_attackRange) {
					

					//�G�ւ̃x�N�g���ŏՌ���^����
					toEnemyPos.Normalize();

					float matchRate = Dot(toEnemyPos, m_player->GetPlayerDirection());

					if (matchRate < ATTACK_POSSIBLE_MATCH_RATE) {
						return;
					}

					

					//�G�Ƀ_���[�W��^����
					if (m_enemys[enemyNum]->GetState() == enemy::enEnemyDown) {
						return;
					}

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);

					/*CSoundSource* attackSe = NewGO<CSoundSource>(PRIORITY_VERYLOW);
					attackSe->Init(L"Assets/sound/se/WeakCollide.wav");
					attackSe->SetVolume(1.0f);
					attackSe->Play(false);*/

					//m_attackEffect.Play();
				}
			}
		}

		void Attack::ChargeMeleeAttack()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//�U���\�ȋ����������ꍇ�c
				if (toEnemyPos.Length() < m_attackRange) {

					//�G�ւ̃x�N�g���ŏՌ���^����
					toEnemyPos.Normalize();

					

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * STRONG_IMPACT_FORCE);

					//�G�Ƀ_���[�W��^����
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::BulletFiring()
		{
			m_bullets.push_back(NewGO<Bullet>(PRIORITY_VERYLOW));
			Vector3 startPos = m_player->GetPlayerPosition();
			startPos.y += 50.0f;
			Vector3 targetPos;
			if (m_gameCamera->GetCameraMode() == enCameraModeFps) {
				targetPos = m_gameCamera->GetCameraGazePointPos();
			}
			else {
				targetPos = m_player->GetPlayerPosition() + m_player->GetPlayerDirection();
				targetPos.y = startPos.y;
			}
			m_bullets[m_bullets.size() - 1]->Init(this, &m_enemys, startPos, targetPos);
			m_remainingBullets--;
		}

		void Attack::BulletExecution()
		{
			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				m_bullets[bulletNum]->Execution();
			}

		}
	}
}