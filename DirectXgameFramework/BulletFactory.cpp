#include "BulletFactory.h"
#include "WICTextureLoader.h"
#include "DirectX11.h"

BulletFactory::BulletFactory()
{
}

Bullet* BulletFactory::Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity)
{
	return new Bullet(m_texture.Get(), position, velocity, m_color);
}

void BulletFactory::Initialize()
{
	// Turretテクスチャをロードする
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"tank3.png", nullptr, m_texture.ReleaseAndGetAddressOf());
}

