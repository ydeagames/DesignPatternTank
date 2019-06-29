#pragma once
#include "IShotStrategy.h"
#include "StepTimer.h"

class AbstractShot : public IWeapon
{
protected:
	BulletFactory* m_bulletFactory;

public:
	void Initialize(BulletFactory* bulletFactory) override;
};

class DefaultShot : public AbstractShot
{
public:
	std::wstring GetName() const override { return L"í èÌíe"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override;
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
	std::wstring GetName() const override { return std::to_wstring(m_n) + L"Wayíe"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override;
};

class BombShot : public AbstractShot
{
public:
	std::wstring GetName() const override { return L"É{ÉÄíe"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override;
};

class ScatteringShot : public AbstractShot
{
private:
	int m_n;

public:
	ScatteringShot(int n = 32)
		: m_n(n) {}

public:
	std::wstring GetName() const override { return L"éUíe"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angley) override;
};

class Scattering2Shot : public AbstractShot
{
private:
	int m_n;

public:
	Scattering2Shot(int n = 32)
		: m_n(n) {}

public:
	std::wstring GetName() const override { return L"2íiäKéUíe"; }
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angley) override;
};

class Shots
{
private:
	static std::vector<std::unique_ptr<IWeapon>> weapons;

public:
	static std::vector<std::unique_ptr<IWeapon>>& GetWeapons();
};