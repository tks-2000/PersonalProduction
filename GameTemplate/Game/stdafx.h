#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define TK_ENABLE_HDR		//��`��HDR�����_�����O��L���ɂ���B

#include "MiniEngine.h"
#include "ExEngine.h"
#include "RenderingEngine.h"
#include "Lighting.h"
#include "Shadow.h"
#include "PostEffect.h"
#include "GaussianBlur.h"
#include "Bloom.h"
#include "SkinModelRender.h"
#include "Game.h"

/// @brief ���̏ꏊ�ł��K�v�ɂȂ郌���_�����O�G���W���̒萔
namespace Render {

	static const char* RENDERING_ENGINE_NAME = "RenderingEngine";
	static const char* LIGHTING_NAME = "Lighting";
	static const char* SHADOW_NAME = "Shadow";
	static const char* POST_EFFECT_NAME = "PostEffect";
	static const char* GAUSSIAN_BLUR_NAME = "GaussianBlur";
	static const char* BLOOM_NAME = "Bloom";
	
	/// @brief ���F
	static const Vector3 COLORLESS = { 0.0f,0.0f,0.0f };

}