#include "MyGame.h"

// コンストラクタ
MyGame::MyGame(int width, int height) : Game(width, height)
{
}

// MyGameオブジェクトを初期する
void MyGame::Initialize() 
{
	// 基本クラスのInitializeを呼び出す 
	Game::Initialize();

	// Playerオブジェクトを生成する 
	m_player = std::make_unique<Player>();
	// Playerオブジェクトを初期化する 
	m_player->Initialize(DirectX::SimpleMath::Vector2(200.0f, 300.0f), DirectX::XMConvertToRadians(0.0f), DirectX::SimpleMath::Vector4(DirectX::Colors::BlanchedAlmond));
}

// ゲームを更新する 
void MyGame::Update(const DX::StepTimer& timer) 
{
	float elapsedTime = float(timer.GetElapsedSeconds());
	// TODO: 更新処理を追加する

	// プレイヤを更新する
	m_player->Update(timer);
}

// シーンを描画する Draws scene
void MyGame::Render(const DX::StepTimer& timer) 
{
	// 最初の更新の前は何も描画しないようにする 
	if (timer.GetFrameCount() == 0) 
		return;

	// TODO: レンダリングコードを追加する 
	// バッファをクリアする
	Clear();
	// 描画を始める 
	GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, GetCommonStates()->NonPremultiplied());
	// 描画する 
	m_player->Render(*GetSpriteBatch());

	// 描画を終える 
	GetSpriteBatch()->End();
	// バックバッファをスクリーンに送る 
	Present();
}

// 終了処理をおこなう 
void MyGame::Finalize() 
{

	// Playerオブジェクトの後処理をおこなう
	m_player->Finalize();
	// Playerオブジェクトをリセットする
	m_player.reset();

	// 基本クラスのFinalizeを呼び出す
	Game::Finalize();
}
