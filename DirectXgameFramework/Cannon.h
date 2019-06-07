#pragma once
#ifndef CANNON_DEFINED
#define CANNON_DEFINED

#include <vector>
#include "Tank.h"

// 砲塔クラス
class Cannon : public Tank
{
public:
	// コンストラクタ
	Cannon();
	// パーツを追加する
	void AddParts(Tank* tank) override;
	// パーツを取得する
	Tank* GetParts() override;
	// ショット打つ
	void Shot(std::vector<Bullet*>& bullets, BulletFactory* bulletFactory) override;
	// 初期化する 
	void Initialize() override;
	// 更新する 
	void Update(const DX::StepTimer& timer) override;
	// 描画する
	void Render(DirectX::SpriteBatch& spriteBatch,
		DirectX::SimpleMath::Vector2& position,
		float angle,
		DirectX::SimpleMath::Vector4& color) override;
	// 後処理をおこなう
	void Finalize() override;
	// デストラクタ
	~Cannon() override {}

private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 向き
	float m_angle;
};

#endif // CANNON_DEFINED
