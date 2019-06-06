#ifndef BODY_DEFINED
#define BODY_DEFINED

#include <vector>

#include "Tank.h"

// Bodyクラス
class Body : public Tank 
{
public:
	// コンストラクタ
	Body();
	// パーツを追加する
	void AddParts(Tank* tank) override;
	// パーツを取得する
	Tank* GetParts() override;
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
	~Body()override {}

private:
	Tank* m_tank;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

#endif // TANK_BODY
