#pragma once
#include "Lighting.h"
class AnimationClip;
class RenderingEngine;
class Lighting;
class Shadow;

namespace mainGame {
	namespace map {
		class MiniMap;
	}
}
namespace render {
	namespace model {
		enum EnModelDrawTarget {
			enMainRenderTarget,
			enMiniMapRenderTarget,
		};
		
		/// @brief 3Dモデルの表示を行うクラス
		class SkinModelRender : public IGameObject
		{
		public:
			SkinModelRender();
			~SkinModelRender();

			bool Start();
			void Update();

			/// @brief モデルの状態を入手
			/// @return モデルのconst参照
			Model& GetModel(){ return m_model; }



			/// @brief モデルの座標を設定
			/// @param pos 座標
			void SetPosition(const Vector3& pos) { m_position = pos; }

			/// @brief モデルの大きさを設定
			/// @param scale 拡大率
			void SetScale(const Vector3& scale) { m_scale = scale; }

			/// @brief モデルの回転を設定
			/// @param rot クォータニオン
			void SetRotation(const Quaternion& rot) { m_qRot = rot; }

			/// @brief モデルの座標を入手
			/// @return 座標
			Vector3 GetPosition() { return m_position; }

			/// @brief モデルの初期化
			/// @param modelFilePath モデルのファイルパス
			//void Init(const char* modelFilePath);

			/// @brief モデルを初期化
			/// @param modelFilePath モデルのファイルパス
			/// @param skeletonPath スケルトンのファイルパス
			/// @param animationClip アニメーションクリップ
			/// @param animationNum アニメーションの数
			/// @param enAxsis モデルの上方向
			void Init(
				const char* modelFilePath,
				const EnModelDrawTarget& drawTarget = enMainRenderTarget,
				const char* skeletonPath = nullptr,
				AnimationClip* animationClip = nullptr,
				int animationNum = 0,
				EnModelUpAxis enAxsis = enModelUpAxisZ
			);

			/// @brief モデルのシェーダーファイルパスを変更
			/// @param fxFilePath シェーダーファイルパス
			void ChangeFxFilePath(const char* fxFilePath) { m_modelInitData.m_fxFilePath = fxFilePath; m_model.Init(m_modelInitData); }

			/// @brief 影を生成する
			void CreateShadow();

			/// @brief アニメーションを再生する
			/// @param animNo 再生するアニメーション番号
			/// @param interpolateTime アニメーション補完率
			void PlayAnimation(const int animNo, const float interpolateTime = 0.0f);

			/// @brief スキンモデルレンダラーのワールド行列を取得
			/// @return モデルのワールド行列
			Matrix GetModelWorldMatrix() { return m_model.GetWorldMatrix(); }

			/// @brief 実行
			void Execution();

		private:
			/// @brief モデルのファイルパス
			const char* m_modelFilePath = nullptr;
			/// @brief スケルトンのファイルパス
			const char* m_skeletonFilePath = nullptr;
			/// @brief モデル
			Model m_model;
			/// @brief モデルの初期化情報
			ModelInitData m_modelInitData;


			/// @brief モデルに設定するスケルトン
			Skeleton m_skeleton;
			/// @brief アニメーション
			Animation m_animation;
			/// @brief アニメーションクリップ
			AnimationClip* m_animationClip;

			/// @brief 影を生成するかどうかのフラグ
			bool m_shadowFlag = false;
			/// @brief 影描写用のモデル
			Model m_shadowModel;
			/// @brief 影描写用のモデル初期化情報
			ModelInitData m_shadowModelInitData;
			//レンダリングエンジン
			RenderingEngine* m_renderingEngine = nullptr;
			/// @brief ライティング
			light::Lighting* m_lig = nullptr;
			/// @brief シャドウ
			shadow::Shadow* m_shadow = nullptr;

			Vector3 m_position = Vector3::Zero;			//座標
			Vector3 m_scale = Vector3::One;				//拡大率
			Quaternion m_qRot = Quaternion::Identity;	//回転


			/// @brief アニメーションを再生するかどうかのフラグ
			bool m_animFlag = false;

			/// @brief 初期化完了フラグ
			bool m_isInitd = false;

			mainGame::map::MiniMap* m_miniMap = nullptr;

			EnModelDrawTarget m_target = enMainRenderTarget;
		};
	}
}