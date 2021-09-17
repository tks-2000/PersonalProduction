#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "Lighting.h"
#include "SkinModelRender.h"
#include "Game.h"

/// @brief 他の場所でも必要になるレンダリングエンジンの定数
namespace Render {

	static const char* LIGHTING_NAME = "Lighting";
	
	/// @brief 無色
	static const Vector3 COLORLESS = { 0.0f,0.0f,0.0f };

}