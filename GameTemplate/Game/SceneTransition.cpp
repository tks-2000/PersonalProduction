#include "stdafx.h"
#include "SceneTransition.h"

namespace mainGame{
	SceneTransition::SceneTransition()
	{

	}

	SceneTransition::~SceneTransition()
	{

	}

	void SceneTransition::Init()
	{
		//使用する情報を取得
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		//変数を初期化
		m_opacity = 0.0f;
		//初期化完了
		m_isInitd = true;
	}

	void SceneTransition::Execution()
	{
		//未初期化なら実行しない
		if (m_isInitd == false) {
			return;
		}

		//フェードイン中
		if (m_feadIn == true) {
			//不透明度を上げる
			m_opacity += g_gameTime->GetFrameDeltaTime() * m_feadRate;
			//不透明度が最大に達したら…
			if (m_opacity >= 1.0f) {
				//フェードインを終了する
				m_opacity = 1.0f;
				m_feadIn = false;
			}
		}
		//フェードアウト中
		if (m_feadOut == true) {
			//不透明度を下げる
			m_opacity -= g_gameTime->GetFrameDeltaTime() * m_feadRate;
			//不透明度が最小に達したら…
			if (m_opacity <= 0.0f) {
				//フェードアウトを終了する
				m_opacity = 0.0f;
				m_feadOut = false;
			}
		}

		//シーンのカラーに不透明度を設定する
		m_sceneColor.x = m_opacity;
		m_sceneColor.y = m_opacity;
		m_sceneColor.z = m_opacity;

		//不透明度をシーンのスプライトに設定
		m_renderingEngine->SetFinalSpriteColor(m_sceneColor);
	}
}