#pragma once

class SkinModelRender;
class SpriteRender;
class CSoundSource;
;
namespace nsAI {
	class NaviMesh;
	class Path;
	class PathFinding;
}

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

	class GameCamera;

	/// @brief �Q�[���̏�Ԃ�\���񋓌^
	enum EnGameState {
		/// @brief �Q�[���J�n�O
		enGameStart,
		/// @brief �Q�[���i�s��
		enGameInProgress,
		/// @brief �Q�[���N���A
		enGameClear,
		/// @brief �Q�[���I�[�o�[
		enGameOver,
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

		/// @brief �Q�[���̏�Ԃ�ύX
		/// @param state �Q�[���̏�Ԃ�\���X�e�[�g
		void SetGameState(const EnGameState& state) { m_state = state; }

		/// @brief �Q�[���̏�Ԃ��擾
		/// @return �Q�[���̏�Ԃ�\���X�e�[�g
		const EnGameState& GetGameState() { return m_state; }


	private:
		/// @brief �Q�[���J�n���̏���
		void GameStartExecution();
		/// @brief �Q�[���v���C���̏���
		void InGameExecution();
		/// @brief �Q�[���N���A���̏���
		void GameClearExecution();
		/// @brief �Q�[���I�[�o�[���̏���
		void GameOverExecution();
		/// @brief �Q�[�����̃I�u�W�F�N�g��S�č쐬
		void AllNew();
		/// @brief �Q�[�����̃I�u�W�F�N�g��S�č폜
		void AllDelete();
		/// @brief �|�[�Y���̏���
		void Pause();

		/// @brief �������t���O
		bool m_isInitd = false;

		render::model::SkinModelRender* m_unityChanModel = nullptr;
		render::model::SkinModelRender* m_unityChanModel2 = nullptr;
		render::model::SkinModelRender* m_backGroundModel = nullptr;
		render::model::SkinModelRender* m_backGroundModel2 = nullptr;

		render::sprite::SpriteRender* m_sampleSprite = nullptr;
		render::font::FontRender* m_sampleFont = nullptr;
		Vector3 m_pos = g_vec3Zero;

		Quaternion m_qRot = g_quatIdentity;

		Quaternion m_qRot2 = g_quatIdentity;

		enum UnityChanAnimation {
			enIdle,
			enWark,
			enAnimationNum
		};

		AnimationClip m_unityChanAnimationClip[enAnimationNum];

		EnGameState m_state = enGameStart;


		bool m_isDead = false;

		bool m_pause = false;

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

		CSoundSource* m_sound = nullptr;

		nsAI::NaviMesh m_nvmMesh;
		nsAI::Path m_path;
		nsAI::PathFinding m_pathFinding;
	};

}