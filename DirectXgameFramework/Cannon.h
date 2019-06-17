#pragma once
#ifndef CANNON_DEFINED
#define CANNON_DEFINED

#include <vector>
#include "Tank.h"
#include "IShotStrategy.h"
#include "StepTimer.h"

// 砲塔クラス
class Cannon : public Tank
{
	enum class ShotType
	{
		DEFAULT,
		NWAY,
		BOMB,
		SCATTERING,
	};

public:
	// コンストラクタ
	Cannon();
	// パーツを追加する
	void AddParts(Tank* tank) override;
	// パーツを取得する
	Tank* GetParts() override;
	// ショット打つ
	void Shot(const DX::StepTimer& timer) override;
	// ショットを切り替える
	void SwitchShot() override;
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
	void SetBulletFactory(BulletFactory* bulletFactory) override;

private:
	BulletFactory* m_bulletFactory;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 
	std::unique_ptr<IWeapon> m_shotState;
	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 向き
	float m_angle;
	// ショットの種類
	ShotType m_shotType;
};

#endif // CANNON_DEFINED
