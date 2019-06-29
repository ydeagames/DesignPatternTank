#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include "SpriteBatch.h"
#include "StepTimer.h"
#include <deque>

class Bullet
{
public:
	static const DirectX::SimpleMath::Vector2 SIZE;

protected:
	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �e�N�X�`���|�C���^
	ID3D11ShaderResourceView* m_texture;
	// �F
	DirectX::SimpleMath::Vector4 m_color;

public:
	Bullet(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& velocity, const DirectX::SimpleMath::Vector4& color);
	virtual ~Bullet() = default;

	DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	virtual bool IsUsed() { return true; }

	// ����������
	virtual void Initialize();
	// �X�V����
	virtual void Update(const DX::StepTimer& timer);
	// �`�悷��
	virtual void Render(DirectX::SpriteBatch& spriteBatch);
	// �㏈���������Ȃ�
	virtual void Finalize();

};

class Bomb : public Bullet
{
	float m_life;

public:
	Bomb(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& velocity, const DirectX::SimpleMath::Vector4& color);
	virtual ~Bomb() = default;

	bool IsUsed() override { return m_life > 0; }

	// �X�V����
	virtual void Update(const DX::StepTimer& timer);
	// �`�悷��
	virtual void Render(DirectX::SpriteBatch& spriteBatch);
};


class Scattering : public Bullet
{
public:
	struct Task
	{
		float m_life;
		DirectX::SimpleMath::Vector2 m_after_velocity;
	};

private:
	std::deque<Task> m_tasks;

public:
	Scattering(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const std::deque<Task>& tasks, const DirectX::SimpleMath::Vector4& color);
	virtual ~Scattering() = default;

	// �X�V����
	virtual void Update(const DX::StepTimer& timer);
};