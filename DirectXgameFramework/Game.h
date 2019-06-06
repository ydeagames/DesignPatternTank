#ifndef GAME_DEFINED
#define GAME_DEFINED

#include <windows.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Keyboard.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <string>

#include "StepTimer.h"
#include "dx.h"
#include "Window.h"
#include "DirectX11.h"

#include "Player.h"

class Window;

class Game 
{
public:
	// スプライトバッチを取得する
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spriteBatch.get();
	}
	// コモンステートを取得する
	DirectX::CommonStates* GetCommonStates() 
	{
		return m_commonStates.get();
	}
	// 基本ゲームループを実行する 
	MSG Run();
	// コンストラクタ
    Game(int width, int height);
    // 初期する 
    virtual void Initialize();
	// 更新する 
	virtual void Update(const DX::StepTimer& timer);
	// バッファをクリアする 
	void Clear();
	// シーンを描画する
	virtual void Render(const DX::StepTimer& timer);
	// バックバッファをスクリーンに送る
	void Present();
	// 終了処理をおこなう 
	virtual void Finalize();

    // メッセージ 
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ 
    void GetDefaultSize(int& width, int& height) const;
	// FPSを描画する 
	void DrawFPS();

private:
	// インスタンスハンドル
	HINSTANCE m_hInstance;
	// 実行時のウィンドウの大きさ
	int m_nCmdShow;
    // デバイスリソース
    HWND m_hWnd;
	// 出力幅 
    int m_width;
	// 出力高 
    int m_height;
    // ループタイマーを描画する 
    DX::StepTimer m_timer;
	// ウィンドウ
	std::unique_ptr<Window> m_window;

	// 機能レベル 
    D3D_FEATURE_LEVEL m_featureLevel;
	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// スプライトバッチ 
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// フォント Font
	std::unique_ptr<DirectX::SpriteFont> m_font;
	// DirectX11 グラフィックス 
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// GAME_DEFINED
