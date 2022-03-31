#pragma once

namespace mainGame {
	namespace title {
		/// @brief タイトル画面のプレイヤーのアニメーション
		enum EnTitlePlAnim {
			enTitlePlIdle,
			enTitlePlClear,
			enTitlePlAnimNum
		};

		/// @brief タイトル画面に出すモデルを制御するクラス
		class Models
		{
		public:
			Models();
			~Models();
			/// @brief 初期化
			/// @param title タイトルのアドレス
			void Init(Title* title);
			/// @brief 実行
			void Execution();
			/// @brief プレイヤーのアニメーションを設定
			/// @param state アニメーションのステート
			void SetTitlePlayerAnimState(const EnTitlePlAnim& state) { m_plAnimState = state; }
		private:
			/// @brief 武器のモデルを設定
			void SetWeapons();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief プレイヤーのモデル
			render::model::SkinModelRender* m_plModel = nullptr;
			/// @brief プレイヤーモデルの座標
			Vector3 m_plModelPos = g_vec3Zero;
			/// @brief プレイヤーのアニメーションクリップ
			AnimationClip m_plAnim[enTitlePlAnimNum];
			/// @brief プレイヤーのアニメーションステート
			EnTitlePlAnim m_plAnimState = enTitlePlIdle;
			/// @brief 剣のモデル
			render::model::SkinModelRender* m_swordModel = nullptr;
			/// @brief 盾のモデル
			render::model::SkinModelRender* m_shieldModel = nullptr;
			/// @brief モデルの数
			enum {MODEL_NUM = 2};
			/// @brief エネミーのモデル
			render::model::SkinModelRender* m_enemyModel[MODEL_NUM] = { nullptr };
			/// @brief エネミーのモデルの座標
			Vector3 m_enemyModelPos[MODEL_NUM] = { g_vec3Zero,g_vec3Zero };
			/// @brief タイトル画面のエネミーのアニメーション
			enum EnTitleEnemyAnim {
				enTitleEnemyIdle,
				enTitleEnemyAnimNum,
			};
			/// @brief エネミーのアニメーションクリップ
			AnimationClip m_enemyAnim[enTitleEnemyAnimNum];
			/// @brief ステージのモデル
			render::model::SkinModelRender* m_stageModel = nullptr;
			/// @brief 背景のモデル
			render::model::SkinModelRender* m_backgroundModel = nullptr;
			/// @brief 防衛対象のモデル
			render::model::SkinModelRender* m_houseModel = nullptr;
			/// @brief タイトル
			Title* m_title = nullptr;
		};
	}
}
