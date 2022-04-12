#pragma once

namespace mainGame {
	namespace item {
		/// @brief �A�C�e���̃G�t�F�N�g������
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();
			/// @brief ������
			/// @param item �A�C�e���̃A�h���X
			void Init(Item* item);
			/// @brief ���s
			void Execution();

		private:
			/// @brief �o���G�t�F�N�g�̏���
			void PlaySpawnEffect();
			/// @brief ����G�t�F�N�g�̏���
			void PlayGetEffect();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �o���G�t�F�N�g�̍Đ��t���O
			bool m_isSpawnEffectPlay = false;
			/// @brief �o���G�t�F�N�g
			render::effect::EffectRender* m_spawnEffect = nullptr;
			/// @brief ����G�t�F�N�g�̍Đ��t���O
			bool m_isGetEffectPlay = false;
			/// @brief ����G�t�F�N�g
			render::effect::EffectRender* m_getEffect = nullptr;
			/// @brief ����G�t�F�N�g�̊g�嗦
			Vector3 m_getEffectScale = g_vec3Zero;
			/// @brief �A�C�e��
			Item* m_item = nullptr;
		};
	}
}
