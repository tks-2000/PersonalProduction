#pragma once

namespace mainGame {
	namespace ui {
		class BaseEndurance
		{
		public:
			BaseEndurance();
			~BaseEndurance();
			void Init();
			void Execution();

			void SetDamage();
			void ApplyDamage();
		private:

			

			bool m_isInitd = false;

			bool m_hpDown = false;

			Vector3 m_enduranceSpritePos = g_vec3Zero;

			Vector3 m_enduranceSpriteScale = g_vec3One;

			float m_enduranceDeclineAmount = 0.0f;

			Vector4 m_enduranceSpriteColor = g_vec4White;

			render::sprite::SpriteRender* m_enduranceSprite = nullptr;

			render::sprite::SpriteRender* m_enduranceBaseSprite = nullptr;

			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
