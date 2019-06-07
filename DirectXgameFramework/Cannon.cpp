#include "Cannon.h"
#include "Bullet.h"
#include "BulletFactory.h"

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
void Cannon::Shot(std::vector<Bullet*>& bullets, BulletFactory * bulletFactory)
{
	auto vel = DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 4, DirectX::SimpleMath::Matrix::CreateRotationZ(-m_angle));
	auto pos = m_position + DirectX::SimpleMath::Vector2::Transform(DirectX::SimpleMath::Vector2::UnitX * 70, DirectX::SimpleMath::Matrix::CreateRotationZ(-m_angle));
	bullets.push_back(bulletFactory->Create(pos, vel));
}

// ����������
void Cannon::Initialize()
{
	// TurretAngle
	SetTurretAngle(1.f);
	// Turret�e�N�X�`�������[�h����
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"tank4.png", nullptr, m_texture.ReleaseAndGetAddressOf());
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

