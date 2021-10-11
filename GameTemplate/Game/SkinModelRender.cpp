#include "stdafx.h"
#include "SkinModelRender.h"

namespace render {
	namespace model {
		SkinModelRender::SkinModelRender()
		{
			m_renderingEngine = FindGO<RenderingEngine>(RENDERING_ENGINE_NAME);
			m_lig = FindGO<light::Lighting>(light::LIGHTING_NAME);
			m_shadow = FindGO<shadow::Shadow>(shadow::SHADOW_NAME);
			m_shadowFlag = false;
			m_animFlag = false;
			m_modelFilePath = nullptr;
			m_skeletonFilePath = nullptr;
			m_isInitd = false;
		}

		SkinModelRender::~SkinModelRender()
		{
			if (m_shadowFlag == true) {
				m_shadow->DeleteShadowModel(&m_shadowModel);
			}
			m_renderingEngine->DeleteModel(&m_model);
		}

		bool SkinModelRender::Start()
		{
			return true;
		}


		void SkinModelRender::Init(const char* modelFilePath, const char* skeletonPath, AnimationClip* animationClip, int animationNum, EnModelUpAxis enAxsis)
		{
			//既に初期化されていたら実行しない
			if (m_isInitd == true) {
				return;
			}

			//モデルのファイルパスを設定
			m_modelFilePath = modelFilePath;
			m_modelInitData.m_tkmFilePath = modelFilePath;

			//シェーダーファイルパスを設定
			m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

			//モデルの上方向を設定
			m_modelInitData.m_modelUpAxis = enAxsis;

			//スケルトンのファイルパスが指定されていたらスケルトンを作成
			if (skeletonPath != nullptr) {

				//スケルトンのファイルパスを記憶しておく
				m_skeletonFilePath = skeletonPath;

				m_skeleton.Init(skeletonPath);
				//スケルトンをモデルに設定
				m_modelInitData.m_skeleton = &m_skeleton;

				//頂点シェーダーのエントリーポイントを指定
				m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

				//アニメーションクリップとアニメーションの数が設定されていたらアニメーションを作成
				if (animationClip != nullptr && animationNum != 0) {

					m_animationClip = animationClip;

					m_animation.Init(m_skeleton, m_animationClip, animationNum);

					m_animFlag = true;
				}
			}
			else {
				//アニメーション無しの頂点シェーダーのエントリーポイントを設定
				m_modelInitData.m_vsEntryPointFunc = "VSMain";
			}

			//モデルにライトの情報を渡す
			m_modelInitData.m_expandConstantBuffer[0] = m_lig->GetLightAddress();
			m_modelInitData.m_expandConstantBufferSize[0] = sizeof(m_lig->GetLight());

			//モデルにシャドウマップの情報を渡す
			m_modelInitData.m_expandShaderResoruceView[0] = &m_shadow->GetShadowMapTexture();

			//モデルにライトカメラの情報を渡す
			m_modelInitData.m_expandConstantBuffer[1] = (void*)&m_shadow->GetLightCameraMatrix();
			m_modelInitData.m_expandConstantBufferSize[1] = sizeof(m_shadow->GetLightCameraMatrix());

			//初期化情報でモデルを初期化する
			m_model.Init(m_modelInitData);

			//初期化したモデルをレンダリングエンジンに渡す
			m_renderingEngine->SetDrawModel(&m_model);

			//初期化完了
			m_isInitd = true;
		}


		void SkinModelRender::CreateShadow()
		{
			//影を生成するため同じファイルパスを設定
			m_shadowModelInitData.m_tkmFilePath = m_modelFilePath;

			//シャドウマップ用のシェーダーファイルパスを設定
			m_shadowModelInitData.m_fxFilePath = "Assets/shader/shadowMap.fx";

			//カラーバッファのフォーマットを設定
			m_shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

			if (m_animFlag == true) {
				m_shadowModelInitData.m_skeleton = &m_skeleton;

				m_shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
			}
			else {
				//アニメーション無しの頂点シェーダーのエントリーポイントを設定
				m_modelInitData.m_vsEntryPointFunc = "VSMain";
			}

			//初期化情報で影描写用のモデルを初期化
			m_shadowModel.Init(m_shadowModelInitData);

			//影描写用のモデルをシャドウマップ作成のクラスに渡す
			m_shadow->SetShadowModel(&m_shadowModel);

			//影が作られたフラグを立てる
			m_shadowFlag = true;
		}

		void SkinModelRender::PlayAnimation(const int animNo, const float interpolateTime)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		void SkinModelRender::Update()
		{


		}

		void SkinModelRender::Execution()
		{
			//初期化されていなければ実行しない
			if (m_isInitd == false) {
				return;
			}

			m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
			m_skeleton.Update(m_model.GetWorldMatrix());
			m_animation.Progress(1.0f / 60.0f);

			if (m_shadowFlag == true) {
				m_shadowModel.UpdateWorldMatrix(m_position, m_qRot, m_scale);
			}
		}
	}
}