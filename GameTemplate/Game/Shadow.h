#pragma once
#include "../../MiniEngine/RenderTarget.h"

namespace Render {
	const int MAX_SHADOW_MODEL_NUM = 100;

	class Shadow : public IGameObject
	{
	public:
		Shadow();
		~Shadow();
		bool Start();
		void Update();
		/// @brief シャドウマップを取得
		/// @return シャドウマップのconst参照
		const RenderTarget& GetShadowMap() const { return m_shadowMap; }

		/// @brief ライトカメラを取得
		/// @return ライトカメラのconst参照
		const Camera& GetLightCamera() const { return m_lightCamera; }

		/// @brief ライトカメラの座標を設定
		/// @param pos ライトカメラに設定する座標のconst参照
		void SetLightCameraPos(const Vector3& pos) { m_ligCameraPos = pos; }

		/// @brief ライトカメラの注視点を設定
		/// @param target ライトカメラに設定する注視点座標のconst参照
		void SetLightCameraTarget(const Vector3& target) { m_ligCameraTarget = target; }

		/// @brief 影を生成するモデルを作成
		/// @param shadowModel 影を生成するモデル
		void SetShadowModel(Model* shadowModel);
	private:
		/// @brief シャドウマップ
		RenderTarget m_shadowMap;
		/// @brief カラーバッファのクリアカラー
		float m_clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		/// @brief ライトカメラ
		Camera m_lightCamera;
		/// @brief ライトカメラの座標
		Vector3 m_ligCameraPos = g_vec3One;
		/// @brief ライトカメラの注視点
		Vector3 m_ligCameraTarget = g_vec3Zero;
		/// @brief ライトカメラの上方向
		Vector3 m_ligCameraUp = { 1.0f,0.0f,0.0f };
		/// @brief ライトカメラの画角
		float m_ligCameraViewAngle = 20.0f;
		/// @brief シャドウマップに書き込むモデルの合計数
		int m_shadowModelSum = 0;
		/// @brief シャドウマップ生成のためのモデル
		std::vector<Model*> m_shadowModel = { nullptr };
		/// @brief シャドウモデルの番号
		int m_shadowModelNum[MAX_SHADOW_MODEL_NUM] = { MAX_SHADOW_MODEL_NUM };

		/// @brief ライトカメラの更新
		void LightCameraUpdate();
	};
}

