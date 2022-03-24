#pragma once
#include "MiniEngine.h"
#include "ExEngine.h"

/// @brief ���̏ꏊ�ł��K�v�ɂȂ郌���_�����O�G���W���̒萔
namespace render {

	static const char* RENDERING_ENGINE_NAME = "RenderingEngine";

	/// @brief ���C�g
	namespace light {
		static const char* LIGHTING_NAME = "Lighting";
	}

	/// @brief �V���h�E
	namespace shadow {
		static const char* SHADOW_NAME = "Shadow";
	}

	/// @brief �|�X�g�G�t�F�N�g
	namespace postEffect {
		static const char* POST_EFFECT_NAME = "PostEffect";
		static const char* GAUSSIAN_BLUR_NAME = "GaussianBlur";
		static const char* BLOOM_NAME = "Bloom";
	}

	/// @brief ���F
	static const Vector4 COLORLESS = { 0.0f,0.0f,0.0f,0.0f };

}