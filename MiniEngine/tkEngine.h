#pragma once

#include "HID/GamePad.h"
#include "TResourceBank.h"
#include "tkFile/TkmFile.h"
#include "tkFile/TksFile.h"
#include "tkFile/TkaFile.h"
#include "Shader.h"
#include <MiniEngine.h>

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~TkEngine();
	/// <summary>
	/// フレームの開始時に呼ばれる処理。
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// フレームの終了時に呼ばれる処理。
	/// </summary>
	void EndFrame();
	/// <summary>
	/// ゲームエンジンの初期化。
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

	TkmFile* GetTkmFileFromBank(const char* filePath)
	{
		return m_tkmFileBank.Get(filePath);
	}

	void RegistTkmFileToBank(const char* filePath, TkmFile* tkmFile)
	{
		m_tkmFileBank.Regist(filePath, tkmFile);
	}

	Shader* GetShaderFromBank(const char* filePath, const char* entryPointFuncName)
	{
		std::string programName = filePath;
		programName += entryPointFuncName;
		return m_shaderBank.Get(programName.c_str());
	}

	void RegistShaderToBank(const char* filePath, const char* entryPointFuncName, Shader* shader)
	{
		std::string programName = filePath;
		programName += entryPointFuncName;
		m_shaderBank.Regist(programName.c_str(), shader);
	}

	LowTexture* GetLowTextureFromBank(const char* filePath)
	{
		return m_lowTextureBank.Get(filePath);
	}

	void RegistLowTextureToBank(const char* filePath, LowTexture* textureLow)
	{
		m_lowTextureBank.Regist(filePath, textureLow);
	}

	TksFile* GetTksFileFromBank(const char* filePath)
	{
		return m_tksFileBank.Get(filePath);
	}

	void RegistTksFileToBank(const char* filePath, TksFile* tksFIle)
	{
		m_tksFileBank.Regist(filePath, tksFIle);
	}

	TkaFile* GetTkaFileFromBank(const char* filePath)
	{
		return m_tkaFileBank.Get(filePath);
	}

	void RegistTkaFileToBank(const char* filePath, TkaFile* tkaFile)
	{
		m_tkaFileBank.Regist(filePath, tkaFile);
	}

private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//グラフィックエンジン。
	TResourceBank<TkmFile> m_tkmFileBank;			//tkmファイルのリソースバンク
	TResourceBank<Shader> m_shaderBank;				//シェーダーリソースバンク
	TResourceBank<LowTexture> m_lowTextureBank;		//Lowテクスチャのリソースバンク
	TResourceBank<TksFile> m_tksFileBank;			//tksファイルのリソースバンク
	TResourceBank<TkaFile> m_tkaFileBank;			//tkaファイルのリソースバンク
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//ゲームパッド。
	GameTime m_gameTime;							//ゲームタイム。
	
};

extern TkEngine* g_engine;	//TKエンジン。
extern GameTime* g_gameTime;