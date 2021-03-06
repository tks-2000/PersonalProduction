#pragma once

namespace mainGame {
	namespace ui {

		/// @brief hqÎÛÌÏvÍð\¦·éNX
		class BaseEndurance
		{
		public:
			BaseEndurance();
			~BaseEndurance();
			/// @brief ú»
			void Init();

			/// @brief Às
			void Execution();

			/// @brief _[WðKp
			void ApplyDamage();
			
			/// @brief UIðñ\¦
			void HIdeUI();
		private:
			/// @brief ú»tO
			bool m_isInitd = false;

			/// @brief ÏvÍÌæÊu
			Vector3 m_enduranceSpritePos = g_vec3Zero;
			/// @brief ÏvÍÌæÌgå¦
			Vector3 m_enduranceSpriteScale = g_vec3One;
			/// @brief ÏvÍÌæÌJ[
			Vector4 m_enduranceSpriteColor = g_vec4White;
			/// @brief ÏvÍÌºnÌæ
			render::sprite::SpriteRender* m_enduranceBaseSprite = nullptr;
			/// @brief ÏvÍÌºnÌgæ
			render::sprite::SpriteRender* m_enduranceBaseFrame = nullptr;
			/// @brief ÏvÍÌæ
			render::sprite::SpriteRender* m_enduranceSprite = nullptr;
			/// @brief ÏvÍÌºÌæ
			render::sprite::SpriteRender* m_enduranceUnderSprite = nullptr;
			/// @brief hqÎÛ
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
			/// @brief Q[V[
			GameScene* m_gameScene = nullptr;
		};
	}
}
