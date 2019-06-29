#include "Bullet.h"

const DirectX::SimpleMath::Vector2 Bullet::SIZE(6.0f, 6.0f);

Bullet::Bullet(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity, const DirectX::SimpleMath::Vector4& color)
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
	spriteBatch.Draw(m_texture, m_position, nullptr, m_color, 0, DirectX::SimpleMath::Vector2(6.0f, 6.0f));
}

void Bullet::Finalize()
{
}

Bomb::Bomb(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity, const DirectX::SimpleMath::Vector4& color)
	: Bullet(texture, position, velocity, color)
	, m_life(2)
{
}

void Bomb::Update(const DX::StepTimer & timer)
{
	m_life -= timer.GetElapsedSeconds();
	if (m_life > 1)
		m_position += m_velocity;
}

void Bomb::Render(DirectX::SpriteBatch & spriteBatch)
{
	if (m_life > 0)
	{
		// スプライトを描画する
		spriteBatch.Draw(m_texture, m_position, nullptr, m_color, 0, DirectX::SimpleMath::Vector2(6.0f, 6.0f), m_life > 1 ? 1 : (1 - m_life) * 20 + 1);
	}
}

Scattering::Scattering(ID3D11ShaderResourceView * texture, const DirectX::SimpleMath::Vector2 & position, const std::deque<Task>& tasks, const DirectX::SimpleMath::Vector4 & color)
	: Bullet(texture, position, tasks.front().m_after_velocity, color)
	, m_tasks(tasks)
{
}

void Scattering::Update(const DX::StepTimer & timer)
{
	if (!m_tasks.empty())
	{
		auto& front = m_tasks.front();
		front.m_life -= timer.GetElapsedSeconds();
		if (front.m_life < 1)
		{
			m_tasks.pop_front();
			if (!m_tasks.empty())
				m_velocity = m_tasks.front().m_after_velocity;
		}
	}
	m_position += m_velocity;
}
