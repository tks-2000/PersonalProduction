#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace ui {

		/// @brief ���L�A�C�e����\������N���X
		class OwnedItem
		{
		public:
			OwnedItem();
			~OwnedItem();
			void Init();
			void Execution();

		private:
			/// @brief �A�C�e���摜���쐬
			/// @param slotNum �쐬����X���b�g�ԍ�
			void CreateItemSprite(const int slotNum);

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �A�C�e���X���b�g�̉��n�̉摜
			render::sprite::SpriteRender* m_itemSlotBaseSprite = nullptr;

			render::sprite::SpriteRender* m_itemSlotBaseFrame = nullptr;
			/// @brief �A�C�e���X���b�g�̉摜
			render::sprite::SpriteRender* m_itemSlotSprite[3] = { nullptr };
			/// @brief �A�C�e���̉摜
			render::sprite::SpriteRender* m_itemSprite[3] = { nullptr };
			/// @brief �A�C�e���̉摜�̕\���t���O
			bool m_itemSpriteFlag[3] = { false };
			/// @brief �v���C���[���I�����Ă���A�C�e���������摜
			render::sprite::SpriteRender* m_selectSprite = nullptr;

			

			

			player::Player* m_player = nullptr;
			

			Vector3 m_selectSpritePos = g_vec3Zero;
		};
	}
}
