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
#include "FontRender.h"
#include "SoundSource.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "PlayerAnimation.h"
#include "DefensiveTarget.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "Stage.h"
#include "Timer.h"
#include "MiniMap.h"

namespace {
	const int PRIORITY_VERYLOW = 0;
}



namespace mainGame {

	static const int PLAYER1_CONTROLLER_NUM = 0;

	static const char* GAME_NAME = "Game";
	static const char* GAME_CAMERA_NAME = "GameCamera";

	namespace player {
		static const char* PLAYER_NAME = "Player";
	}
	namespace defensiveTarget {
		static const char* DEFENSIVE_TARGET_NAME = "DefensiveTarget";
	}
	namespace enemy {

		static const char* ENEMY_GENERATOR_NAME = "EnemyGenerator";

		static const char* ENEMY_NAME = "Enemy";

		static const char* ENEMY_NAMES[MAX_ENEMY_NUM] = { 
			"Enemy1",
			"Enemy2",
			"Enemy3",
			"Enemy4",
			"Enemy5",
			"Enemy6",
			"Enemy7",
			"Enemy8",
			"Enemy9",
			"Enemy10"
		};
	}
	namespace stage {
		static const char* STAGE_NAME = "Stage";
	}

	namespace timer {
		static const char* TIMER_NAME = "Timer";
	}

	namespace map {
		static const char* MINI_MAP_NAME = "MIniMap";
	}
}