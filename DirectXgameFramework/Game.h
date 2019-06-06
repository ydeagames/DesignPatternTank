#ifndef GAME_DEFINED
#define GAME_DEFINED

#include <windows.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Keyboard.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <string>

#include "StepTimer.h"
#include "dx.h"
#include "Window.h"
#include "DirectX11.h"

#include "Player.h"

class Window;

class Game 
{
public:
	// �X�v���C�g�o�b�`���擾����
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spriteBatch.get();
	}
	// �R�����X�e�[�g���擾����
	DirectX::CommonStates* GetCommonStates() 
	{
		return m_commonStates.get();
	}
	// ��{�Q�[�����[�v�����s���� 
	MSG Run();
	// �R���X�g���N�^
    Game(int width, int height);
    // �������� 
    virtual void Initialize();
	// �X�V���� 
	virtual void Update(const DX::StepTimer& timer);
	// �o�b�t�@���N���A���� 
	void Clear();
	// �V�[����`�悷��
	virtual void Render(const DX::StepTimer& timer);
	// �o�b�N�o�b�t�@���X�N���[���ɑ���
	void Present();
	// �I�������������Ȃ� 
	virtual void Finalize();

    // ���b�Z�[�W 
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // �v���p�e�B 
    void GetDefaultSize(int& width, int& height) const;
	// FPS��`�悷�� 
	void DrawFPS();

private:
	// �C���X�^���X�n���h��
	HINSTANCE m_hInstance;
	// ���s���̃E�B���h�E�̑傫��
	int m_nCmdShow;
    // �f�o�C�X���\�[�X
    HWND m_hWnd;
	// �o�͕� 
    int m_width;
	// �o�͍� 
    int m_height;
    // ���[�v�^�C�}�[��`�悷�� 
    DX::StepTimer m_timer;
	// �E�B���h�E
	std::unique_ptr<Window> m_window;

	// �@�\���x�� 
    D3D_FEATURE_LEVEL m_featureLevel;
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// �X�v���C�g�o�b�` 
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// �t�H���g Font
	std::unique_ptr<DirectX::SpriteFont> m_font;
	// DirectX11 �O���t�B�b�N�X 
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// GAME_DEFINED
