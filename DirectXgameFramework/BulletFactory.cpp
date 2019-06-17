#include "BulletFactory.h"
#include "WICTextureLoader.h"
#include "DirectX11.h"

BulletFactory::BulletFactory(std::vector<Bullet*>* bullets)
	: m_color(DirectX::Colors::White)
	, m_bullets(bullets)
{
}

Bullet* BulletFactory::Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity)
{
	auto bullet = new Bullet(m_texture.Get(), position, velocity, m_color);
	bullet->Initialize();
	return bullet;
}

Bullet* BulletFactory::CreateBomb(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity)
{
	auto bullet = new Bomb(m_texture.Get(), position, velocity, m_color);
	bullet->Initialize();
	return bullet;
}

Bullet * BulletFactory::CreateScattering(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity, const DirectX::SimpleMath::Vector2 & after_velocity)
{
	auto bullet = new Scattering(m_texture.Get(), position, velocity, after_velocity, m_color);
	bullet->Initialize();
	return bullet;
}

void BulletFactory::Initialize()
{
	// Turretテクスチャをロードする
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"bullet.png", nullptr, m_texture.ReleaseAndGetAddressOf());
}

std::vector<Bullet*>& BulletFactory::GetBullets()
{
	return *m_bullets;
}

