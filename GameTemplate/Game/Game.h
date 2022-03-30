#pragma once


class SkinModelRender;
class SpriteRender;
class Effect;
class CSoundSource;


namespace nsAI {
	class NaviMesh;
	class Path;
	class PathFinding;
}

namespace sound {
	class SoundPlayer;
}

namespace mainGame {
	namespace title {
		class Title;
	}
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
	
	class GameScene;

	class GameCamera;

	class SceneTransition;

	/// @brief �Q�[���̏�Ԃ�\���񋓌^
	enum EnGameState {
		/// @brief �^�C�g�����
		enTitleScene,
		/// @brief �Q�[���i�s��
		enGameInProgress,
		/// @brief �Q�[���̏�Ԃ�\���X�e�[�g�̐�
		enGameStateNum
	};

	/// @brief �Q�[���S�̗̂���𐧌䂷��N���X
	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		
		/// @brief �J�n���̏���
		/// @return 
		bool Start();
		/// @brief �X�V
		void Update();

		/// @brief �^�C�g���V�[���J�n�̏���
		void TitleSceneStart();
		/// @brief �^�C�g���V�[���폜�̏���
		void DeleteTitleScene(); 
		/// @brief �Q�[���V�[���J�n�̏���
		void GameSceneStart();
		/// @brief �Q�[���V�[���폜�̏���
		void DeleteGameScene();

		/// @brief �Q�[���̏�Ԃ�ύX
		/// @param state �Q�[���̏�Ԃ�\���X�e�[�g
		void SetGameState(const EnGameState& state) { m_state = state; }

		/// @brief �Q�[���̏�Ԃ��擾
		/// @return �Q�[���̏�Ԃ�\���X�e�[�g
		const EnGameState& GetGameState() { return m_state; }

		

	private:
		

		/// @brief �������t���O
		bool m_isInitd = false;
		/// @brief �Q�[���̏�Ԃ�\���X�e�[�g
		EnGameState m_state = enGameStateNum;
		/// @brief �^�C�g��
		title::Title* m_title = nullptr;
		/// @brief �Q�[���V�[��
		GameScene* m_gameScene = nullptr;
		/// @brief �T�E���h�v���C���[
		sound::SoundPlayer* m_soundPlayer = nullptr;
		/// @brief �����_�����O�G���W��
		render::RenderingEngine* m_renderingEngine = nullptr;
		/// @brief �V�[���J��
		SceneTransition* m_sceneTransition = nullptr;
	};

}