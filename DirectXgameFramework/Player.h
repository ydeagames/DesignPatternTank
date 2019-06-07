#pragma once
#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <Keyboard.h>

#include "StepTimer.h"
#include "dx.h"

#include "DirectX11.h"
#include "TankFactory.h"
#include "ITank.h"
#include "Tank.h"
#include "Turret.h"
#include "Body.h"
#include "Bullet.h"
#include "BulletFactory.h"

// Playerクラス
class Player 
{
public:
	// コンストラクタ
	Player();
	// 初期化する
	void Initialize(const DirectX::SimpleMath::Vector2& position, const float& angle,const DirectX::SimpleMath::Vector4& color);
	// 更新する
	bool Update(const DX::StepTimer& timer);
	// 描画する
	void Render(DirectX::SpriteBatch& spriteBatch);
	// 後処理をおこなう
	void Finalize();

private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// キーボード 
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// キーボードステートトラッカ
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	// タンク
	Tank* m_tank;
	// 弾
	std::vector<Bullet*> m_bullets;
	// 弾工場
	std::unique_ptr<BulletFactory> m_bulletFactory;
};

#endif // PLAYER_DEFINED
