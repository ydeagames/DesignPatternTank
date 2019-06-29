#include "Cannon.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "IShotStrategy.h"
#include "Shots.h"
#include <sstream>

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
	Shots::GetWeapons()[m_shotType]->Initialize(m_bulletFactory);
	Shots::GetWeapons()[m_shotType]->Shoot(timer, m_position, m_angle);
}

// �V���b�g�؂�ւ���
void Cannon::SwitchShot(int d)
{
	int sz = Shots::GetWeapons().size();
	m_shotType = ((m_shotType + d) % sz + sz) % sz;
}

// ����������
void Cannon::Initialize()
{
	// TurretAngle
	SetTurretAngle(1.f);
	// Turret�e�N�X�`�������[�h����
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"tank4.png", nullptr, m_texture.ReleaseAndGetAddressOf());
	m_shotType = 0;
	m_font = std::make_unique<DirectX::SpriteFont>(DirectX11::Get().GetDevice().Get(), L"logofont.spritefont");
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

	{
		std::wostringstream sb;
		int i = 0;
		for (auto& weapon : Shots::GetWeapons())
		{
			sb << (m_shotType == i ? L"->" : L"") << weapon->GetName() << std::endl;
			i++;
		}
		m_font->DrawString(&spriteBatch, sb.str().c_str(), DirectX::SimpleMath::Vector3::Zero, DirectX::Colors::White, 0, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * .5f);
	}
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

