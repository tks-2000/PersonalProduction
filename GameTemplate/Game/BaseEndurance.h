#pragma once

namespace mainGame {
	namespace ui {

		/// @brief –h‰q‘ÎÛ‚Ì‘Ï‹v—Í‚ğ•\¦‚·‚éƒNƒ‰ƒX
		class BaseEndurance
		{
		public:
			BaseEndurance();
			~BaseEndurance();
			/// @brief ‰Šú‰»
			void Init();

			/// @brief Às
			void Execution();

			/// @brief ƒ_ƒ[ƒW‚ğ“K—p
			void ApplyDamage();
			
			/// @brief UI‚ğ”ñ•\¦
			void HIdeUI();
		private:
			/// @brief ‰Šú‰»ƒtƒ‰ƒO
			bool m_isInitd = false;

			/// @brief ‘Ï‹v—Í‚Ì‰æ‘œˆÊ’u
			Vector3 m_enduranceSpritePos = g_vec3Zero;
			/// @brief ‘Ï‹v—Í‚Ì‰æ‘œ‚ÌŠg‘å—¦
			Vector3 m_enduranceSpriteScale = g_vec3One;
			/// @brief ‘Ï‹v—Í‚Ì‰æ‘œ‚ÌƒJƒ‰[
			Vector4 m_enduranceSpriteColor = g_vec4White;
			/// @brief ‘Ï‹v—Í‚Ì‰º’n‚Ì‰æ‘œ
			render::sprite::SpriteRender* m_enduranceBaseSprite = nullptr;
			/// @brief ‘Ï‹v—Í‚Ì‰º’n‚Ì˜g‰æ‘œ
			render::sprite::SpriteRender* m_enduranceBaseFrame = nullptr;
			/// @brief ‘Ï‹v—Í‚Ì‰æ‘œ
			render::sprite::SpriteRender* m_enduranceSprite = nullptr;
			/// @brief ‘Ï‹v—Í‚Ì‰º‚Ì‰æ‘œ
			render::sprite::SpriteRender* m_enduranceUnderSprite = nullptr;
			/// @brief –h‰q‘ÎÛ
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
			/// @brief ƒQ[ƒ€ƒV[ƒ“
			GameScene* m_gameScene = nullptr;
		};
	}
}
