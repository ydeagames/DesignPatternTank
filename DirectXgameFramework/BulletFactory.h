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
	BulletFactory(std::vector<Bullet*>* bullets);
	// タンクのパーツを生成する
	Bullet* Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity);
	Bullet* CreateBomb(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity);
	Bullet* CreateScattering(const DirectX::SimpleMath::Vector2 & position, const std::deque<Scattering::Task>& tasks);
	// 初期化する
	void Initialize();
	std::vector<Bullet*>& GetBullets();

private:
	std::vector<Bullet*>* m_bullets;
	//// 位置 
	//DirectX::SimpleMath::Vector2 m_position;
	//// 速度 
	//DirectX::SimpleMath::Vector2 m_velocity;
	// 色 Color
	DirectX::SimpleMath::Vector4 m_color;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif	// BULLET_FACTORY
