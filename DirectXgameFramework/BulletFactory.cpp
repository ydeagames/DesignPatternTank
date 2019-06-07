#include "BulletFactory.h"
#include "WICTextureLoader.h"
#include "DirectX11.h"

BulletFactory::BulletFactory()
	: m_color(DirectX::Colors::White)
{
}

Bullet* BulletFactory::Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity)
{
	auto bullet = new Bullet(m_texture.Get(), position, velocity, m_color);
	bullet->Initialize();
	return bullet;
}

void BulletFactory::Initialize()
{
	// Turretテクスチャをロードする
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"tank3.png", nullptr, m_texture.ReleaseAndGetAddressOf());
}

