#ifndef TANK_FACTORY
#define TANK_FACTORY

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>

#include "Tank.h"
#include "Turret.h"
#include "Cannon.h"
#include "Body.h"

// Tankファクトリクラス
class TankFactory 
{
public:
	// コンストラクタ
	TankFactory(const DirectX::SimpleMath::Vector2& position, const float& angle, const DirectX::SimpleMath::Vector4& color);
	// タンクのパーツを生成する
	Tank* Create(Tank::PARTS_ID id);

private:
	// 位置 
	DirectX::SimpleMath::Vector2 m_position;
	// 速度 
	DirectX::SimpleMath::Vector2 m_velocity;
	// 角度 
	float m_angle;
	// Turret角度 
	float m_turretAngle;
	// 色 Color
	DirectX::SimpleMath::Vector4 m_color;
};

#endif	// TANK_FACTORY
