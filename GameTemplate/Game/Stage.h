#pragma once

class SkinModelRender;

namespace mainGame {
	namespace stage {
		/// @brief ステージの情報をまとめたクラス
		class Stage : public IGameObject
		{
		public:
			Stage();
			~Stage();
			void Init();
			void Execution();
		private:

			bool m_isInitd = false;

			Vector3 m_position = g_vec3Zero;

			Quaternion m_qRot = g_quatIdentity;

			Vector3 m_scale = g_vec3One;

			render::model::SkinModelRender* m_stageModel = nullptr;

			PhysicsStaticObject m_staticStageObject;
		};
	}
}
