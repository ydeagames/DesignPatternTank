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
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override;
};

class NWayShot : public AbstractShot
{
private:
	int m_n;
	int m_rad;

public:
	NWayShot(int n = 3, float rad = 30)
		: m_n(n)
		, m_rad(rad) {}

public:
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) override;
};

class BombShot : public AbstractShot
{
public:
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
	void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angley) override;
};
