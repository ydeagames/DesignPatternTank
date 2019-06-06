#ifndef MYGAME_DEFINED
#define MYGAME_DEFINED

#include "Game.h"
#include "Player.h"

class MyGame : public Game 
{
public:
	// コンストラクタ
	MyGame(int width, int height);
	// 初期する
	void Initialize() override;
	// 更新する
	void Update(const DX::StepTimer& timer) override;
	// 描画する
	void Render(const DX::StepTimer& timer) override;
	// 後始末をする
	void Finalize() override;

private:
	// DirectX11グラフィックス 
	DirectX11& m_directX = DirectX11::Get();

	// プレイヤ
	std::unique_ptr<Player> m_player;
};

#endif	// MYGAME_DEFINED

