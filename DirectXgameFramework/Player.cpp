#include "Player.h"
#include <iostream>

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

	// Mouseオブジェクトを生成する
	m_mouse = std::make_unique<DirectX::Mouse>();
	// ButtonStateTrackerオブジェクトを生成する
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// TankFactoryオブジェクトを生成する
	TankFactory tankFactory(position, angle, color);
	// Bodyオブジェクトを生成する 
	m_tank = tankFactory.Create(Tank::PARTS_ID::BODY);
	// Turretオブジェクを生成する
	m_tank->AddParts(tankFactory.Create(Tank::PARTS_ID::TURRET));

	// 弾工場作成
	m_bulletFactory = std::make_unique<BulletFactory>(&m_bullets);
	m_bulletFactory->Initialize();
	// Cannonオブジェクを生成する
	m_tank->GetParts()->AddParts(tankFactory.Create(Tank::PARTS_ID::CANNON));
	m_tank->GetParts()->GetParts()->SetBulletFactory(m_bulletFactory.get());
}

// Playerオブジェクトを更新する
bool Player::Update(const DX::StepTimer& timer)
{
	// キーボードの状態を取得する
	DirectX::Keyboard::State keyboardState = m_keyboard->GetState();
	// キーボードトラッカーを更新する
	m_keyboardTracker->Update(keyboardState);
	// マウスの状態を取得する
	DirectX::Mouse::State mouseState = m_mouse->GetState();
	// マウストラッカーを更新する
	m_mouseTracker->Update(mouseState);

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
	//// キャノンを奥に回転する
	//if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::C))
	//{
	//	// 回転角を設定する
	//	m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() - DirectX::XMConvertToRadians(1.0f));
	//}
	//// キャノンを手前に回転する
	//else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Z))
	//{
	//	// 回転角を設定する
	//	m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() + DirectX::XMConvertToRadians(1.0f));
	//}
	// 発射
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		static float time = 0;
		time += static_cast<float>(timer.GetElapsedSeconds());
		if (time > .1f)
		{
			// 発射
			m_tank->GetParts()->GetParts()->Shot(timer);
			time = 0;
		}
	}
	// 切り替え
	if (m_keyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::Z))
	{
		m_tank->GetParts()->GetParts()->SwitchShot(-1);
	}
	// 切り替え
	if (m_keyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::X))
	{
		m_tank->GetParts()->GetParts()->SwitchShot(1);
	}
	// ウィール
	{
		int wheel = m_mouseTracker->GetLastState().scrollWheelValue;
		int diff = wheel - m_mouseWheel;
		m_mouseWheel = wheel;

		m_tank->GetParts()->GetParts()->SwitchShot(diff == 0 ? 0 : (diff > 0 ? -1 : 1));
	}

	// 移動する
	m_tank->SetPosition(m_tank->GetPosition() + m_tank->GetVelocity());
	// Tankオブジェクトを更新する
	m_tank->Update(timer);
	// 弾を更新
	for (auto& bullet : m_bullets)
		bullet->Update(timer);

	{
		DirectX::SimpleMath::Vector2 size = Bullet::SIZE;

		DirectX::SimpleMath::Vector2 windowSize = DirectX::SimpleMath::Vector2(float(DirectX11::Get().GetWidth()), float(DirectX11::Get().GetHeight()));

		DirectX::SimpleMath::Vector2 regionMin = -size / 2.f;
		DirectX::SimpleMath::Vector2 regionMax = windowSize + (DirectX::SimpleMath::Vector2)(size / 2.f);

		for (auto itr = m_bullets.begin(); itr != m_bullets.end();)
		{
			auto& bullet = (*itr);
			auto& pos = bullet->GetPosition();

			if (pos.x < regionMin.x || pos.y < regionMin.y || pos.x > regionMax.x || pos.y > regionMax.y || !bullet->IsUsed())
			{
				itr = m_bullets.erase(itr);
			} else ++itr;
		}

		//std::cout << "count : " << m_bullets.size();
	}

	return true;
}

// スプライトを描画する
void Player::Render(DirectX::SpriteBatch& spriteBatch)
{
	// Tankオブジェクトを描画する
	m_tank->Render(spriteBatch, m_tank->GetPosition(), m_tank->GetBodyAngle(), m_tank->GetColor());
	// 弾を描画
	for (auto& bullet : m_bullets)
		bullet->Render(spriteBatch);
}

// 後処理をおこなう
void Player::Finalize()
{
	// 再帰的にTankオブジェクトの後処理をおこなう
	m_tank->Finalize();
	// Tankオブジェクトをリセットする
	if (m_tank != nullptr)
		delete m_tank;
	// 弾をリセット
	for (auto& bullet : m_bullets)
	{
		bullet->Finalize();
	}
}
