#pragma once
#include "Lighting.h"
class AnimationClip;
class Lighting;

namespace Render {
	/// @brief 3Dモデルの表示を行うクラス
	class SkinModelRender : public IGameObject
	{
	public:
		SkinModelRender();
		~SkinModelRender();

		bool Start();
		void Update();
		void Render(RenderContext& rc);

		Model& GetModel() { return m_model; }




		/// @brief モデルの座標を設定
		/// @param pos 座標
		void SetPosition(const Vector3& pos) { m_position = pos; }

		/// @brief モデルの大きさを設定
		/// @param scale 拡大率
		void SetScale(const Vector3& scale) { m_scale = scale; }

		/// @brief モデルの回転を設定
		/// @param rot クォータニオン
		void SetRotation(const Quaternion& rot) { m_qRot = rot; }


		void SetNewModel() { m_model.Init(m_modelInitData); }

		/// @brief モデルの座標を入手
		/// @return 座標
		Vector3 GetPosition() { return m_position; }


		/// @brief モデルの初期化
		/// @param modelFilePath モデルのファイルパス
		/// @param lig ライティング構造体のアドレス
		void Init(const char* modelFilePath, Render::Light* lig);

		/// @brief モデルの初期化
		/// @param modelFilePath モデルのファイルパス
		void Init(const char* modelFilePath);

		void InitA(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis enAxis, AnimationClip* animation, int animationNum, bool cullMode);

		void PlayAnimation(int animNo, float interpolateTime);

		/// @brief スキンモデルレンダラーのワールド行列を取得
		/// @return モデルのワールド行列
		Matrix GetModelWorldMatrix() { return m_model.GetWorldMatrix(); }

	private:
		Model m_model;								//モデル
		ModelInitData m_modelInitData;				//モデルの初期化情報
		Lighting* m_lig = nullptr;					//ライティング
		Vector3 m_position = Vector3::Zero;			//座標
		Vector3 m_scale = Vector3::One;				//拡大率
		Quaternion m_qRot = Quaternion::Identity;	//回転

		Skeleton m_skeleton;
		Animation m_animation;
		AnimationClip* m_animationClip;
	};

}