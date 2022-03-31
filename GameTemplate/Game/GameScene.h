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
		/// @brief ������
		void Init();

		/// @brief ���s
		void Execution();

		/// @brief �Q�[���V�[���̃X�e�[�g���擾
		/// @return �Q�[���V�[���̃X�e�[�g��const�Q��
		const EnGameSceneState& GetGameSceneState() { return m_gameSceneState; }

		/// @brief �Q�[���V�[���̃X�e�[�g��ݒ�
		/// @param state �Q�[���V�[���ɐݒ肷��X�e�[�g
		void SetGameSceneState(const EnGameSceneState& state) { m_gameSceneState = state; }

	private:
		
		/// @brief �Q�[���V�[�����I�����鏈��
		void GameSceneEnd();

		/// @brief �������t���O
		bool m_isInitd = false;
		/// @brief �ꎟ��~�t���O
		bool m_pause = false;
		/// @brief �Q�[���V�[���̏�Ԃ�\���X�e�[�g
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
		/// @brief �A�C�e��������
		item::ItemGenerator* m_itemGenerator = nullptr;
		/// @brief UI
		ui::GameUI* m_gameUI = nullptr;
		/// @brief �T�E���h�v���C���[
		sound::SoundPlayer* m_soundPlayer = nullptr;
		/// @brief �N���A���̃T�E���hID
		int m_clearSoundID = 0;
		/// @brief �Q�[���I�[�o�[���̃T�E���hID
		int m_gameOverSoundID = 0;
		/// @brief �{�^�����������Ƃ��̃T�E���hID
		int m_pressKeySoundID = 0;
		/// @brief �I�����̃T�E���h���Đ����ꂽ�t���O
		bool m_isPlayEndSound = false;
		/// @brief �摜
		render::sprite::SpriteRender* m_sampleSprite = nullptr;
		/// @brief �Q�[��
		Game* m_game = nullptr;
		/// @brief �V�[���J��
		SceneTransition* m_sceneTransition = nullptr;
		/// @brief �I���t���O
		bool m_endFlag = false;
		/// @brief �{�^���������悤�ɑ����t�H���g
		render::font::FontRender* m_pressKeyFont = nullptr;
		/// @brief �t�H���g�J���[
		Vector4 m_pressKeyFontColor = { 0.0f,0.0f,0.0f,0.0f };
	};
}
