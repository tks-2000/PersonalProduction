#pragma once

namespace mainGame {
	namespace player {

		struct EffectData
		{
			Effect effect;
			Vector3 pos = g_vec3Zero;
			Quaternion qRot = Quaternion::Identity;
			Vector3 scale = g_vec3One;
			
		};

		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();
			void Init(Player* player);
			void Execution();
		private:

			void UpdateEffect(EffectData& effectData);

			bool m_isInitd = false;

			EffectData m_attackEffect;

			Player* m_player = nullptr;
		};
	}
}
