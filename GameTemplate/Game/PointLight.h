#pragma once

namespace render {
	namespace light {
		/// @brief ポイントライト構造体
		struct StPointLight
		{
			Vector3 position = Vector3::Zero;	//位置
			float pad0 = 0.0f;					//パディング
			Vector3 color = Vector3::Zero;		//カラー
			float range = 0.0f;					//影響範囲
		};

		/// @brief ポイントライトの機能をまとめたクラス
		class PointLight
		{
		public:
			PointLight();
			~PointLight();
			/// @brief 初期化
			void Init();
			/// @brief 実行
			void Execution();
			/// @brief 座標を設定
			/// @param pos 設定する座標
			void SetPosition(const Vector3 pos) { m_pointLight.position = pos; }
			/// @brief カラーを設定
			/// @param color 設定するカラー
			void SetColor(const Vector3& color) { m_pointLight.color = color; }
			/// @brief 影響範囲を設定
			/// @param range 設定する影響範囲
			void SetRange(const float range) { m_pointLight.range = range; }
			/// @brief ライトを消す
			void LightOFF();
			/// @brief ポイントライトを入手
			/// @return ポイントライト構造体のconst参照
			const StPointLight& GetPointLight() const { return m_pointLight; }
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief ポイントライト
			StPointLight m_pointLight;
		};
	}
}
