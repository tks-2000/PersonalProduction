#pragma once
class SkinModelRender;

namespace mainGame {
	namespace defensiveTarget {
		/// @brief –h‰q‘ÎÛ‚Ì‹@”\‚ğ‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX
		class DefensiveTarget : public IGameObject
		{
		public:
			DefensiveTarget();
			~DefensiveTarget();

			/// @brief ‰Šú‰»
			void Init();

			/// @brief Às
			void Execution();

			/// @brief ƒ_ƒ[ƒW‚ğó‚¯‚é
			/// @param damage ó‚¯‚éƒ_ƒ[ƒW—Ê
			void ReceiveDamage(const int damage) { m_defensiveTargetHp -= damage; }

			/// @brief –h‰q‘ÎÛ‚Ì‘Ï‹v—Í‚ğæ“¾
			/// @return –h‰q‘ÎÛ‚Ìc‚è‘Ï‹v—Í
			int GetDefensiveTargetHp() { return m_defensiveTargetHp; }

			/// @brief –h‰q‘ÎÛ‚ª”j‰ó‚³‚ê‚½‚©H
			/// @return true‚Å”j‰ó‚³‚ê‚½ false‚Å”j‰ó‚³‚ê‚Ä‚¢‚È‚¢
			bool IsBreak() { return m_isBreak; }
		private:
			/// @brief ‰Šú‰»ƒtƒ‰ƒO
			bool m_isInitd = false;
			/// @brief À•W
			Vector3 m_position = g_vec3Zero;
			/// @brief Šg‘å—¦
			Vector3 m_scale = g_vec3One;
			/// @brief ‘Ï‹v—Í
			int m_defensiveTargetHp = 0;
			/// @brief ”j‰óƒtƒ‰ƒO
			bool m_isBreak = false;

			/// @brief ƒ‚ƒfƒ‹
			render::model::SkinModelRender* m_defensiveTargetModel = nullptr;

			PhysicsStaticObject m_staticDefensiveTargetObject;
		};
	}
}