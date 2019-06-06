#include "Bullet.h"

Bullet::Bullet(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity, DirectX::SimpleMath::Vector4& color)
	: m_texture(texture)
	, m_position(position)
	, m_velocity(velocity)
	, m_color(color)
{
}

void Bullet::Initialize()
{
}

void Bullet::Update(const DX::StepTimer & timer)
{
	m_position += m_velocity;
}

void Bullet::Render(DirectX::SpriteBatch & spriteBatch)
{
	// スプライトを描画する
	spriteBatch.Draw(m_texture, m_position, nullptr, m_color, 0, DirectX::SimpleMath::Vector2(64.0f, 64.0f));
}

void Bullet::Finalize()
{
}
