#include "Shots.h"
#include "DirectX11.h"
#include "BulletFactory.h"

void DefaultShot::Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle)
{
	auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	m_bulletFactory->Instantiate<Bullet>(pos, vel, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
}

void NWayShot::Shoot(const DX::StepTimer & timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
{
	for (int i = 0; i < m_n; i++)
	{
		auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle + DirectX::XMConvertToRadians(m_rad * (i - (m_n - 1) / 2.f))));
		auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		m_bulletFactory->Instantiate<Bullet>(pos, vel, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
	}
}

void BombShot::Shoot(const DX::StepTimer & timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
{
	auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
	m_bulletFactory->Instantiate<Bomb>(pos, vel, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
}

void ScatteringShot::Shoot(const DX::StepTimer & timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
{
	float rad = DirectX::XM_2PI / m_n;
	for (int i = 0; i < m_n; i++)
	{
		auto vel1 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		auto vel2 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(rad * i));
		auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		m_bulletFactory->Instantiate<Scattering>(pos, std::deque<Scattering::Task>{ { 2, vel1 }, { 2, vel2 } }, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
	}
}

void AbstractShot::Initialize(BulletFactory * bulletFactory)
{
	m_bulletFactory = bulletFactory;
}

void Scattering2Shot::Shoot(const DX::StepTimer & timer, const DirectX::SimpleMath::Vector2 & position, float& angle)
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
			m_bulletFactory->Instantiate<Scattering>(pos, std::deque<Scattering::Task>{ { 2, vel1 }, { 2, vel2 }, { 100, vel3 } }, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
		}
	}
}

std::vector<std::unique_ptr<IWeapon>> Shots::weapons;

std::vector<std::unique_ptr<IWeapon>>& Shots::GetWeapons()
{
	static bool flag = true;
	if (flag)
	{
		weapons.emplace_back(std::make_unique<DefaultShot>());
		weapons.emplace_back(std::make_unique<NWayShot>(3, 30.f));
		weapons.emplace_back(std::make_unique<NWayShot>(5, 30.f));
		weapons.emplace_back(std::make_unique<NWayShot>(24, 5.f));
		weapons.emplace_back(std::make_unique<NWayShot>(6, 30.f));
		weapons.emplace_back(std::make_unique<BombShot>());
		weapons.emplace_back(std::make_unique<ScatteringShot>(16));
		weapons.emplace_back(std::make_unique<Scattering2Shot>(4));
		weapons.emplace_back(std::make_unique<Scattering2Shot>(8));
		weapons.emplace_back(std::make_unique<Scattering2Shot>(16));

		flag = false;
	}
	return weapons;
}
