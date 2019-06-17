#include "Cannon.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "IShotStrategy.h"
#include "Shots.h"

// コンストラクタ
Cannon::Cannon()
{
}

// パーツを追加する
void Cannon::AddParts(Tank* tank)
{
}

// パーツを取得する
Tank* Cannon::GetParts()
{
	return nullptr;
}

// ショット打つ
void Cannon::Shot(const DX::StepTimer& timer)
{
	m_shotState->Initialize(m_bulletFactory);
	m_shotState->Shoot(timer, m_position, m_angle);
}

// ショット切り替える
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

// 初期化する
void Cannon::Initialize()
{
	// TurretAngle
	SetTurretAngle(1.f);
	// Turretテクスチャをロードする
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
		L"tank4.png", nullptr, m_texture.ReleaseAndGetAddressOf());
	m_shotType = ShotType::NWAY;
	m_shotState = std::make_unique<NWayShot>(3, 30);
}

// 更新する
void Cannon::Update(const DX::StepTimer& timer)
{
}

// 描画する
void Cannon::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SimpleMath::Vector2& position, float angle, DirectX::SimpleMath::Vector4& color)
{
	m_position = position;
	m_angle = angle;
	spriteBatch.Draw(m_texture.Get(), position, nullptr, color, -angle + DirectX::XMConvertToRadians(90.0f), DirectX::SimpleMath::Vector2(64.0f, 64.0f), DirectX::SimpleMath::Vector3(1.f, GetTurretAngle(), 1.f));
}

// 後処理をおこなう
void Cannon::Finalize()
{
	// テクスチャをリセットする
	m_texture.Reset();
}

void Cannon::SetBulletFactory(BulletFactory* bulletFactory)
{
	m_bulletFactory = bulletFactory;
}

