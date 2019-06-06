#ifndef TANK_FACTORY
#define TANK_FACTORY

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>

#include "Tank.h"
#include "Turret.h"
#include "Cannon.h"
#include "Body.h"

// Tank�t�@�N�g���N���X
class TankFactory 
{
public:
	// �R���X�g���N�^
	TankFactory(const DirectX::SimpleMath::Vector2& position, const float& angle, const DirectX::SimpleMath::Vector4& color);
	// �^���N�̃p�[�c�𐶐�����
	Tank* Create(Tank::PARTS_ID id);

private:
	// �ʒu 
	DirectX::SimpleMath::Vector2 m_position;
	// ���x 
	DirectX::SimpleMath::Vector2 m_velocity;
	// �p�x 
	float m_angle;
	// Turret�p�x 
	float m_turretAngle;
	// �F Color
	DirectX::SimpleMath::Vector4 m_color;
};

#endif	// TANK_FACTORY
