#include "Game.h"

void ExitGame();

// �R���X�g���N�^
Game::Game(int width, int height)
	: 
	m_hWnd(0), m_width(width), m_height(height), m_featureLevel(D3D_FEATURE_LEVEL_9_1) {
	
	// �X�^�[�g�A�b�v���
	STARTUPINFO si{};	
	// �C���X�^���X�n���h�����擾����
	m_hInstance = ::GetModuleHandle(NULL);
	
	// STARTUPINFO�\���̂̓��e���擾����
	::GetStartupInfo(&si);
	m_nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	// Window�I�u�W�F�N�g�𐶐����� 
	m_window = std::make_unique<Window>(m_hInstance, m_nCmdShow);

}

// ��{�Q�[�����[�v�����s���� 
MSG Game::Run() 
{
	// ���b�Z�[�W 
	MSG msg = {};

	// MyGame�I�u�W�F�N�g������������
	Initialize();
	// �Q�[�����[�v
	while (WM_QUIT != msg.message) 
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// �Q�[�����X�V���� 
			this->m_timer.Tick([&]() { Update(m_timer); });
			// �V�[����`�悷�� 
			Render(m_timer);
		}
	}
	// MyGame�I�u�W�F�N�g�̏I�������������Ȃ�
	Finalize();
	return msg;
}

// ���s�ɕK�v�ƂȂ�Direct3D���\�[�X������������
void Game::Initialize() 
{
	// Window�I�u�W�F�N�g������������
	m_window->Initialize(m_width, m_height);
	// Window�I�u�W�F�N�g�̐�����ɃE�B���h�E�n���h�����擾����
    m_hWnd = m_window->GetHWnd();
	// �E�B���h�E��\������
	m_window->ShowWindow();

	// DirectX11 Graphics�N���X�̃C���X�^���X���擾����
	DirectX11& directX11 = DirectX11::Get();
	// DirectX�̏������̂��߃E�B���h�E�n���h����ݒ肷��
	directX11.SetHWnd(m_hWnd);
	// DirectX�̏������̂��߃E�B���h�E����ݒ肷��
	directX11.SetWidth(m_width);
	// DirectX�̏������̂��߃E�B���h�E����ݒ肷��
	directX11.SetHeight(m_height);

	// �f�o�C�X�𐶐����� 
	directX11.CreateDevice();
	// ���\�[�X�𐶐�����
	directX11.CreateResources();

    // TODO: �f�t�H���g�ϐ�timestep���[�h�ȊO�̂��̂��K�v�ȏꍇ�^�C�}�[�ݒ��ύX����
	// �Ⴆ�� 60 FPS�Œ�^�C���X�e�b�v�X�V���W�b�N�ɑ΂��Ă͈ȉ����Ăяo��
	// Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    
    // this->timer.SetFixedTimeStep(true);
    // this->timer.SetTargetElapsedSeconds(1.0 / 60);

	// TODO: �������R�[�h��ǉ�����
	
	// SpriteBatch�I�u�W�F�N�g�𐶐�����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(directX11.GetContext().Get());
	// �R�����X�e�[�g�𐶐�����
	m_commonStates = std::make_unique<DirectX::CommonStates>(directX11.GetDevice().Get());
	// Font�I�u�W�F�N�g�𐶐����� 
	m_font = std::make_unique<DirectX::SpriteFont>(directX11.GetDevice().Get(), L"myfile.spritefont");

}

// �I�������������Ȃ�
void Game::Finalize() 
{
	// Font�I�u�W�F�N�g��j������
	m_font.reset();
	// SpriteBatch�I�u�W�F�N�g��j������
	m_spriteBatch.reset();
	// �R�����X�e�[�g��j������
	m_commonStates.reset();
	// DirectX11 Graphics�I�u�W�F�N�g��j������
	DirectX11::Dispose();
	// Window�I�u�W�F�N�g��j������
	m_window.reset();
}


// ���[���h���X�V���� 
void Game::Update(const DX::StepTimer& timer)
{
}

// �V�[����`�悷�� 
void Game::Render(const DX::StepTimer& timer) 
{
}

// FPS��`�悷��
void Game::DrawFPS() 
{
	// FPS������𐶐����� 
	std::wstring fpsString = L"fps = " + std::to_wstring((unsigned int)this->m_timer.GetFramesPerSecond());
	// FPS��`�悷�� 
	m_font->DrawString(m_spriteBatch.get(), fpsString.c_str(), DirectX::SimpleMath::Vector2(0, 0), DirectX::Colors::White);
}

// �o�b�N�o�b�t�@���N���A���邽�߂̃w���p�[�֐� 
void Game::Clear()
{
    // DirectX11 Graphics�N���X�̃C���X�^���X���擾����
	DirectX11& directX11 = DirectX11::Get();
	// �����_�[�^�[�Q�b�g���N���A���� 
	directX11.GetContext()->ClearRenderTargetView(directX11.GetRenderTargetView().Get(), DirectX::Colors::Black);
	// �f�v�X�X�e���V���r���[��ݒ肷�� 
	directX11.GetContext()->ClearDepthStencilView(directX11.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// �����_�[�^�b�Q�[�g��ݒ肷�� 
	directX11.GetContext()->OMSetRenderTargets(1, directX11.GetRenderTargetView().GetAddressOf(), directX11.GetDepthStencilView().Get());
    // �r���[�|�[�g��ݒ肷�� 
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	directX11.GetContext()->RSSetViewports(1, &viewport);
}

// �o�b�N�o�b�t�@���X�N���[���ɑ��� 
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
	 
	// DirectX11 Graphics�N���X�̃C���X�^���X���擾����
	DirectX11& directX = DirectX11::Get();
	HRESULT hr = directX.GetSwapChain()->Present(1, 0);

    // �f�o�C�X�����Z�b�g���ꂽ�ꍇ�����_�����ď���������K�v������ 
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
		directX.OnDeviceLost();
    }
    else 
	{
        DX::ThrowIfFailed(hr);
    }
}

// ���b�Z�[�W�n���h�� 
void Game::OnActivated()
{
    // TODO: �Q�[�����A�N�e�B�u�ȃE�B���h�E�ɂȂ�
}

void Game::OnDeactivated()
{
    // TODO: �Q�[�����o�b�N�O���E���h�E�B���h�E�ɂȂ� 
}

void Game::OnSuspending()
{
    // TODO: �Q�[�����p���[�T�X�y���f�b�h�ɂȂ� 
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

    // TODO: �Q�[�����p���[���W���[���ɂȂ� 
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_width = width;
    m_height = height;
	
	DirectX11::Get().CreateResources();
    // TODO: �Q�[���E�B���h�E�̃T�C�Y���ĕύX����� 
}

// �v���p�e�B Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: �C�ӂ̃f�t�H���g�E�B���h�E�T�C�Y�ɕύX����(�ŏ��T�C�Y��320x200) 
    width = 800;
    height = 600;
}

// Exit�w���p�[�֐� 
void ExitGame() 
{
	PostQuitMessage(0);
}
