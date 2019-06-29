#include "Shots.h"
#include "DirectX11.h"
#include "BulletFactory.h"

class AbstractShot : public IWeapon
{
protected:
	BulletFactory* m_bulletFactory;

public:
	void Initialize(BulletFactory* bulletFactory) override
	{
		m_bulletFactory = bulletFactory;
	}
};

class DefaultShot : public AbstractShot
{
public:
	std::wstring GetName() const override { return L"’Êí’e"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override
	{
		auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		m_bulletFactory->Instantiate<Bullet>(pos, vel, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
	}
};

class NWayShot : public AbstractShot
{
private:
	int m_n;
	float m_rad;

public:
	NWayShot(int n = 3, float rad = 30)
		: m_n(n)
		, m_rad(rad) {}

public:
	std::wstring GetName() const override { return std::to_wstring(m_n) + L"Way’e"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override
	{
		for (int i = 0; i < m_n; i++)
		{
			auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle + DirectX::XMConvertToRadians(m_rad * (i - (m_n - 1) / 2.f))));
			auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
			m_bulletFactory->Instantiate<Bullet>(pos, vel, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
		}
	}
};

class BombShot : public AbstractShot
{
public:
	std::wstring GetName() const override { return L"ƒ{ƒ€’e"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override
	{
		auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
		m_bulletFactory->Instantiate<Bomb>(pos, vel, DirectX::SimpleMath::Vector4(DirectX::Colors::White));
	}
};

class ScatteringShot : public AbstractShot
{
private:
	int m_n;

public:
	ScatteringShot(int n = 32)
		: m_n(n) {}

public:
	std::wstring GetName() const override { return L"ŽU’e" + std::to_wstring(m_n); }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override
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
};

class Scattering2Shot : public AbstractShot
{
private:
	int m_n;

public:
	Scattering2Shot(int n = 32)
		: m_n(n) {}

public:
	std::wstring GetName() const override { return L"2’iŠKŽU’e" + std::to_wstring(m_n); }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override
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
};

class Toho1Shot : public AbstractShot
{
private:
	int m_n;
	int m_cycle;

public:
	Toho1Shot(int n = 32, int cycle = 16)
		: m_n(n)
		, m_cycle(cycle) {}

public:
	std::wstring GetName() const override { return L"ToHo1*" + std::to_wstring(m_n); }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override
	{
		float rad = DirectX::XM_2PI / m_cycle;
		float duration = 3.f;
		for (int i = 0; i < m_n; i++)
		{
			auto vel1 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
			auto vel2 = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 1, DirectX::SimpleMath::Matrix::CreateRotationZ(rad * i));
			auto pos = position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-angle));
			float t = duration * float(i) / float(m_n);
			m_bulletFactory->Instantiate<Scattering>(
				pos,
				std::deque<Scattering::Task>{ { 2, vel1 }, { t, DirectX::SimpleMath::Vector2::Zero }, { 2, vel2 } },
				DirectX::SimpleMath::Vector4(DirectX::Colors::White));
		}
	}
};

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
		weapons.emplace_back(std::make_unique<Toho1Shot>(256, 64));

		flag = false;
	}
	return weapons;
}
