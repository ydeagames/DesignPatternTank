#ifndef TANK_DEFINED
#define TANK_DEFINED

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "StepTimer.h"
#include "dx.h"
#include <vector>
#include "ITank.h"

class Bullet;
class BulletFactory;

class Tank : public ITank
{
public:
	// �p�[�cID
	enum PARTS_ID { TURRET, BODY, CANNON };
	// �X�s�[�h
	static DirectX::SimpleMath::Vector2 SPEED;

	// �ʒu���擾����
	DirectX::SimpleMath::Vector2 GetPosition() const
	{
		return m_position;
	}
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector2& position) 
	{
		m_position = position;
	}
	// ���x���擾����
	DirectX::SimpleMath::Vector2 GetVelocity() const
	{
		return m_velocity;
	}
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector2& velocity)
	{
		m_velocity = velocity;
	}
	// �ԑ̊p���擾����
	float GetBodyAngle() const
	{
		return m_bodyAngle;
	}
	// �ԑ̊p��ݒ肷��
	void SetBodyAngle(const float& angle) 
	{
		m_bodyAngle = angle;
	}

	// �C���p���擾����
	float GetTurretAngle() const
	{
		return m_turretAngle;
	}
	// �C���p��ݒ肷��
	void SetTurretAngle(const float& headAngle) 
	{
		m_turretAngle = headAngle;
	}
	
	// �F���擾����
	DirectX::SimpleMath::Vector4 GetColor() const
	{
		return m_color;
	}
	// �F��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Vector4& color) 
	{
		m_color = color;
	}

	// �R���X�g���N�^
	Tank() 
		: 
		m_position(0.0f, 0.0f), 
		m_velocity(0.0f, 0.0f),
		m_bodyAngle(0.0f), 
		m_turretAngle(0.0f), 
		m_color(0.0f, 0.0f, 0.0f, 0.0f) 
	{
	}

	// �p�[�c��ǉ�����
	virtual void AddParts(Tank* tank)
	{
	}
	// �p�[�c���擾����
	virtual Tank* GetParts()
	{
		return nullptr;
	}
	// ����������
	virtual void Initialize() 
	{
	};
	// �V���b�g�ł�
	virtual void Shot(std::vector<Bullet*>& bullets, BulletFactory* bulletFactory)
	{
	}
	// �X�V����
	virtual void Update(const DX::StepTimer& timer)
	{
	};
	// �`�悷��
	virtual void Render(DirectX::SpriteBatch& spriteBatch,
		DirectX::SimpleMath::Vector2& position,
		float angle,
		DirectX::SimpleMath::Vector4& color) 
	{
	}
	// �㏈���������Ȃ�
	virtual void Finalize() 
	{
	};
	// �f�X�g���N�^
	virtual ~Tank() 
	{
	};

private:
	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �p�x
	float m_bodyAngle;
	// �C���p�x
	float m_turretAngle;
	// �F
	DirectX::SimpleMath::Vector4 m_color;
};

#endif // TANK_DEFINED
