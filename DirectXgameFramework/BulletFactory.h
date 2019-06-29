#ifndef BULLET_FACTORY
#define BULLET_FACTORY

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <wrl/client.h>
#include <vector>

#include "Bullet.h"

// Tankファクトリクラス
class BulletFactory
{
public:
	// コンストラクタ
	BulletFactory(std::vector<std::unique_ptr<Bullet>>* bullets);

	// タンクのパーツを生成する
	template<typename T, typename... Args>
	std::unique_ptr<Bullet> Create(const DirectX::SimpleMath::Vector2& position, Args&&... args)
	{
		auto bullet = std::make_unique<T>(m_texture.Get(), position, std::forward<Args>(args)...);
		bullet->Initialize();
		return bullet;
	}

	template<typename T, typename... Args>
	void Instantiate(const DirectX::SimpleMath::Vector2& position, Args&&... args)
	{
		GetBullets().push_back(Create<T>(position, std::forward<Args>(args)...));
	}

	// 初期化する
	void Initialize();
	std::vector<std::unique_ptr<Bullet>>& GetBullets();

private:
	std::vector<std::unique_ptr<Bullet>>* m_bullets;
	//// 位置 
	//DirectX::SimpleMath::Vector2 m_position;
	//// 速度 
	//DirectX::SimpleMath::Vector2 m_velocity;
	// 色 Color
	//DirectX::SimpleMath::Vector4 m_color;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif	// BULLET_FACTORY
