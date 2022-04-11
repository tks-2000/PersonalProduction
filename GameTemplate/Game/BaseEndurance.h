#pragma once

namespace mainGame {
	namespace ui {

		/// @brief �h�q�Ώۂ̑ϋv�͂�\������N���X
		class BaseEndurance
		{
		public:
			BaseEndurance();
			~BaseEndurance();
			/// @brief ������
			void Init();

			/// @brief ���s
			void Execution();

			/// @brief �_���[�W��K�p
			void ApplyDamage();
			
			/// @brief UI���\��
			void HIdeUI();
		private:
			/// @brief �������t���O
			bool m_isInitd = false;

			/// @brief �ϋv�͂̉摜�ʒu
			Vector3 m_enduranceSpritePos = g_vec3Zero;
			/// @brief �ϋv�͂̉摜�̊g�嗦
			Vector3 m_enduranceSpriteScale = g_vec3One;
			/// @brief �ϋv�͂̉摜�̃J���[
			Vector4 m_enduranceSpriteColor = g_vec4White;
			/// @brief �ϋv�͂̉��n�̉摜
			render::sprite::SpriteRender* m_enduranceBaseSprite = nullptr;
			/// @brief �ϋv�͂̉��n�̘g�摜
			render::sprite::SpriteRender* m_enduranceBaseFrame = nullptr;
			/// @brief �ϋv�͂̉摜
			render::sprite::SpriteRender* m_enduranceSprite = nullptr;
			/// @brief �ϋv�͂̉��̉摜
			render::sprite::SpriteRender* m_enduranceUnderSprite = nullptr;
			/// @brief �h�q�Ώ�
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
			/// @brief �Q�[���V�[��
			GameScene* m_gameScene = nullptr;
		};
	}
}
