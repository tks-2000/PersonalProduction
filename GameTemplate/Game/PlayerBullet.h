#pragma once

class SkinModelRender;

namespace mainGame {
	namespace player {

		class Attack;

		/// @brief プレイヤーの弾丸を制御するクラス
		class Bullet : public IGameObject
		{
		public:
			Bullet();
			~Bullet();

			/// @brief 初期化
			/// @param plAttack 生成元のプレイヤーの攻撃を制御するクラスのアドレス
			/// @param enemys 弾丸と当たり判定を取る敵クラスの配列
			/// @param pos 弾丸の初期位置
			/// @param target 弾丸の進む位置
			void Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos,const Vector3& target);

			/// @brief 実行
			void Execution();

			/// @brief 座標を入手
			/// @return 座標のconst参照
			const Vector3& GetPosition()const { return m_position; }
		private:
			/// @brief 移動する
			void MoveExecution();
			/// @brief 敵と接触する
			void EnemyCollision();
			/// @brief 自身を削除
			void DeleteThis();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 初期位置
			Vector3 m_startPos = g_vec3Zero;
			/// @brief 座標
			Vector3 m_position = g_vec3Zero;
			/// @brief 目標の座標
			Vector3 m_target = g_vec3Zero;
			/// @brief 移動方向
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief 移動速度
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief 弾丸のモデル
			render::model::SkinModelRender* m_bulletModel = nullptr;
			/// @brief 敵のアドレスの配列
			std::vector<enemy::Enemy*>* m_enemys = nullptr;
			/// @brief プレイヤーの攻撃を制御するクラス
			Attack* m_playerAttack = nullptr;

			render::effect::EffectRender* m_shotEffect = nullptr;
		};
	}
}
