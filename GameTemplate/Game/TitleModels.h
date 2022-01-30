#pragma once

namespace mainGame {
	namespace title {

		enum EnTitlePlAnim {
			enTitlePlIdle,
			enTitlePlClear,
			enTitlePlAnimNum
		};

		class Models
		{
		public:
			Models();
			~Models();
			void Init(Title* title);
			void Execution();

			void SetTitlePlayerAnimState(const EnTitlePlAnim& state) { m_plAnimState = state; }
		private:
			void SetWeapons();

			bool m_isInitd = false;

			render::model::SkinModelRender* m_plModel = nullptr;

			Vector3 m_plModelPos = g_vec3Zero;

			

			AnimationClip m_plAnim[enTitlePlAnimNum];

			EnTitlePlAnim m_plAnimState = enTitlePlIdle;

			/// @brief åïÇÃÉÇÉfÉã
			render::model::SkinModelRender* m_swordModel = nullptr;
			/// @brief èÇÇÃÉÇÉfÉã
			render::model::SkinModelRender* m_shieldModel = nullptr;


			enum {MODEL_NUM = 2};

			render::model::SkinModelRender* m_enemyModel[MODEL_NUM] = { nullptr };

			Vector3 m_enemyModelPos[MODEL_NUM] = { g_vec3Zero,g_vec3Zero };

			enum EnTitleEnemyAnim {
				enTitleEnemyIdle,
				enTitleEnemyAnimNum,
			};

			AnimationClip m_enemyAnim[enTitleEnemyAnimNum];

			render::model::SkinModelRender* m_stageModel = nullptr;

			render::model::SkinModelRender* m_backgroundModel = nullptr;

			Title* m_title = nullptr;
		};
	}
}
