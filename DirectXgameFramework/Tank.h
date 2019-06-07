#ifndef TANK_DEFINED
#define TANK_DEFINED

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "StepTimer.h"
#include "dx.h"
#include <vector>
#include "ITank.h"

class Bullet;
class BulletFactory;

class Tank : public ITank
{
public:
	// パーツID
	enum PARTS_ID { TURRET, BODY, CANNON };
	// スピード
	static DirectX::SimpleMath::Vector2 SPEED;

	// 位置を取得する
	DirectX::SimpleMath::Vector2 GetPosition() const
	{
		return m_position;
	}
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector2& position) 
	{
		m_position = position;
	}
	// 速度を取得する
	DirectX::SimpleMath::Vector2 GetVelocity() const
	{
		return m_velocity;
	}
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector2& velocity)
	{
		m_velocity = velocity;
	}
	// 車体角を取得する
	float GetBodyAngle() const
	{
		return m_bodyAngle;
	}
	// 車体角を設定する
	void SetBodyAngle(const float& angle) 
	{
		m_bodyAngle = angle;
	}

	// 砲塔角を取得する
	float GetTurretAngle() const
	{
		return m_turretAngle;
	}
	// 砲塔角を設定する
	void SetTurretAngle(const float& headAngle) 
	{
		m_turretAngle = headAngle;
	}
	
	// 色を取得する
	DirectX::SimpleMath::Vector4 GetColor() const
	{
		return m_color;
	}
	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color) 
	{
		m_color = color;
	}

	// コンストラクタ
	Tank() 
		: 
		m_position(0.0f, 0.0f), 
		m_velocity(0.0f, 0.0f),
		m_bodyAngle(0.0f), 
		m_turretAngle(0.0f), 
		m_color(0.0f, 0.0f, 0.0f, 0.0f) 
	{
	}

	// パーツを追加する
	virtual void AddParts(Tank* tank)
	{
	}
	// パーツを取得する
	virtual Tank* GetParts()
	{
		return nullptr;
	}
	// 初期化する
	virtual void Initialize() 
	{
	};
	// ショット打つ
	virtual void Shot(std::vector<Bullet*>& bullets, BulletFactory* bulletFactory)
	{
	}
	// 更新する
	virtual void Update(const DX::StepTimer& timer)
	{
	};
	// 描画する
	virtual void Render(DirectX::SpriteBatch& spriteBatch,
		DirectX::SimpleMath::Vector2& position,
		float angle,
		DirectX::SimpleMath::Vector4& color) 
	{
	}
	// 後処理をおこなう
	virtual void Finalize() 
	{
	};
	// デストラクタ
	virtual ~Tank() 
	{
	};

private:
	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 速度
	DirectX::SimpleMath::Vector2 m_velocity;
	// 角度
	float m_bodyAngle;
	// 砲塔角度
	float m_turretAngle;
	// 色
	DirectX::SimpleMath::Vector4 m_color;
};

#endif // TANK_DEFINED
