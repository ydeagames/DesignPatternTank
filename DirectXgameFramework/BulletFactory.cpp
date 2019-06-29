#include "BulletFactory.h"
#include "WICTextureLoader.h"
#include "DirectX11.h"

BulletFactory::BulletFactory(std::vector<std::unique_ptr<Bullet>>* bullets)
	: m_bullets(bullets)
{
}

void BulletFactory::Initialize()
{
	// Turretテクスチャをロードする
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"bullet.png", nullptr, m_texture.ReleaseAndGetAddressOf());
}

std::vector<std::unique_ptr<Bullet>>& BulletFactory::GetBullets()
{
	return *m_bullets;
}

