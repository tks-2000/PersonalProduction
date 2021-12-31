#pragma once

class CSoundSource;


namespace mainGame {

	namespace player {
		class Player;
	}
	namespace defensiveTarget {
		class DefensiveTarget;
	}
	namespace enemy {
		class Generator;
		class Enemy;
	}
	namespace stage {
		class Stage;
	}
	namespace timer {
		class Timer;
	}
	namespace map {
		class MiniMap;
	}
	namespace item {
		class ItemGenerator;
	}
	namespace ui {
		class GameUI;
	}

	enum EnGameSceneState {
		enGameSceneStart,
		enGameSceneInProgress,
		enGameSceneClear,
		enGameSceneOver,
		enGameSceneNum
	};

	/// @brief �Q�[���V�[���ŏo�����镨���Ǘ�����N���X
	class GameScene : public IGameObject
	{

	public:
		GameScene();
		~GameScene();
		void Init();
		void Execution();

	private:
		void CreateGameScene();
		void DeleteGameScene();

		bool m_isInitd = false;

		bool m_pause = false;

		EnGameSceneState m_gameSceneState = enGameSceneNum;

		/// @brief �Q�[���J����
		GameCamera* m_gameCamera = nullptr;
		/// @brief �v���C���[
		player::Player* m_player = nullptr;
		/// @brief �h�q�Ώ�
		defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		/// @brief �G������
		enemy::Generator* m_enemyGenerator = nullptr;
		/// @brief �X�e�[�W
		stage::Stage* m_stage = nullptr;
		/// @brief �^�C�}�[
		timer::Timer* m_timer = nullptr;
		/// @brief �����_�����O�G���W��
		render::RenderingEngine* m_renderingEngine = nullptr;

		map::MiniMap* m_miniMap = nullptr;

		item::ItemGenerator* m_itemGenerator = nullptr;

		ui::GameUI* m_gameUI = nullptr;

		CSoundSource* m_sound = nullptr;

		render::sprite::SpriteRender* m_sampleSprite = nullptr;
	};
}
