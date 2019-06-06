#ifndef BULLET_FACTORY
#define BULLET_FACTORY

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <wrl/client.h>

#include "Bullet.h"

// Tankファクトリクラス
class BulletFactory
{
public:
	// コンストラクタ
	BulletFactory();
	// タンクのパーツを生成する
	Bullet* Create(const DirectX::SimpleMath::Vector2 & position, const DirectX::SimpleMath::Vector2 & velocity);
	// 初期化する
	void Initialize();

private:
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
