#pragma once

class CSoundSource;


namespace mainGame {

	class Game;

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

	/// @brief �Q�[���V�[���̏�Ԃ�\���X�e�[�g
	enum EnGameSceneState {
		/// @brief �Q�[���J�n����̃J�E���g��
		enGameSceneStart,
		/// @brief �Q�[�����v���C��
		enGameSceneInProgress,
		/// @brief �Q�[���N���A
		enGameSceneClear,
		/// @brief �Q�[���I�[�o�[
		enGameSceneOver,
		/// @brief �Q�[���V�[���̃X�e�[�g�̐�
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

		const EnGameSceneState& GetGameSceneState() { return m_gameSceneState; }

		void SetGameSceneState(const EnGameSceneState& state) { m_gameSceneState = state; }

	private:
		void CreateGameScene();
		void DeleteGameScene();

		void GameSceneEnd();

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

		Game* m_game = nullptr;
	};
}
