#include "stdafx.h"
#include "ItemGenerator.h"
#include <random>

namespace mainGame {
	namespace item {
		/// @brief �A�C�e���̏o���m��
		const int ITEM_SPAWN_PROBABILITY = 4;

		ItemGenerator::ItemGenerator()
		{
			m_isInitd = false;
		}

		ItemGenerator::~ItemGenerator()
		{
			//�z��̒��g��S�č폜
			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				DeleteGO(m_items[itemNum]);
			}
			//�z����N���A
			m_items.clear();
		}

		void ItemGenerator::Init()
		{
			//�g�p������������ė���
			m_game = FindGO<Game>(GAME_NAME);
			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);
			m_enemys = m_enemyGenerator->GetEnemys();

			//����������
			m_isInitd = true;
		}

		void ItemGenerator::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�Q�[�����łȂ��ꍇ�͎��s���Ȃ�
			if (m_game->GetGameState() != enGameInProgress) {
				return;
			}

			//�o��������s��
			SpawnJudgement();

			//�A�C�e���̐��������������s����
			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				m_items[itemNum]->Execution();
			}

		}

		void ItemGenerator::SpawnItem(const EnItemType& itemType, const Vector3& pos)
		{
			//�A�C�e���̎�ނŏ����𕪂���
			switch (itemType)
			{
				//���e
			case enItemBomb: {
				//���e���쐬
				m_items.push_back(NewGO<Bomb>(PRIORITY_VERYLOW));
			}break;
				//�C������
			case enItemRepairTools: {
				//�C��������쐬
				m_items.push_back(NewGO<RepairTools>(PRIORITY_VERYLOW));
			}break;
				//�h�{�h�����N
			case enItemNutritionDrink: {
				//�h�{�h�����N���쐬
				m_items.push_back(NewGO<NutritionDrink>(PRIORITY_VERYLOW));
			}break;
			default:{
				return;
			}break;
			}

			//�쐬�����A�C�e����������
			m_items[m_items.size() - 1]->Init(this,pos);

		}

		void ItemGenerator::DeleteItem(Item* item)
		{
			//�A�C�e���̃C�e���[�^��p�ӂ���
			std::vector<Item*>::iterator it;

			//�A�C�e���̃A�h���X����폜����A�C�e���̃C�e���[�^��������
			it = std::find(
				m_items.begin(),
				m_items.end(),
				item
			);
			//�C�e���[�^���Ō���łȂ��ꍇ�c
			if (it != m_items.end()) {
				//�C�e���[�^���g���Ĕz�񂩂�폜
				m_items.erase(it);
			}
		}

		void ItemGenerator::SpawnJudgement()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�����j����Ă�����c
				if (enemyData->IsDefeat() == true) {
					//�����_���Ȑ��l�𐶐�����
					std::random_device rnd;
					int num = rnd();
					//���l��0�����̏ꍇ�c
					if (num < 0) {
						//-1����Z�����̐��ɂ���
						num *= -1;
					}

					//�o���m���ŏ��Z�����]�肪0�̂Ƃ��c
					if (num % ITEM_SPAWN_PROBABILITY == 0) {

						//�A�C�e���̎�ނ̐��ŏ��Z�����]��̐��̃A�C�e���𐶐�����
						switch (num % enItemTypeNum)
						{
							//���e
						case enItemBomb: {
							//���e���o��������
							SpawnItem(enItemBomb, enemyData->GetPosition());
						}break;
							//�C������
						case enItemRepairTools: {
							//�C��������o��������
							SpawnItem(enItemRepairTools, enemyData->GetPosition());
						}break;
							//�h�{�h�����N
						case enItemNutritionDrink: {
							//�h�{�h�����N���o��������
							SpawnItem(enItemNutritionDrink, enemyData->GetPosition());
						}
						default:
							break;
						}
						
					}
				}
			}
		}
	}
}