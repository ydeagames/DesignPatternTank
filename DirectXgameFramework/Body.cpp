#include "Body.h"

// コンストラクタ
Body::Body()
	: m_tank(nullptr)
{
}

// パーツを追加する
void Body::AddParts(Tank* tank) 
{
	// パーツを追加する
	m_tank = tank;
}

// パーツを取得する
Tank* Body::GetParts()
{
	// パーツを追加する
	return m_tank;
}

// 初期化する
void Body::Initialize()
{
	// Turretテクスチャをロードする
	DirectX::CreateWICTextureFromFile(DirectX11::Get().GetDevice().Get(),
	L"tank1.png", nullptr, m_texture.ReleaseAndGetAddressOf());
}

// 更新する
void Body::Update(const DX::StepTimer& timer)
{
}

// 描画する
void Body::Render(DirectX::SpriteBatch& spriteBatch, DirectX::SimpleMath::Vector2& position, float angle, DirectX::SimpleMath::Vector4& color) 
{
	// スプライトを描画する
	spriteBatch.Draw(m_texture.Get(), position, nullptr, color, -angle + DirectX::XMConvertToRadians(90.0f), DirectX::SimpleMath::Vector2(64.0f, 64.0f));
	if(m_tank != nullptr)
		// Render関数を呼び出す
		m_tank->Render(spriteBatch, position, angle, color);

}

// 後処理をおこなう
void Body::Finalize() 
{
	// テクスチャをリセットする
	m_texture.Reset();

	if (m_tank != nullptr) 
	{
		// 再帰的にFinalize関数を呼び出す
		m_tank->Finalize();
		// パーツを破棄する
		delete m_tank;
	}
}
