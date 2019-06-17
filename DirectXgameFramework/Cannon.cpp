#include "Cannon.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "IShotStrategy.h"
#include "Shots.h"

// �R���X�g���N�^
Cannon::Cannon()
{
}

// �p�[�c��ǉ�����
void Cannon::AddParts(Tank* tank)
{
}

// �p�[�c���擾����
Tank* Cannon::GetParts()
{
	return nullptr;
}

// �V���b�g�ł�
void Cannon::Shot(const DX::StepTimer& timer)
{
	m_shotState->Initialize(m_bulletFactory);
	m_shotState->Shoot(timer, m_position, m_angle);
}

// �V���b�g�؂�ւ���
void Cannon::SwitchShot()
{
	switch (m_shotType)
	{
	case Cannon::ShotType::DEFAULT:
		m_shotState = std::make_unique<DefaultShot>();
		m_shotType = ShotType::NWAY;
		break;
	case Cannon::ShotType::NWAY:
		m_shotState = std::make_unique<NWayShot>(3, 30);
		m_shotType = ShotType::BOMB;
		break;
	case Cannon::ShotType::BOMB:
		m_shotState = std::make_unique<BombShot>();
		m_shotType = ShotType::SCATTERING;
		break;
	case Cannon::ShotType::SCATTERING:
		m_shotState = std::make_unique<ScatteringShot>();
		m_shotType = ShotType::DEFAULT;
		break;
	default:
		break;
	}
}

// ����������
void Cannon::Initialize()
{
	// TurretAngle
	SetTurretAngle(1.f);
	// Turret�e�N�X�`�������[�h����
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"tank4.png", nullptr, m_texture.ReleaseAndGetAddressOf());
	m_shotType = ShotType::NWAY;
	m_shotState = std::make_unique<NWayShot>(3, 30);
}

// �X�V����
void Cannon::Update(const DX::StepTimer& timer)
{
}

// �`�悷��
void Cannon::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SimpleMath::Vector2& position, float angle, DirectX::SimpleMath::Vector4& color)
{
	m_position = position;
	m_angle = angle;
	spriteBatch.Draw(m_texture.Get(), position, nullptr, color, -angle + DirectX::XMConvertToRadians(90.0f), DirectX::SimpleMath::Vector2(64.0f, 64.0f), DirectX::SimpleMath::Vector3(1.f, GetTurretAngle(), 1.f));
}

// �㏈���������Ȃ�
void Cannon::Finalize()
{
	// �e�N�X�`�������Z�b�g����
	m_texture.Reset();
}

void Cannon::SetBulletFactory(BulletFactory* bulletFactory)
{
	m_bulletFactory = bulletFactory;
}

