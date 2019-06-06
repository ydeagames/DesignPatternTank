#ifndef  WINDOW_DEFINED
#define  WINDOW_DEFINED

#include <windows.h>
#include <mouse.h>
#include <keyboard.h>
#include "Game.h"

const wchar_t appName[] = L"Factory method 2019/06/03";

class Window 
{
public:
	// �R���X�g���N�^
	Window(HINSTANCE hInstance, int nCmdShow) : m_hInstance(hInstance), m_nCmdShow(nCmdShow) 
	{
	}
	// �N���X��o�^���E�B���h�E�𐶐�����
	int Initialize(int width, int height) 
	{
		// �N���X��o�^����
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInstance;
		wcex.hIcon = LoadIcon(m_hInstance, L"IDI_ICON");
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = appName;
;
		wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
		// �N���X��o�^����
		if (!RegisterClassEx(&wcex))
			return 1;

		// �E�B���h�E�𐶐�����
		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = static_cast<LONG>(width);
		rc.bottom = static_cast<LONG>(height);

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		// �E�B���h�E�𐶐����� Create window
		HWND hWnd = CreateWindowEx(0, appName, appName, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);

		if (!hWnd)
			return 1;
		// �E�B���h�E��\������
		 ::ShowWindow(hWnd, m_nCmdShow);
		// TODO: nCmdShow��SW_SHOWMAXIMIZED���Z�b�g���ċK��Ńt���X�N���[���ɕύX����
		// Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.
		// SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_game.get()));

		// GetClientRect(hwnd, &rc);
		// Initialize window
		// g_game->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
		m_hWnd = hWnd;
		return 0;
	}

	// �E�B���h�E��\������
	void ShowWindow()
	{
		// �E�B���h�E��\������
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	// �E�B���h�E�n���h�����擾����
	HWND GetHWnd() const
	{ 
		return m_hWnd; 
	}
	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// �E�B���h�E�n���h��
	HWND m_hWnd;
	// �C���X�^���X�n���h��
	HINSTANCE m_hInstance;
	// �E�B���h�E�̕\�����
	int m_nCmdShow;
};

#endif	// WINDOW_DEFINED

