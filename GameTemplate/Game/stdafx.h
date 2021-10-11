#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define TK_ENABLE_HDR		//定義でHDRレンダリングを有効にする。

#include "MiniEngine.h"
#include "ExEngine.h"
#include "RenderResource.h"
#include "RenderingEngine.h"
#include "Lighting.h"
#include "Shadow.h"
#include "PostEffect.h"
#include "GaussianBlur.h"
#include "Bloom.h"
#include "SkinModelRender.h"
#include "SpriteRender.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "PlayerAnimation.h"

namespace {
	const int PRIORITY_VERYLOW = 0;
}



namespace mainGame {
	static const char* GAME_NAME = "Game";
	static const char* GAME_CAMERA_NAME = "GameCamera";
	namespace player {
		static const char* PLAYER_NAME = "Player";
	}
}