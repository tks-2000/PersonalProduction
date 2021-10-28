#pragma once
#include "RenderResource.h"
#include "FontRender.h"

namespace mainGame {
	namespace map {
		class MiniMap;
	}
}

namespace render {
	namespace light {
		class Lighting;
	}
	namespace shadow {
		class Shadow;
	}
	namespace postEffect{
		class PostEffect;
	}
	/// @brief レンダリングに必要な機能をまとめたクラス
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

		Texture* GetTexture() { return &m_mainRenderTarget.GetRenderTargetTexture(); }

		/// @brief 描画するモデルを追加
		/// @param model 追加するモデルのアドレス
		void SetDrawModel(Model* model);

		/// @brief 描画しているモデルを削除
		/// @param model 削除するモデルのアドレス
		void DeleteModel(Model* model);

		/// @brief 描画するスプライトを追加
		/// @param sprite 追加するスプライトのアドレス
		void SetDrawSprite(Sprite* sprite);

		/// @brief 描画しているスプライトを削除
		/// @param sprite 削除するスプライトのアドレス
		void DeleteSprite(Sprite* sprite);

		/// @brief 描画するフォントを追加
		/// @param font 追加するフォントのアドレス
		void SetDrawFont(font::FontData* fontdata);

		/// @brief 描画しているフォントを削除
		/// @param font 削除するフォントのアドレス
		void DeleteFont(font::FontData* fontdata);

		void SetLightFlag(const bool Authenticity) { m_ligFlag = Authenticity; }

		void SetMiniMapData(mainGame::map::MiniMap* miniMap) { m_miniMap = miniMap; m_mapRenderFlag = true; }

		void DeleteMiniMapData() { m_miniMap = nullptr; m_mapRenderFlag = false; }

	private:
		/// @brief ライトの更新
		void LightUpdate();
		
		/// @brief ライティング
		light::Lighting* m_lig = nullptr;
		/// @brief シャドウ
		shadow::Shadow* m_shadow = nullptr;
		/// @brief ポストエフェクト
		postEffect::PostEffect* m_postEffect = nullptr;

		/// @brief メインレンダリングターゲット
		RenderTarget m_mainRenderTarget;

		/// @brief 描画するモデルの配列
		std::vector<Model*> m_drawModels;

		/// @brief 描画するスプライトの配列
		std::vector<Sprite*> m_drawSprites;

		/// @brief 描画するフォントの配列
		std::vector<font::FontData*> m_drawFontsData;

		/// @brief フレームバッファのスプライトの初期化情報
		SpriteInitData m_frameBufferSpriteInitData;
		/// @brief フレームバッファのスプライト
		Sprite m_frameBufferSprite;

		Vector3 m_ligColor = g_vec3Zero;

		bool m_ligFlag = false;

		mainGame::map::MiniMap* m_miniMap = nullptr;

		bool m_mapRenderFlag = false;
	};
}
