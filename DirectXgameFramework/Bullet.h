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
	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 速度
	DirectX::SimpleMath::Vector2 m_velocity;
	// テクスチャポインタ
	ID3D11ShaderResourceView* m_texture;
	// 色
	DirectX::SimpleMath::Vector4 m_color;

public:
	Bullet(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& velocity, const DirectX::SimpleMath::Vector4& color);
	virtual ~Bullet() = default;

	DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	virtual bool IsUsed() { return true; }

	// 初期化する
	virtual void Initialize();
	// 更新する
	virtual void Update(const DX::StepTimer& timer);
	// 描画する
	virtual void Render(DirectX::SpriteBatch& spriteBatch);
	// 後処理をおこなう
	virtual void Finalize();

};

class Bomb : public Bullet
{
	float m_life;

public:
	Bomb(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& velocity, const DirectX::SimpleMath::Vector4& color);
	virtual ~Bomb() = default;

	bool IsUsed() override { return m_life > 0; }

	// 更新する
	virtual void Update(const DX::StepTimer& timer);
	// 描画する
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

	// 更新する
	virtual void Update(const DX::StepTimer& timer);
};