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

	/// @brief �Q�[���̏�Ԃ�\���񋓌^
	enum EnGameState {
		/// @brief �^�C�g�����
		enTitleScene,
		/// @brief �Q�[���i�s��
		enGameInProgress,
		/// @brief �Q�[���̏�Ԃ�\���X�e�[�g�̐�
		enGameStateNum
	};

	/// @brief �Q�[�����̗���𐧌䂷��N���X
	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		/// @brief ������
		void Init();

		bool Start();
		void Update();

		void TitleSceneStart();

		void DeleteTitleScene(); 

		void GameSceneStart();

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

		EnGameState m_state = enGameStateNum;

		title::Title* m_title = nullptr;

		GameScene* m_gameScene = nullptr;

		sound::SoundPlayer* m_soundPlayer = nullptr;

		render::RenderingEngine* m_renderingEngine = nullptr;
	};

}