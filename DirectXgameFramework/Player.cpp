#include "Player.h"
#include <iostream>

// �R���X�g���N�^
Player::Player()
{
}

// ����������
void Player::Initialize(const DirectX::SimpleMath::Vector2& position, const float& angle, const DirectX::SimpleMath::Vector4& color)
{
	// Keyboard�I�u�W�F�N�g�𐶐�����
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	// KeyboardStateTracker�I�u�W�F�N�g�𐶐�����
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// Mouse�I�u�W�F�N�g�𐶐�����
	m_mouse = std::make_unique<DirectX::Mouse>();
	// ButtonStateTracker�I�u�W�F�N�g�𐶐�����
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// TankFactory�I�u�W�F�N�g�𐶐�����
	TankFactory tankFactory(position, angle, color);
	// Body�I�u�W�F�N�g�𐶐����� 
	m_tank = tankFactory.Create(Tank::PARTS_ID::BODY);
	// Turret�I�u�W�F�N�𐶐�����
	m_tank->AddParts(tankFactory.Create(Tank::PARTS_ID::TURRET));

	// �e�H��쐬
	m_bulletFactory = std::make_unique<BulletFactory>(&m_bullets);
	m_bulletFactory->Initialize();
	// Cannon�I�u�W�F�N�𐶐�����
	m_tank->GetParts()->AddParts(tankFactory.Create(Tank::PARTS_ID::CANNON));
	m_tank->GetParts()->GetParts()->SetBulletFactory(m_bulletFactory.get());
}

// Player�I�u�W�F�N�g���X�V����
bool Player::Update(const DX::StepTimer& timer)
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	DirectX::Keyboard::State keyboardState = m_keyboard->GetState();
	// �L�[�{�[�h�g���b�J�[���X�V����
	m_keyboardTracker->Update(keyboardState);
	// �}�E�X�̏�Ԃ��擾����
	DirectX::Mouse::State mouseState = m_mouse->GetState();
	// �}�E�X�g���b�J�[���X�V����
	m_mouseTracker->Update(mouseState);

	// ���x�����Z�b�g����
	m_tank->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f));
	// �E�ɉ�]����
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::D) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		// ��]�p��ݒ肷��
		m_tank->SetBodyAngle(m_tank->GetBodyAngle() - DirectX::XMConvertToRadians(1.0f));
	}
	// ���ɉ�]����
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::A) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		// ��]�p��ݒ肷��
		m_tank->SetBodyAngle(m_tank->GetBodyAngle() + DirectX::XMConvertToRadians(1.0f));
	}
	// �^���b�g���E�ɉ�]����
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::E))
	{
		// ��]�p��ݒ肷��
		m_tank->GetParts()->SetBodyAngle(m_tank->GetParts()->GetBodyAngle() - DirectX::XMConvertToRadians(1.0f));
	}
	// �^���b�g�����ɉ�]����
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Q))
	{
		// ��]�p��ݒ肷��
		m_tank->GetParts()->SetBodyAngle(m_tank->GetParts()->GetBodyAngle() + DirectX::XMConvertToRadians(1.0f));
	}
	// �O�i����
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::W) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Up))
	{
		// ��]�s��𐶐�����
		DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateRotationZ(-m_tank->GetBodyAngle());
		// ���x��ݒ肷��
		m_tank->SetVelocity(DirectX::SimpleMath::Vector2::Transform(Tank::SPEED, rotation));
	}
	// ��ނ���
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::S) || keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Down))
	{
		// ��]�s��𐶐�����
		DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateRotationZ(-m_tank->GetBodyAngle());
		// ���x��ݒ肷��
		m_tank->SetVelocity(-DirectX::SimpleMath::Vector2::Transform(Tank::SPEED, rotation));
	}
	//// �L���m�������ɉ�]����
	//if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::C))
	//{
	//	// ��]�p��ݒ肷��
	//	m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() - DirectX::XMConvertToRadians(1.0f));
	//}
	//// �L���m������O�ɉ�]����
	//else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Z))
	//{
	//	// ��]�p��ݒ肷��
	//	m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() + DirectX::XMConvertToRadians(1.0f));
	//}
	// ����
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		static float time = 0;
		time += static_cast<float>(timer.GetElapsedSeconds());
		if (time > .1f)
		{
			// ����
			m_tank->GetParts()->GetParts()->Shot(timer);
			time = 0;
		}
	}
	// �؂�ւ�
	if (m_keyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::Z))
	{
		m_tank->GetParts()->GetParts()->SwitchShot(-1);
	}
	// �؂�ւ�
	if (m_keyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::X))
	{
		m_tank->GetParts()->GetParts()->SwitchShot(1);
	}
	// �E�B�[��
	{
		int wheel = m_mouseTracker->GetLastState().scrollWheelValue;
		int diff = wheel - m_mouseWheel;
		m_mouseWheel = wheel;

		m_tank->GetParts()->GetParts()->SwitchShot(diff == 0 ? 0 : (diff > 0 ? -1 : 1));
	}

	// �ړ�����
	m_tank->SetPosition(m_tank->GetPosition() + m_tank->GetVelocity());
	// Tank�I�u�W�F�N�g���X�V����
	m_tank->Update(timer);
	// �e���X�V
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

// �X�v���C�g��`�悷��
void Player::Render(DirectX::SpriteBatch& spriteBatch)
{
	// Tank�I�u�W�F�N�g��`�悷��
	m_tank->Render(spriteBatch, m_tank->GetPosition(), m_tank->GetBodyAngle(), m_tank->GetColor());
	// �e��`��
	for (auto& bullet : m_bullets)
		bullet->Render(spriteBatch);
}

// �㏈���������Ȃ�
void Player::Finalize()
{
	// �ċA�I��Tank�I�u�W�F�N�g�̌㏈���������Ȃ�
	m_tank->Finalize();
	// Tank�I�u�W�F�N�g�����Z�b�g����
	if (m_tank != nullptr)
		delete m_tank;
	// �e�����Z�b�g
	for (auto& bullet : m_bullets)
	{
		bullet->Finalize();
	}
}
