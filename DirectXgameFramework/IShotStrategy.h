#pragma once
#include <vector>
#include "DirectX11.h"
#include "StepTimer.h"
#include <string>

class Bullet;
class BulletFactory;

class IWeapon
{
public:
	virtual std::wstring GetName() const = 0;
	virtual void Initialize(BulletFactory* bulletFactory) = 0;
	virtual void Shoot(const DX::StepTimer& timer, const DirectX::SimpleMath::Vector2& position, float& angle) = 0;
	virtual ~IWeapon() = default;
};

