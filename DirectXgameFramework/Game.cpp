#include "Game.h"

void ExitGame();

// コンストラクタ
Game::Game(int width, int height)
	: 
	m_hWnd(0), m_width(width), m_height(height), m_featureLevel(D3D_FEATURE_LEVEL_9_1) {
	
	// スタートアップ情報
	STARTUPINFO si{};	
	// インスタンスハンドルを取得する
	m_hInstance = ::GetModuleHandle(NULL);
	
	// STARTUPINFO構造体の内容を取得する
	::GetStartupInfo(&si);
	m_nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	// Windowオブジェクトを生成する 
	m_window = std::make_unique<Window>(m_hInstance, m_nCmdShow);

}

// 基本ゲームループを実行する 
MSG Game::Run() 
{
	// メッセージ 
	MSG msg = {};

	// MyGameオブジェクトを初期化する
	Initialize();
	// ゲームループ
	while (WM_QUIT != msg.message) 
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームを更新する 
			this->m_timer.Tick([&]() { Update(m_timer); });
			// シーンを描画する 
			Render(m_timer);
		}
	}
	// MyGameオブジェクトの終了処理をおこなう
	Finalize();
	return msg;
}

// 実行に必要となるDirect3Dリソースを初期化する
void Game::Initialize() 
{
	// Windowオブジェクトを初期化する
	m_window->Initialize(m_width, m_height);
	// Windowオブジェクトの生成後にウィンドウハンドルを取得する
    m_hWnd = m_window->GetHWnd();
	// ウィンドウを表示する
	m_window->ShowWindow();

	// DirectX11 Graphicsクラスのインスタンスを取得する
	DirectX11& directX11 = DirectX11::Get();
	// DirectXの初期化のためウィンドウハンドルを設定する
	directX11.SetHWnd(m_hWnd);
	// DirectXの初期化のためウィンドウ幅を設定する
	directX11.SetWidth(m_width);
	// DirectXの初期化のためウィンドウ高を設定する
	directX11.SetHeight(m_height);

	// デバイスを生成する 
	directX11.CreateDevice();
	// リソースを生成する
	directX11.CreateResources();

    // TODO: デフォルト変数timestepモード以外のものが必要な場合タイマー設定を変更する
	// 例えば 60 FPS固定タイムステップ更新ロジックに対しては以下を呼び出す
	// Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    
    // this->timer.SetFixedTimeStep(true);
    // this->timer.SetTargetElapsedSeconds(1.0 / 60);

	// TODO: 初期化コードを追加する
	
	// SpriteBatchオブジェクトを生成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(directX11.GetContext().Get());
	// コモンステートを生成する
	m_commonStates = std::make_unique<DirectX::CommonStates>(directX11.GetDevice().Get());
	// Fontオブジェクトを生成する 
	m_font = std::make_unique<DirectX::SpriteFont>(directX11.GetDevice().Get(), L"myfile.spritefont");

}

// 終了処理をおこなう
void Game::Finalize() 
{
	// Fontオブジェクトを破棄する
	m_font.reset();
	// SpriteBatchオブジェクトを破棄する
	m_spriteBatch.reset();
	// コモンステートを破棄する
	m_commonStates.reset();
	// DirectX11 Graphicsオブジェクトを破棄する
	DirectX11::Dispose();
	// Windowオブジェクトを破棄する
	m_window.reset();
}


// ワールドを更新する 
void Game::Update(const DX::StepTimer& timer)
{
}

// シーンを描画する 
void Game::Render(const DX::StepTimer& timer) 
{
}

// FPSを描画する
void Game::DrawFPS() 
{
	// FPS文字列を生成する 
	std::wstring fpsString = L"fps = " + std::to_wstring((unsigned int)this->m_timer.GetFramesPerSecond());
	// FPSを描画する 
	m_font->DrawString(m_spriteBatch.get(), fpsString.c_str(), DirectX::SimpleMath::Vector2(0, 0), DirectX::Colors::White);
}

// バックバッファをクリアするためのヘルパー関数 
void Game::Clear()
{
    // DirectX11 Graphicsクラスのインスタンスを取得する
	DirectX11& directX11 = DirectX11::Get();
	// レンダーターゲットをクリアする 
	directX11.GetContext()->ClearRenderTargetView(directX11.GetRenderTargetView().Get(), DirectX::Colors::Black);
	// デプスステンシルビューを設定する 
	directX11.GetContext()->ClearDepthStencilView(directX11.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// レンダータッゲートを設定する 
	directX11.GetContext()->OMSetRenderTargets(1, directX11.GetRenderTargetView().GetAddressOf(), directX11.GetDepthStencilView().Get());
    // ビューポートを設定する 
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	directX11.GetContext()->RSSetViewports(1, &viewport);
}

// バックバッファをスクリーンに送る 
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
	 
	// DirectX11 Graphicsクラスのインスタンスを取得する
	DirectX11& directX = DirectX11::Get();
	HRESULT hr = directX.GetSwapChain()->Present(1, 0);

    // デバイスがリセットされた場合レンダラを再初期化する必要がある 
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
		directX.OnDeviceLost();
    }
    else 
	{
        DX::ThrowIfFailed(hr);
    }
}

// メッセージハンドラ 
void Game::OnActivated()
{
    // TODO: ゲームがアクティブなウィンドウになる
}

void Game::OnDeactivated()
{
    // TODO: ゲームがバックグラウンドウィンドウになる 
}

void Game::OnSuspending()
{
    // TODO: ゲームがパワーサスペンデッドになる 
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

    // TODO: ゲームがパワーレジュームになる 
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_width = width;
    m_height = height;
	
	DirectX11::Get().CreateResources();
    // TODO: ゲームウィンドウのサイズが再変更される 
}

// プロパティ Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: 任意のデフォルトウィンドウサイズに変更する(最小サイズは320x200) 
    width = 800;
    height = 600;
}

// Exitヘルパー関数 
void ExitGame() 
{
	PostQuitMessage(0);
}
