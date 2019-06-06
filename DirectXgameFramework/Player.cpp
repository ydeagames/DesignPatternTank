#include "Player.h"

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

	// TankFactory�I�u�W�F�N�g�𐶐�����
	TankFactory tankFactory(position, angle, color);
	// Body�I�u�W�F�N�g�𐶐����� 
	m_tank = tankFactory.Create(Tank::PARTS_ID::BODY);
	// Turret�I�u�W�F�N�𐶐�����
	m_tank->AddParts(tankFactory.Create(Tank::PARTS_ID::TURRET));
	// Cannon�I�u�W�F�N�𐶐�����
	m_tank->GetParts()->AddParts(tankFactory.Create(Tank::PARTS_ID::CANNON));
}

// Player�I�u�W�F�N�g���X�V����
bool Player::Update(const DX::StepTimer& timer) 
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	DirectX::Keyboard::State keyboardState = m_keyboard->GetState();
	// �L�[�{�[�h�g���b�J�[���X�V����
	m_keyboardTracker->Update(keyboardState);

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
	// �L���m�������ɉ�]����
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::C))
	{
		// ��]�p��ݒ肷��
		m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() - DirectX::XMConvertToRadians(1.0f));
	}
	// �L���m������O�ɉ�]����
	else if (keyboardState.IsKeyDown(DirectX::Keyboard::Keys::Z))
	{
		// ��]�p��ݒ肷��
		m_tank->GetParts()->GetParts()->SetTurretAngle(m_tank->GetParts()->GetParts()->GetTurretAngle() + DirectX::XMConvertToRadians(1.0f));
	}
	// �ړ�����
	m_tank->SetPosition(m_tank->GetPosition() + m_tank->GetVelocity());
	// Tank�I�u�W�F�N�g���X�V����
	m_tank->Update(timer);

	return true;
}

// �X�v���C�g��`�悷��
void Player::Render(DirectX::SpriteBatch& spriteBatch)
{
	// Tank�I�u�W�F�N�g��`�悷��
	m_tank->Render(spriteBatch, m_tank->GetPosition(), m_tank->GetBodyAngle(), m_tank->GetColor());
}

// �㏈���������Ȃ�
void Player::Finalize() 
{
	// �ċA�I��Tank�I�u�W�F�N�g�̌㏈���������Ȃ�
	m_tank->Finalize();	
	// Tank�I�u�W�F�N�g�����Z�b�g����
	if(m_tank != nullptr)
		delete m_tank;
}
