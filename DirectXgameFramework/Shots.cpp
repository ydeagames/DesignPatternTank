#include "Shots.h"
#include "DirectX11.h"
#include "BulletFactory.h"

void DefaultShot::Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle)
{
	auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	m_bulletFactory->GetBullets().push_back(m_bulletFactory->Create(pos, vel));
}

void NWayShot::Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
{
	for (int i = 0; i < m_n; i++)
	{
		auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle + DirectX::XMConvertToRadians(m_rad * (i - m_n / 2))));
		auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		m_bulletFactory->GetBullets().push_back(m_bulletFactory->Create(pos, vel));
	}
}

void BombShot::Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
{
	auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	m_bulletFactory->GetBullets().push_back(m_bulletFactory->CreateBomb(pos, vel));
}

void ScatteringShot::Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
{
	float rad = DirectX::XM_2PI / m_n;
	for (int i = 0; i < m_n; i++)
	{
		for (int j = 0; j < m_n; j++)
		{
			auto vel1 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
			auto vel2 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(rad * i));
			auto vel3 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(rad * j));
			auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
			m_bulletFactory->GetBullets().push_back(m_bulletFactory->CreateScattering(pos, { { 2, vel1 },{ 2, vel2 },{ 100, vel3 } }));
		}
	}
}

void AbstractShot::Initialize(BulletFactory* bulletFactory)
{
	m_bulletFactory = bulletFactory;
}
