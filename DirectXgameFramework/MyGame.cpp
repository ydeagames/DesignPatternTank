#include "MyGame.h"

// �R���X�g���N�^
MyGame::MyGame(int width, int height) : Game(width, height)
{
}

// MyGame�I�u�W�F�N�g����������
void MyGame::Initialize() 
{
	// ��{�N���X��Initialize���Ăяo�� 
	Game::Initialize();

	// Player�I�u�W�F�N�g�𐶐����� 
	m_player = std::make_unique<Player>();
	// Player�I�u�W�F�N�g������������ 
	m_player->Initialize(DirectX::SimpleMath::Vector2(200.0f, 300.0f), DirectX::XMConvertToRadians(0.0f), DirectX::SimpleMath::Vector4(DirectX::Colors::BlanchedAlmond));
}

// �Q�[�����X�V���� 
void MyGame::Update(const DX::StepTimer& timer) 
{
	float elapsedTime = float(timer.GetElapsedSeconds());
	// TODO: �X�V������ǉ�����

	// �v���C�����X�V����
	m_player->Update(timer);
}

// �V�[����`�悷�� Draws scene
void MyGame::Render(const DX::StepTimer& timer) 
{
	// �ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ��� 
	if (timer.GetFrameCount() == 0) 
		return;

	// TODO: �����_�����O�R�[�h��ǉ����� 
	// �o�b�t�@���N���A����
	Clear();
	// �`����n�߂� 
	GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, GetCommonStates()->NonPremultiplied());
	// �`�悷�� 
	m_player->Render(*GetSpriteBatch());

	// �`����I���� 
	GetSpriteBatch()->End();
	// �o�b�N�o�b�t�@���X�N���[���ɑ��� 
	Present();
}

// �I�������������Ȃ� 
void MyGame::Finalize() 
{

	// Player�I�u�W�F�N�g�̌㏈���������Ȃ�
	m_player->Finalize();
	// Player�I�u�W�F�N�g�����Z�b�g����
	m_player.reset();

	// ��{�N���X��Finalize���Ăяo��
	Game::Finalize();
}
