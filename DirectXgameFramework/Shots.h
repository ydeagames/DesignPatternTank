#pragma once
#include "IShotStrategy.h"
#include "StepTimer.h"

class Shots
{
private:
	static std::vector<std::unique_ptr<IWeapon>> weapons;

public:
	static std::vector<std::unique_ptr<IWeapon>>& GetWeapons();
};