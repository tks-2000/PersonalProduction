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
#include "../../ExEngine/effect/Effect.h"
#include "EffectRender.h"
#include "SoundSource.h"
#include "SoundPlayer.h"
#include "NaviMesh.h"
#include "Path.h"
#include "PathFinding.h"
#include "Game.h"
#include "SceneTransition.h"
#include "Title.h"
#include "GameScene.h"
#include "GameCamera.h"
#include "Player.h"
#include "PlayerAnimation.h"
#include "DefensiveTarget.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "Stage.h"
#include "Timer.h"
#include "MiniMap.h"
#include "ItemGenerator.h"
#include "ItemSlot.h"
#include "Item.h"
#include "Bomb.h"
#include "RepairTools.h"
#include "NutritionDrink.h"
#include "GameUI.h"


namespace {
	const int PRIORITY_VERYLOW = 0;
}

namespace sound {
	static const char* SOUND_PLAYER_NAME = "SoundPlayer";
}

namespace mainGame {

	static const int PLAYER1_CONTROLLER_NUM = 0;

	static const char* GAME_NAME = "Game";
	static const char* GAME_SCENE_NAME = "GameScene";
	static const char* GAME_CAMERA_NAME = "GameCamera";
	static const char* SCENE_TRANSITION_NAME = "SceneTransition";

	namespace title{
		static const char* TITLE_NAME = "Title";
	}
	namespace player {
		static const char* PLAYER_NAME = "Player";
	}
	namespace defensiveTarget {
		static const char* DEFENSIVE_TARGET_NAME = "DefensiveTarget";
	}
	namespace enemy {

		static const char* ENEMY_GENERATOR_NAME = "EnemyGenerator";

		static const char* ENEMY_NAME = "Enemy";

		
	}
	namespace stage {
		static const char* STAGE_NAME = "Stage";
	}

	namespace timer {
		static const char* TIMER_NAME = "Timer";
	}

	

	namespace item {
		static const char* ITEM_GENERATOR_NAME = "ItemGenerator";
	}

	namespace ui {
		static const char* GAME_UI_NAME = "GameUI";
		static const int MINI_MAP_RENDER_GROUP = render::model::enExpandModelGroup1;
		static const char* MINI_MAP_NAME = "MIniMap";
	}

	
}