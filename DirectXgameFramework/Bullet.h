#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"
#include "StepTimer.h"

class Bullet
{
	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 速度
	DirectX::SimpleMath::Vector2 m_velocity;
	// テクスチャポインタ
	ID3D11ShaderResourceView* m_texture;
	// 色
	DirectX::SimpleMath::Vector4 m_color;

public:
	Bullet(ID3D11ShaderResourceView* m_texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& velocity, DirectX::SimpleMath::Vector4& color);

	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DX::StepTimer& timer);
	// 描画する
	void Render(DirectX::SpriteBatch& spriteBatch);
	// 後処理をおこなう
	void Finalize();

};

