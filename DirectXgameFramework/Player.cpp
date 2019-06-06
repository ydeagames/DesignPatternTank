#include "Player.h"

// コンストラクタ
Player::Player() 
{
}

// 初期化する
void Player::Initialize(const DirectX::SimpleMath::Vector2& position, const float& angle, const DirectX::SimpleMath::Vector4& color)
{
	// Keyboardオブジェクトを生成する
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	// KeyboardStateTrackerオブジェクトを生成する
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// TankFactoryオブジェクトを生成する
	TankFactory tankFactory(position, angle, color);
	// Bodyオブジェクトを生成する 
	m_tank = tankFactory.Create(Tank::PARTS_ID::BODY);
	// Turretオブジェクを生成する
	m_tank->AddParts(tankFactory.Create(Tank::PARTS_ID::TURRET));
	// Cannonオブジェクを生成する
	m_tank->GetParts()->AddParts(tankFactory.Create(Tank::PARTS_ID::CANNON));
}

// Playerオブジェクトを更新する
bool Player::Update(const DX::StepTimer& timer) 
{
	// キーボードの状態を取得する
	DirectX::Keyboard::State keyboardState = m_keyboard->GetState();
	// キーボードトラッカーを更新する
	m_keyboardTracker->Update(keyboardState);

	// 速度をリセットする
	m_tank->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f));
	// 右に回転する
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::D) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		// 回転角を設定する
		m_tank->SetBodyAngle(m_tank->GetBodyAngle() - DirectX::XMConvertToRadians(1.0f));
	}
	// 左に回転する
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::A) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		// 回転角を設定する
		m_tank->SetBodyAngle(m_tank->GetBodyAngle() + DirectX::XMConvertToRadians(1.0f));
	}
	// タレットを右に回転する
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::E))
	{
		// 回転角を設定する
		m_tank->GetParts()->SetBodyAngle(m_tank->GetParts()->GetBodyAngle() - DirectX::XMConvertToRadians(1.0f));
	}
	// タレットを左に回転する
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Q))
	{
		// 回転角を設定する
		m_tank->GetParts()->SetBodyAngle(m_tank->GetParts()->GetBodyAngle() + DirectX::XMConvertToRadians(1.0f));
	}
	// 前進する
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::W) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Up))
	{
		// 回転行列を生成する
		DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateRotationZ(-m_tank->GetBodyAngle());
		// 速度を設定する
		m_tank->SetVelocity(DirectX::SimpleMath::Vector2::Transform(Tank::SPEED, rotation));
	}
	// 後退する
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::S) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Down))
	{
		// 回転行列を生成する
		DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateRotationZ(-m_tank->GetBodyAngle());
		// 速度を設定する
		m_tank->SetVelocity(-DirectX::SimpleMath::Vector2::Transform(Tank::SPEED, rotation));
	}
	// キャノンを奥に回転する
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::C))
	{
		// 回転角を設定する
		m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() - DirectX::XMConvertToRadians(1.0f));
	}
	// キャノンを手前に回転する
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Z))
	{
		// 回転角を設定する
		m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() + DirectX::XMConvertToRadians(1.0f));
	}
	// 移動する
	m_tank->SetPosition(m_tank->GetPosition() + m_tank->GetVelocity());
	// Tankオブジェクトを更新する
	m_tank->Update(timer);

	return true;
}

// スプライトを描画する
void Player::Render(DirectX::SpriteBatch& spriteBatch)
{
	// Tankオブジェクトを描画する
	m_tank->Render(spriteBatch, m_tank->GetPosition(), m_tank->GetBodyAngle(), m_tank->GetColor());
}

// 後処理をおこなう
void Player::Finalize() 
{
	// 再帰的にTankオブジェクトの後処理をおこなう
	m_tank->Finalize();	
	// Tankオブジェクトをリセットする
	if(m_tank != nullptr)
		delete m_tank;
}
